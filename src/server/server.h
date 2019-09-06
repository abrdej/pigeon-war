#pragma once

#include <atomic>
#include <functional>
#include <thread>
#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/next_prior.hpp>

#include <external/json.hpp>

#include <utils/message_joiner.h>

using boost::asio::ip::tcp;

class websocket_connection : public std::enable_shared_from_this<websocket_connection> {
 public:
  using executor_type = tcp::socket::executor_type;
  using connection_ptr = std::shared_ptr<websocket_connection>;

  static connection_ptr create(executor_type executor);

  tcp::socket& socket();

  void get_ws();

  std::function<void(const std::string&)> read_handler;
  std::function<void()> initial_handler;

  template <typename Handler>
  void set_reading_handler(Handler handler) {
    read_handler = handler;
  }

  template <typename Handler>
  void set_initial_handler(Handler handler) {
    initial_handler = handler;
  }

  void start_reading();
  void send(const std::string& message);

 private:
  explicit websocket_connection(executor_type executor);
  void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);

  tcp::socket socket_;
  std::unique_ptr<boost::beast::websocket::stream<tcp::socket>> ws_;
  boost::asio::streambuf buffer;
  message_joiner joiner{"\n"};
};

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
 public:
  using connection_ptr = std::shared_ptr<tcp_connection>;

  static connection_ptr create(boost::asio::io_service& io_service);

  tcp::socket& socket();

  std::function<void(const std::string&)> read_handler;
  std::function<void()> initial_handler;

  template <typename Handler>
  void set_reading_handler(Handler handler) {
    read_handler = handler;
  }

  template <typename Handler>
  void set_initial_handler(Handler handler) {
    initial_handler = handler;
  }

  void send_initial_message();

  void start_reading();

  void send(const std::string& message);

 private:
  explicit tcp_connection(boost::asio::io_service& io_service);

  tcp::socket socket_;
  boost::asio::streambuf buffer;
  message_joiner joiner{"\n"};
};

class tcp_server {
  using Connection = websocket_connection;

  using json_data_type = nlohmann::json;
  using callback_type = std::function<void(json_data_type&)>;

  boost::asio::io_service io_service;

  tcp::endpoint endpoint;
  tcp::endpoint websocket_endpoint;
  tcp::acceptor acceptor_;
  tcp::acceptor websocket_acceptor_;
  std::vector<Connection::connection_ptr> connections;

  const std::uint32_t port;

  boost::lockfree::spsc_queue<std::string, boost::lockfree::capacity<30>> messages;

  std::function<void(std::uint32_t)> initial_func;
  std::unordered_map<std::string, callback_type> callbacks;

  std::thread working_thread;
  std::thread io_service_thread;
  std::atomic_bool is_running{false};

  void start_accept();
  void handle_accept(Connection::connection_ptr new_connection,
                     const boost::system::error_code& error);
  void handle_message(const std::string& message);
  std::uint32_t get_new_client_id();

 public:
  explicit tcp_server(unsigned short port);

  void bind(const std::string& message_type, callback_type callback);
  void set_initial_message(std::function<void(std::uint32_t client_id)> func);
  void send_notification(std::string message);
  void send_notification_to(std::uint32_t index, std::string message);

  // this is not thread safe?
  bool is_single_client() const;
  void run();
  void close();
  void wait();
};
