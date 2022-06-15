#include "server.h"

#include <core/logger.h>

using boost::asio::ip::tcp;

websocket_connection::connection_ptr websocket_connection::create(executor_type executor) {
  return connection_ptr(new websocket_connection(executor));
}

tcp::socket& websocket_connection::socket() { return socket_; }

/// Returns `true` if the request indicates a WebSocket upgrade
// bool is_upgrade(const boost::beast::http::request_header& req)
//{
//    if(req.method != "GET")
//        return false;
//    if(req.version < 11)
//        return false;
//    if(! boost::beast::http::is_upgrade(req))
//        return false;
//    if(! boost::beast::http::token_list{req.fields["Upgrade"]}.exists("websocket"))
//        return false;
//    if( req.fields["Sec-WebSocket-Version"] != "13")
//        return false;
//    return true;
//}

void websocket_connection::get_ws() {
  ws_ = std::make_unique<boost::beast::websocket::stream<tcp::socket>>(std::move(socket_));
  // ws_->binary(true);
  //    ws_->async_accept_ex([](auto& m) {
  //                             m.insert(boost::beast::http::field::sec_websocket_protocol,
  //                             "binary");
  //                         },
  //                         [this](const boost::system::error_code& ec) {
  //                             if (ec) {
  //                                 LOG(debug) << "get ws: " << ec.message() << "\n";
  //                             }
  //
  //                             start_reading();
  //                             initial_handler();
  //                         });
  ws_->async_accept([me = shared_from_this()](const boost::system::error_code& error) {
    if (error) {
      LOG(debug) << "get ws: " << error.message() << "\n";
      throw error;
    }

    me->start_reading();
    me->initial_handler();
  });
}

void websocket_connection::start_reading() {
  boost::asio::async_read_until(
      *ws_, buffer, "\n",
      [me = shared_from_this()](const boost::system::error_code& error, size_t bytes_transferred) {
        if (error) {
          LOG(debug) << "error: " << error.message() << "\n";
          throw error;
        }

        std::string message_data(
            boost::asio::buffer_cast<char const*>(boost::beast::buffers_front(me->buffer.data())),
            boost::asio::buffer_size(me->buffer.data()));

        auto messages = me->joiner.add_message_data(message_data);

        for (auto&& message : messages) {
          me->read_handler(message);
        }

        me->buffer.consume(me->buffer.size() + 1);

        me->start_reading();
      });
}

void websocket_connection::send(const std::string& message) {
  boost::system::error_code er;
  ws_->write(boost::asio::buffer(message), er);
  if (er) {
    LOG(debug) << "dfdsfdsf: " << er.message() << "\n";
    throw er;
  }
  // ws_->binary(false);
}

websocket_connection::websocket_connection(executor_type executor) : socket_(executor) {}

void websocket_connection::handle_write(const boost::system::error_code& /*error*/,
                                        size_t /*bytes_transferred*/) {}

tcp_connection::connection_ptr tcp_connection::create(boost::asio::io_service& io_service) {
  return connection_ptr(new tcp_connection(io_service));
}

tcp::socket& tcp_connection::socket() { return socket_; }

void tcp_connection::send_initial_message() { initial_handler(); }

void tcp_connection::start_reading() {
  boost::asio::async_read_until(
      socket_, buffer, "\n",
      [this](const boost::system::error_code& error, size_t bytes_transferred) {
        if (error) {
          LOG(debug) << "error: " << error.message() << "\n";
        }

        std::string message_data(
            boost::asio::buffer_cast<char const*>(boost::beast::buffers_front(buffer.data())),
            boost::asio::buffer_size(buffer.data()));

        LOG(debug) << "message_data: " << message_data << "\n";

        auto messages = joiner.add_message_data(message_data);

        for (auto&& message : messages) {
          read_handler(message);
        }

        buffer.consume(buffer.size() + 1);
        start_reading();
      });
}

void tcp_connection::send(const std::string& message) {
  boost::asio::write(socket_, boost::asio::buffer(message), boost::asio::transfer_all());
}

tcp_connection::tcp_connection(boost::asio::io_service& io_service) : socket_(io_service) {}

tcp_server::tcp_server(unsigned short port)
    : port(port),
      endpoint(tcp::v4(), port),
      websocket_endpoint(tcp::v4(), port + 1),
      websocket_acceptor_(io_service, websocket_endpoint),
      acceptor_(io_service, endpoint) {
  boost::system::error_code ec;
  acceptor_.open(endpoint.protocol(), ec);
  start_accept();

  LOG(debug) << "Starting server on port: " << port << "\n";
}

void tcp_server::start_accept() {
  Connection::connection_ptr new_connection = Connection::create(acceptor_.get_executor());

  acceptor_.async_accept(new_connection->socket(),
                         [this, new_connection](const boost::system::error_code& error) {
                           handle_accept(new_connection, error);
                         });
}

void tcp_server::handle_accept(Connection::connection_ptr new_connection,
                               const boost::system::error_code& error) {
  if (!error) {
    auto client_id = get_new_client_id();

    new_connection->set_initial_handler([this, client_id]() { initial_func(client_id); });
    new_connection->set_reading_handler(
        [this](const std::string& message) { handle_message(message); });
    new_connection->get_ws();

    LOG(debug) << "New client, next id: " << client_id << "\n";

    connections.emplace_back(new_connection);

    //        new_connection->send_initial_message();
    //        new_connection->start_reading();

    start_accept();
  }
}

std::uint32_t tcp_server::get_new_client_id() {
  return static_cast<std::uint32_t>(connections.size());
}

void tcp_server::handle_message(const std::string& message) { messages.push(message); }

void tcp_server::bind(const std::string& message_type, callback_type callback) {
  callbacks.insert(std::make_pair(message_type, callback));
};

void tcp_server::set_initial_message(std::function<void(std::uint32_t client_id)> func) {
  initial_func = std::move(func);
}

void tcp_server::send_notification(std::string message) {
  for (auto&& connection : connections) {
    connection->send(message + "\n");
  }
}

void tcp_server::send_notification_to(std::uint32_t index, std::string message) {
  LOG(debug) << "send message to him: " << message << "\n";
  connections[index]->send(message + "\n");
}

// this is not thread safe?
bool tcp_server::is_single_client() const { return connections.size() == 1; }

void tcp_server::run() {
  is_running = true;

  io_service_thread = std::thread([this]() { io_service.run(); });

  while (is_running) {
    std::string message;
    while (messages.pop(message)) {
      LOG(debug) << "message: " << message << "\n";

      json_data_type data;

      try {
        data = json_data_type::parse(message);

        LOG(debug) << "data: \n" << data.dump() << "\n";

        for (auto&& callback_pack : callbacks) {
          if (data.count(callback_pack.first)) {
            LOG(debug) << "call callback for message: " << callback_pack.first << "\n";
            callback_pack.second(data[callback_pack.first]);
          }
        }

      } catch (...) {
        LOG(debug) << "json parse error!\n";
        LOG(debug) << "in: " << message << "\n";
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
  }
  io_service_thread.join();
}

void tcp_server::close() {
  is_running = false;
  working_thread.join();
  //		io_service_thread.join();
}

void tcp_server::wait() {
  // working_thread.join();
  io_service_thread.join();
}
