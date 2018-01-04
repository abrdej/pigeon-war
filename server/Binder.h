//
// Created by abrdej on 04.01.18.
//

#ifndef PIGEONWAR_BINDER_H
#define PIGEONWAR_BINDER_H

#include <unordered_map>
#include <functional>
#include <thread>
#include <atomic>
#include <SFML/Network.hpp>

//
//namespace detail
//{
//template<int... Is>
//struct seq { };
//
//template<int N, int... Is>
//struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };
//
//template<int... Is>
//struct gen_seq<0, Is...> : seq<Is...> { typedef seq<Is...> type; };
//
//}
//
//namespace detail
//{
//template<typename T, typename F, int... Is>
//void for_each(T&& t, F f, seq<Is...>)
//{
//	auto l = { (f(std::get<Is>(t)), 0)... };
//}
//}
//
//template<typename... Ts, typename F>
//void for_each_in_tuple(std::tuple<Ts...> const& t, F f)
//{
//	detail::for_each(t, f, detail::gen_seq<sizeof...(Ts)>());
//}
//
////template<int ...> struct seq {};
////
////template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};
////
////template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };
//
//template <typename R, typename ...Args>
//struct save_it_for_later
//{
//	std::tuple<Args...> params;
//	R (*func)(Args...);
//
//	R delayed_dispatch()
//	{
//		return callFunc(typename detail::gen_seq<sizeof...(Args)>::type());
//	}
//
//	template<int ...S>
//	R callFunc(detail::seq<S...>)
//	{
//		return func(std::get<S>(params) ...);
//	}
//};

struct Binder {

	std::unordered_map<std::string, std::function<sf::Packet(sf::Packet&)>> callbacks;
	std::thread working_thread;
	std::atomic_bool is_running;

	std::atomic_bool end_turn_flag;

	sf::SocketSelector selector;

	sf::TcpListener listener;

	std::vector<std::shared_ptr<sf::TcpSocket>> clients;

	Binder() {

		end_turn_flag = false;

		if (listener.listen(8081) != sf::Socket::Done) {
			std::cout << "Listener error\n";
		}

		selector.add(listener);
	}

	void bind(const std::string& name, std::function<sf::Packet(sf::Packet&)> func) {
		callbacks.insert(std::make_pair(name, func));
	};

	void end_turn() {
		end_turn_flag = true;
	}

	void start() {

		is_running = true;

		working_thread = std::thread([this]() {

			while (is_running) {

				if (selector.wait()) {

					if (selector.isReady(listener)) {

						auto client = std::make_shared<sf::TcpSocket>();

						if (listener.accept(*client) != sf::Socket::Done)
						{
							std::cout << "Error\n";
						}

						clients.emplace_back(client);
						selector.add(*client);

					}

					for (auto&& client : clients) {
						if (selector.isReady(*client)) {

							sf::Packet request_packet;
							client->receive(request_packet);

							std::string request_name;
							request_packet >> request_name;

							auto result_packet = callbacks.at(request_name)(request_packet);

							client->send(result_packet);

						}
					}
				}

				if (end_turn_flag) {
					for (auto&& client : clients) {

						sf::Packet request_packet;

						request_packet << "end turn";

						client->send(request_packet);
					}
					end_turn_flag = false;
				}
			}
		});
	}

	void close() {
		is_running = false;
		working_thread.join();
	}
};

#endif //PIGEONWAR_BINDER_H
