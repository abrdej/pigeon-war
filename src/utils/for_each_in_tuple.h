#pragma once

#include <tuple>

namespace detail {
template <std::int32_t... Is>
struct seq {};

template <std::int32_t N, std::int32_t... Is>
struct gen_seq : gen_seq<N - 1, N - 1, Is...> {};

template <std::int32_t... Is>
struct gen_seq<0, Is...> : seq<Is...> {};
}  // namespace detail

namespace detail {
template <typename T, typename F, std::int32_t... Is>
void for_each(T&& t, F f, seq<Is...>) {
  auto l = {(f(std::get<Is>(t)), 0)...};
}
}  // namespace detail

template <typename... Ts, typename F>
void for_each_in_tuple(std::tuple<Ts...> const& t, F f) {
  detail::for_each(t, f, detail::gen_seq<sizeof...(Ts)>());
}

template <typename... Ts, typename F>
void for_each_in_tuple(std::tuple<Ts...>& t, F f) {
  detail::for_each(t, f, detail::gen_seq<sizeof...(Ts)>());
}
