#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <thread>

#include <boost/asio/ip/tcp.hpp>

#include <networking/socket_connection.h>
#include <networking/owned_message.h>

namespace networking {

class client {
 public:
  using my_owned_message_type = owned_message_type<socket_connection>;

  client() = default;

  ~client() {
    disconnect();
  }

  bool connect(const std::string& host, std::uint16_t port) {
    try {
      connection_ = std::make_unique<socket_connection>(
          context_, boost::asio::ip::tcp::socket(context_), messages_in_);

      boost::asio::ip::tcp::resolver resolver(context_);
      auto endpoints = resolver.resolve(host, std::to_string(port));
      connection_->connect_to_server(endpoints);

      context_thread_ = std::thread([this]() {
        context_.run();
        LOG(warning) << "Context thread finished";
      });

      return true;

    } catch (std::exception& e) {
      LOG(error) << "client exception: " << e.what();
      return false;
    }
  }

  void disconnect() {
    if (connection_) {
      connection_->disconnect();
    }
    context_.stop();
    if (context_thread_.joinable()) {
      context_thread_.join();
    }
    connection_ = nullptr;
  }

  [[nodiscard]] bool connected() const {
    return connection_ && connection_->connected();
  }

  void send(std::string message) {
    if (connected()) {
      connection_->send(std::move(message));
    }
  }

  template <typename Callback>
  void on_message(Callback callback) {
    on_message_ = std::move(callback);
  }

  void update(std::size_t max_messages = -1) {
    size_t message_count = 0;
    while (message_count < max_messages && !messages_in_.empty()) {
      LOG(debug) << "Updating client messages";

      auto msg = messages_in_.front();
      messages_in_.pop();

      if (on_message_) {
        on_message_(msg.second);
      }

      ++message_count;
    }
  }

 private:
  boost::asio::io_context context_;
  std::thread context_thread_;
  std::unique_ptr<socket_connection> connection_;
  std::queue<my_owned_message_type> messages_in_;
  std::function<void(const std::string&)> on_message_;
};

}  // namespace networking
