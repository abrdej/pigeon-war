#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <thread>
#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <networking/owned_message.h>
#include <networking/web_socket_connection.h>

namespace networking {

template <typename connection_type>
class server {
 public:
  using my_owned_message_type = owned_message_type<connection_type>;

  explicit server(std::uint16_t port)
      : acceptor_(context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

  ~server() {
    stop();
  }

  bool start() {
    try {
      LOG(debug) << "Waiting for connections on port: " << acceptor_.local_endpoint().port();

      wait_for_connections();
      context_thread_ = std::thread([this]() {
        context_.run();
        LOG(warning) << "Server context thread finished";
      });

    } catch (std::exception& e) {
      LOG(debug) << "Exception thrown in server::start(): " << e.what();
      return false;
    }
    return true;
  }

  void stop() {
    context_.stop();
    if (context_thread_.joinable()) {
      context_thread_.join();
    }
  }

  void send_message(std::uint32_t client_id, std::string message) {
    auto client_it = connections_.find(client_id);
    if (client_it != std::end(connections_)) {
      auto connection = client_it->second;
      if (connection && connection->connected()) {
        LOG(debug) << "Sending message to client: " << client_id << ", which is: " << message;
        connection->send(std::move(message));
      } else {
        if (on_client_disconnect_) {
          on_client_disconnect_(connection);
        }
        connection.reset();
        connections_.erase(client_it);
      }
    } else {
      LOG(warning) << "There is no such client: " << client_id;
    }
  }

  void send_message_to_all(const message_type& message) {
    std::vector<std::uint32_t> to_remove;
    for (auto& connection_entry : connections_) {
      if (connection_entry.second && connection_entry.second->connected()) {
        connection_entry.second->send(message);
      } else {
        on_client_disconnect_(connection_entry.second);
        connection_entry.second.reset();
        to_remove.push_back(connection_entry.first);
      }
    }
    for (auto key : to_remove) {
      connections_.erase(key);
    }
  }

  auto number_of_clients() const {
    return connections_.size();
  }

  template <typename Callback>
  void on_client_connect(Callback callback) {
    on_client_connect_ = std::move(callback);
  }

  template <typename Callback>
  void on_client_accepted(Callback callback) {
    on_client_accepted_ = std::move(callback);
  }

  template <typename Callback>
  void on_client_disconnect(Callback callback) {
    on_client_disconnect_ = std::move(callback);
  }

  template <typename Callback>
  void on_message(Callback callback) {
    on_message_ = std::move(callback);
  }

  void update(std::size_t max_messages = -1) {
    size_t message_count = 0;
    while (message_count < max_messages && !messages_in_.empty()) {

      auto msg = messages_in_.front();
      messages_in_.pop();

      if (on_message_) {
        on_message_(msg.first->get_id(), msg.second);
      }

      ++message_count;
    }
  }

 private:
  void wait_for_connections() {
    acceptor_.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
      if (!ec) {
        LOG(debug) << "New client connected: " << socket.remote_endpoint().address().to_string();

        auto new_connection =
            std::make_shared<connection_type>(context_, std::move(socket), messages_in_);

        if (!on_client_connect_ || on_client_connect_(new_connection)) {
          auto client_id = id_counter_++;
          connections_.emplace(client_id, std::move(new_connection))
              .first->second->connect_to_client(client_id, on_client_accepted_);

        } else {
          LOG(debug) << "Client denied.";
        }

      } else {
        LOG(debug) << "Connection failed";
      }
      wait_for_connections();
    });
  }

  std::function<bool(const std::shared_ptr<connection_type>&)> on_client_connect_;
  std::function<void(const std::shared_ptr<connection_type>&)> on_client_disconnect_;
  std::function<void(std::shared_ptr<connection_type>)> on_client_accepted_;
  std::function<void(std::uint32_t client_id, const std::string&)> on_message_;

  std::unordered_map<std::uint32_t, std::shared_ptr<connection_type>> connections_;

  std::queue<my_owned_message_type> messages_in_;

  boost::asio::io_context context_;
  std::thread context_thread_;

  boost::asio::ip::tcp::acceptor acceptor_;

  std::uint32_t id_counter_{0};
};

}  // namespace networking
