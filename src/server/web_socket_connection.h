#pragma once

#include <iostream>
#include <memory>
#include <queue>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include <server/message.h>

namespace networking {

class web_socket_connection;

using message_type = std::string;

using owned_message_type = std::pair<std::shared_ptr<web_socket_connection>, message_type>;

class web_socket_connection : public std::enable_shared_from_this<web_socket_connection> {
 public:
  web_socket_connection(boost::asio::io_context& context,
                        boost::asio::ip::tcp::socket socket,
                        std::queue<owned_message_type>& messages_in)
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
                        messages_out_.push(std::move(my_message));
                        if (!is_writing_message) {
                          write_message();
                        }
                      });
  }

 private:
  void accept_handshake() {
    web_socket_.async_accept([this](boost::beast::error_code ec) {
      if (ec) {
        std::cout << "Failed to accept: " << ec.message() << "\n";
      } else {
        std::cout << "Accepted with id: " << id_ << "\n";
        on_accepted_(shared_from_this());
        read_message();
      }
    });
  }

  void write_message() {
    web_socket_.async_write(boost::asio::buffer(messages_out_.front()),
        [this](std::error_code ec, std::size_t length) {
          if (!ec) {
            messages_out_.pop();

            if (!messages_out_.empty()) {
              write_message();
            }
          } else {
            std::cout << "Write body fail for: " << id_ << ".\n";
            web_socket_.close(boost::beast::websocket::close_code::going_away);
          }
        });
  }

  void read_message() {
    boost::asio::async_read_until(web_socket_, boost::asio::dynamic_buffer(string_buffer_), "\n",
                            [this](std::error_code ec, std::size_t length) {
                              if (!ec) {
                                add_incoming_message();

                              } else {
                                std::cout << "Read body fail for: " << id_ << ".\n";
                                web_socket_.close(boost::beast::websocket::close_code::going_away);
                              }
                            });
  }

  void add_incoming_message() {
    messages_in_.push(std::make_pair(shared_from_this(), std::move(string_buffer_)));
    read_message();
  }

  std::function<void(std::shared_ptr<web_socket_connection>)> on_accepted_;

  boost::beast::websocket::stream<boost::beast::tcp_stream> web_socket_;

  boost::asio::io_context& context_;
  std::queue<message_type> messages_out_;
  std::queue<owned_message_type>& messages_in_;

  std::string string_buffer_;

  std::uint32_t id_;
};

}  // namespace networking
