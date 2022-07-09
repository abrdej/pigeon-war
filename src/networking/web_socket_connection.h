#pragma once

#include <iostream>
#include <memory>
#include <queue>

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include <networking/message.h>
#include <logging/logger.h>

namespace networking {

class web_socket_connection : public std::enable_shared_from_this<web_socket_connection> {
 public:
  using my_owned_message_type = owned_message_type<web_socket_connection>;

  web_socket_connection(boost::asio::io_context& context,
                        boost::asio::ip::tcp::socket socket,
                        std::queue<my_owned_message_type>& messages_in)
      : context_(context), web_socket_(std::move(socket)), messages_in_(messages_in), id_(-1) {}

  ~web_socket_connection() = default;

  template <typename OnAccepted>
  void connect_to_client(std::uint32_t id, OnAccepted on_accepted) {
    on_accepted_ = std::move(on_accepted);
    id_ = id;
    boost::beast::net::dispatch(web_socket_.get_executor(),
                                boost::beast::bind_front_handler(
                                    &web_socket_connection::accept_handshake, shared_from_this()));
  }

  std::uint32_t get_id() const {
    return id_;
  }

  void disconnect() {
    if (connected()) {
      boost::asio::post(context_, [this]() { web_socket_.close(boost::beast::websocket::close_code::normal); });
    }
  }

  bool connected() {
    return web_socket_.is_open();
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
  void accept_handshake() {
    web_socket_.async_accept([this](boost::beast::error_code ec) {
      if (ec) {
        LOG(debug) << "Failed to accept: " << ec.message();
      } else {
        LOG(debug) << "Accepted with id: " << id_;
        on_accepted_(shared_from_this());
        read_message();
      }
    });
  }

  void write_message() {
    web_socket_.async_write(boost::asio::buffer(messages_out_.front()),
        [this](std::error_code ec, std::size_t length) {
          if (!ec) {
            LOG(debug) << "Write message for: " << id_ << ".";
            messages_out_.pop();

            if (!messages_out_.empty()) {
              write_message();
            }
          } else {
            LOG(debug) << "Write message fail for: " << id_ << ".";
            web_socket_.close(boost::beast::websocket::close_code::going_away);
          }
        });
  }

  void read_message() {
    boost::asio::async_read_until(web_socket_, boost::asio::dynamic_buffer(string_buffer_), "\n",
                            [this](std::error_code ec, std::size_t length) {
                              if (!ec) {
                                add_incoming_message(length);

                              } else {
                                LOG(debug) << "Read body fail for: " << id_ << ".";
                                boost::beast::error_code bec;
                                web_socket_.close(boost::beast::websocket::close_code::going_away, bec);
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

  std::function<void(std::shared_ptr<web_socket_connection>)> on_accepted_;

  boost::beast::websocket::stream<boost::beast::tcp_stream> web_socket_;

  boost::asio::io_context& context_;
  std::queue<message_type> messages_out_;
  std::queue<my_owned_message_type>& messages_in_;

  std::string string_buffer_;

  std::uint32_t id_;
};

}  // namespace networking
