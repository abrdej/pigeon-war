#pragma once

#include <iostream>
#include <memory>
#include <queue>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>

#include <networking/message.h>
#include <networking/owned_message.h>
#include <logging/logger.h>

namespace networking {

class socket_connection;

using message_type = std::string;

class socket_connection : public std::enable_shared_from_this<socket_connection> {
 public:
  using my_owned_message_type = owned_message_type<socket_connection>;

  socket_connection(boost::asio::io_context& context,
                    boost::asio::ip::tcp::socket socket,
                    std::queue<my_owned_message_type>& messages_in)
      : context_(context), socket_(std::move(socket)), messages_in_(messages_in), id_(-1) {}

  ~socket_connection() = default;

  void connect_to_server(const boost::asio::ip::tcp::resolver::results_type& endpoints) {
    // Request asio attempts to connect to an endpoint

    if (socket_.is_open()) {
      LOG(debug) << "connect_to_server: socket is open";
    }

    boost::asio::async_connect(socket_, endpoints,
                               [this](std::error_code ec, const boost::asio::ip::tcp::endpoint& endpoint) {
                                 if (!ec) {
                                   LOG(debug) << "connect_to_server: Start message reading: " << id_;
                                   LOG(debug) << "connect_to_server: Start message reading address: " << endpoint.address().to_string()
                                    << " and port: " << endpoint.port();

                                   read_message();
                                 } else {
                                   LOG(error) << "Async connect issue: " << ec.message();
                                 }
                               });
  }

  template <typename OnAccepted>
  void connect_to_client(std::uint32_t id, OnAccepted on_accepted) {
    on_accepted_ = std::move(on_accepted);
    if (socket_.is_open()) {
      id_ = id;
      boost::beast::net::dispatch(socket_.get_executor(),
                                  boost::beast::bind_front_handler(
                                  [this]() {
                                    on_accepted_(shared_from_this());
                                    read_message();
                                  }));
      LOG(debug) << "connect_to_client: Start message reading: " << id_;
    }
  }

  std::uint32_t get_id() const {
    return id_;
  }

  void disconnect() {
    if (connected()) {
      boost::asio::post(context_, [this]() { socket_.close(); });
    }
  }

  bool connected() {
    return socket_.is_open();
  }

  void send(message_type message) {
    boost::asio::post(context_,
                      [this, my_message = std::move(message)]() mutable {
                        bool is_writing_message = !messages_out_.empty();
                        // need to trim all "\n", and add one at the end
                        boost::erase_all(my_message, "\n");
                        messages_out_.push(std::move(my_message + "\n"));
                        if (!is_writing_message) {
                          write_message();
                        }
                      });
  }

 private:
  void write_message() {
    LOG(debug) << "Start async write for: " << id_ ;
    boost::asio::async_write(socket_, boost::asio::buffer(messages_out_.front()),
                             [this](std::error_code ec, std::size_t length) {
                               if (!ec) {

                                 LOG(debug) << "writen message: " << messages_out_.front();

                                 messages_out_.pop();
                                 if (!messages_out_.empty()) {
                                   write_message();
                                 }
                               } else {
                                 LOG(debug) << "Write body fail for: " << id_ << " with: " << ec.message();
                                 socket_.close();
                               }
                             });
  }

  void read_message() {
    boost::asio::async_read_until(socket_, boost::asio::dynamic_buffer(string_buffer_), "\n",
                                  [this](std::error_code ec, std::size_t length) {
                                    if (!ec) {
                                      add_incoming_message(length);

                                    } else {
                                      LOG(debug) << "Read body fail for: " << id_ << " with: " << ec.message();
                                      boost::system::error_code err;
                                      socket_.close(err);
                                      //read_message();
                                    }
                                  });
  }

  void add_incoming_message(std::size_t length) {
    auto message = string_buffer_.substr(0, length);
    LOG(debug) << "Adding incoming message: " << id_ << ", message: " << message;
    messages_in_.push(std::make_pair(weak_from_this().lock(), std::move(message)));
    boost::asio::dynamic_buffer(string_buffer_).consume(length);
    read_message();
  }

  std::function<void(std::shared_ptr<socket_connection>)> on_accepted_;

  boost::asio::ip::tcp::socket socket_;

  boost::asio::io_context& context_;
  std::queue<message_type> messages_out_;
  std::queue<my_owned_message_type>& messages_in_;

  std::string string_buffer_;

  std::uint32_t id_;
};

}  // namespace networking
