//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_BINDER_H
#define PIGEONWAR_BINDER_H

#include <atomic>
#include <functional>
#include <thread>
#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/asio/completion_condition.hpp>
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/next_prior.hpp>
#include <boost/lockfree/spsc_queue.hpp>

#include <external/json.hpp>

#include <utils/message_joiner.h>

using boost::asio::ip::tcp;

class websocket_connection : public std::enable_shared_from_this<websocket_connection> {
public:
    using connection_ptr = std::shared_ptr<websocket_connection>;

    static connection_ptr create(boost::asio::io_service& io_service) {
        return connection_ptr(new websocket_connection(io_service));
    }

    tcp::socket& socket() {
        return socket_;
    }

    void get_ws() {
        ws_ = std::make_unique<boost::beast::websocket::stream<tcp::socket>>(std::move(socket_));
        ws_->binary(true);
        ws_->async_accept_ex([](auto& m) {
                                 m.insert(boost::beast::http::field::sec_websocket_protocol, "binary");
                             },
                             [this](const boost::system::error_code& ec) {
                                 if (ec) {
                                     std::cout << ec.message() << "\n";
                                 }

                                 start_reading();
                                 initial_handler();
                             });
    }

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

    void start_reading() {
        boost::asio::async_read_until(*ws_,
                                      buffer,
                                      "\n",
                                      [this](const boost::system::error_code& error,
                                             size_t bytes_transferred) {

                                          if (error) {
                                              std::cout << "error: " << error.message() << "\n";
                                          }

                                          std::string message_data(boost::asio::buffer_cast<char const*>(
                                                  boost::beast::buffers_front(buffer.data())),
                                                                   boost::asio::buffer_size(buffer.data()));

                                          auto messages = joiner.add_message_data(message_data);

                                          for (auto&& message : messages) {
                                              read_handler(message);
                                          }

                                          buffer.consume(buffer.size() + 1);

                                          start_reading();
                                      });
    }

    void send(const std::string& message) {
//        boost::asio::async_write(socket_, boost::asio::buffer(message), boost::asio::transfer_all(),
//                                 [this](const boost::system::error_code& error, size_t bytes_transferred) {
//                                     handle_write(error, bytes_transferred);
//                                 });
        //ws_->binary(true);

        boost::system::error_code er;
        ws_->write(boost::asio::buffer(message), er);
        if (er) {
            std::cout << "dfdsfdsf: " << er.message() << "\n";
        }
        //ws_->binary(false);


//                                 [this](const boost::system::error_code& error, size_t bytes_transferred) {
//                                     handle_write(error, bytes_transferred);
//                                 });


//        using namespace boost::beast::websocket;
//
//        stream<boost::asio::ip::tcp::socket&> ws(socket_);
//        ws.handshake("127.0.0.1", "/");
//        ws.async_write(boost::asio::buffer("Hello, world\n"),
//                       [this](const boost::system::error_code& error, size_t bytes_transferred) {
//                           std::cout << "writed\n";
//                       });
    }

private:
    explicit websocket_connection(boost::asio::io_service& io_service)
    : socket_(io_service)
            {
            }

    void handle_write(const boost::system::error_code& /*error*/,
                      size_t /*bytes_transferred*/)
    {
    }

    tcp::socket socket_;
    std::unique_ptr<boost::beast::websocket::stream<tcp::socket>> ws_;
    boost::asio::streambuf buffer;
    message_joiner joiner{"\n"};
};

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
    using connection_ptr = std::shared_ptr<tcp_connection>;

    static connection_ptr create(boost::asio::io_service& io_service) {
        return connection_ptr(new tcp_connection(io_service));
    }

    tcp::socket& socket() {
        return socket_;
    }

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

    void send_initial_message() {
        initial_handler();
    }

    void start_reading() {

        boost::asio::async_read_until(socket_,
                                      buffer,
                                      "\n",
                                      [this](const boost::system::error_code& error,
                                                      size_t bytes_transferred) {

                                          if (error) {
                                              std::cout << "error: " << error.message() << "\n";
                                          }

                                          std::string message_data(boost::asio::buffer_cast<char const*>(
                                                  boost::beast::buffers_front(buffer.data())),
                                                             boost::asio::buffer_size(buffer.data()));

                                          auto messages = joiner.add_message_data(message_data);

                                          for (auto&& message : messages) {
                                              read_handler(message);
                                          }

                                          buffer.consume(buffer.size() + 1);
                                          start_reading();
                                      });
    }

    void send(const std::string& message) {
        boost::asio::write(socket_, boost::asio::buffer(message), boost::asio::transfer_all());
    }

private:
    explicit tcp_connection(boost::asio::io_service& io_service)
            : socket_(io_service)
    {
    }

    tcp::socket socket_;
    boost::asio::streambuf buffer;
    message_joiner joiner{"\n"};
};

class tcp_server {

    using json_data_type = nlohmann::json;
    using callback_type = std::function<void(json_data_type&)>;

    boost::asio::io_service io_service;

    tcp::endpoint endpoint;
    tcp::endpoint websocket_endpoint;
    tcp::acceptor acceptor_;
    tcp::acceptor websocket_acceptor_;
    std::vector<tcp_connection::connection_ptr> connections;

    const std::uint32_t port;

	boost::lockfree::spsc_queue<std::string, boost::lockfree::capacity<30>> messages_to_process;

    std::function<void(std::uint32_t)> initial_func;
	std::unordered_map<std::string, callback_type> callbacks;
	std::thread working_thread;
	std::thread io_service_thread;
	std::atomic_bool is_running{false};

public:
	explicit tcp_server(unsigned short port)
            : port(port),
              endpoint(tcp::v4(), port),
              websocket_endpoint(tcp::v4(), port + 1),
              websocket_acceptor_(io_service, websocket_endpoint),
              acceptor_(io_service, endpoint) {
        boost::system::error_code ec;
        acceptor_.open(endpoint.protocol(), ec);
        start_accept();
    }

    void start_accept() {
        tcp_connection::connection_ptr new_connection =
                tcp_connection::create(acceptor_.get_io_service());

        acceptor_.async_accept(new_connection->socket(),
                               [this, new_connection](const boost::system::error_code& error) {
                                   handle_accept(new_connection, error);
                               });
    }

    void handle_accept(tcp_connection::connection_ptr new_connection,
                       const boost::system::error_code& error) {
        if (!error)
        {
            auto client_id = static_cast<std::uint32_t>(connections.size());

            new_connection->set_initial_handler([this, client_id]() {
                initial_func(client_id);
            });
            new_connection->set_reading_handler([this](const std::string& message) {
                handle_message(message);
            });
//            new_connection->get_ws();

			std::cout << "New client, next id: " << client_id << "\n";

            connections.emplace_back(new_connection);
            new_connection->send_initial_message();
            new_connection->start_reading();

            start_accept();
        }
    }

	void handle_message(const std::string& message) {
		messages_to_process.push(message);
	}

	void bind(const std::string& message_type, callback_type callback) {
		callbacks.insert(std::make_pair(message_type, callback));
	};

    void set_initial_message(std::function<void(std::uint32_t client_id)> func) {
        initial_func = std::move(func);
    }

	void send_notification(std::string message) {
		//messages_to_send.push(std::make_pair(std::numeric_limits<std::uint32_t>::max(), message));

        for (auto&& connection : connections) {
            connection->send(message + "\n");
        }
	}

	void send_notification_to(std::uint32_t index, std::string message) {
        std::cout << "send message to him: " << message << "\n";
        connections[index]->send(message + "\n");
	}

    // this is not thread safe?
	bool is_single_client() const {
		return connections.size() == 1;
	}

	void run() {

		is_running = true;

        io_service_thread = std::thread([this]() {
           io_service.run();
        });

        int counter = 0;

        while (is_running) {

            std::string message;
            while (messages_to_process.pop(message)) {

                //auto pos = message.find("{");
                //message.erase(0, pos);

                std::cout << "message: " << message << "\n";

                json_data_type data;

                try {
                    data = json_data_type::parse(message);

                    std::cout << "data: \n" << data.dump() << "\n";

                    for (auto &&callback_pack : callbacks) {
                        if (data.count(callback_pack.first)) {
                            std::cout << "call callback for message: " << callback_pack.first << "\n";
                            callback_pack.second(data[callback_pack.first]);
                        }
                    }

                } catch (...) {
                    std::cout << "json parse error!\n";
                    std::cout << "in: " << message << "\n";
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
        io_service_thread.join();
	}

	void close() {
		is_running = false;
		working_thread.join();
//		io_service_thread.join();
	}

    void wait() {
        //working_thread.join();
		io_service_thread.join();
    }
};

#endif //PIGEONWAR_BINDER_H
