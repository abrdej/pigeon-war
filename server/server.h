//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_BINDER_H
#define PIGEONWAR_BINDER_H

#include <unordered_map>
#include <functional>
#include <thread>
#include <atomic>
#include <boost/next_prior.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <common/message_types.h>
#include "packets_makers.h"
#include "components/damage_taker.h"
#include "json.hpp"
#include "message_joiner.h"

#include <boost/asio.hpp>
#include <boost/asio/completion_condition.hpp>

//#include <boost/beast.hpp>

using boost::asio::ip::tcp;

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
    using connection_ptr = std::shared_ptr<tcp_connection>;

    static connection_ptr create(boost::asio::io_service& io_service) {
        return connection_ptr(new tcp_connection(io_service));
    }

    tcp::socket& socket() {
        return socket_;
    }

	template <typename Handler>
    void start_reading_from(Handler handler) {
        boost::asio::async_read_until(socket_,
                                      buffer,
                                      "\n",
                                      [this, handler](const boost::system::error_code& error,
                                                      size_t bytes_transferred) {

                                          std::istream istream(&buffer);
                                          std::string message_data(std::istreambuf_iterator<char>(istream), {});

                                          auto messages = joiner.add_message_data(message_data);

                                          for (auto&& message : messages) {
                                              std::cout << message << "\n";
                                              handler(message);
                                          }

                                          start_reading_from(handler);
                                      });
    }

    void send(const std::string& message) {
        boost::asio::async_write(socket_, boost::asio::buffer(message), boost::asio::transfer_all(),
                                 [this](const boost::system::error_code& error, size_t bytes_transferred) {
                                     handle_write(error, bytes_transferred);
                                 });

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
    explicit tcp_connection(boost::asio::io_service& io_service)
            : socket_(io_service)
    {
    }

    void handle_write(const boost::system::error_code& /*error*/,
                      size_t /*bytes_transferred*/)
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

    tcp::acceptor acceptor_;
    std::vector<tcp_connection::connection_ptr> connections;

    const std::uint32_t port;

	boost::lockfree::spsc_queue<std::string, boost::lockfree::capacity<30>> messages_to_process;
    boost::lockfree::spsc_queue<std::pair<std::uint32_t, std::string>, boost::lockfree::capacity<30>> messages_to_send;



    std::function<void(std::uint32_t)> initial_func;
	std::unordered_map<std::string, callback_type> callbacks;
	std::thread working_thread;
	std::thread io_service_thread;
	std::atomic_bool is_running{false};


public:
	explicit tcp_server(std::uint32_t port)
            : port(port),
              acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
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
            new_connection->start_reading_from([this](const std::string& message) {
				handle_message(message);
			});

			auto client_id = static_cast<std::uint32_t>(connections.size());

			std::cout << "New client, next id: " << client_id << "\n";

            connections.emplace_back(new_connection);
			initial_func(client_id);

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
		//messages_to_send.push(std::make_pair(index, message));

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

        while (is_running) {

            std::string message;
            while (messages_to_process.pop(message)) {

                std::cout << "message: " << message << "\n";

                json_data_type data;

                try {
                    data = json_data_type::parse(message);

                } catch (...) {
                    std::cout << "json parse error!\n";
                    std::cout << "in: " << message << "\n";
                }

                std::cout << "data: \n" << data.dump() << "\n";

                for (auto &&callback_pack : callbacks) {
                    if (data.count(callback_pack.first)) {
                        std::cout << "call callback for message: " << callback_pack.first << "\n";
                        callback_pack.second(data[callback_pack.first]);
                    }
                }
            }
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
