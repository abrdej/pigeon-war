#pragma once

#include <fstream>
#include <iostream>

#include <external/json.hpp>

#include <config.h>

template <typename T>
inline std::string to_string_wrapper(const T& x) {
  return std::to_string(x);
}

inline std::string to_string_wrapper(const std::string& x) { return x; }

template <typename T>
void str_replace(std::string& text, const std::string& from, const T& to) {
  try {
    text.replace(text.find(from), from.length(), to_string_wrapper(to));

  } catch (const std::exception& e) {
    std::cerr << "str_replace exception: " << e.what();
  }
}

inline std::string get_desc(const std::string& ability_name) {
  std::ifstream ifs(resources_directory + "descriptions.json");
  nlohmann::json j = nlohmann::json::parse(ifs);

  std::string desc = j["descriptions"]["abilities"][ability_name];
  return desc;
}

inline std::string get_effect_desc(const std::string& effect) {
  std::ifstream ifs(resources_directory + "descriptions.json");
  nlohmann::json j = nlohmann::json::parse(ifs);

  std::string desc = j["descriptions"]["effects"][effect];
  return desc;
}

#define STRINGIZE(arg) STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2) CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2) CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2) arg1##arg2

#define FOR_EACH_1(what, x, ...) what(x)
#define FOR_EACH_2(what, x, ...) \
  what(x);                       \
  FOR_EACH_1(what, __VA_ARGS__);
#define FOR_EACH_3(what, x, ...) \
  what(x);                       \
  FOR_EACH_2(what, __VA_ARGS__);
#define FOR_EACH_4(what, x, ...) \
  what(x);                       \
  FOR_EACH_3(what, __VA_ARGS__);
#define FOR_EACH_5(what, x, ...) \
  what(x);                       \
  FOR_EACH_4(what, __VA_ARGS__);
#define FOR_EACH_6(what, x, ...) \
  what(x);                       \
  FOR_EACH_5(what, __VA_ARGS__);
#define FOR_EACH_7(what, x, ...) \
  what(x);                       \
  FOR_EACH_6(what, __VA_ARGS__);
#define FOR_EACH_8(what, x, ...) \
  what(x);                       \
  FOR_EACH_7(what, __VA_ARGS__);

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__)
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, x, ...) CONCATENATE(FOR_EACH_, N)(what, x, __VA_ARGS__)
#define FOR_EACH(what, x, ...) FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, x, __VA_ARGS__)

#define DESC_REPLACE(desc, name) \
  str_replace(desc, std::string("<") + #name + std::string(">"), name);

#define DESC_REPLACE_WITH_DESC(name) DESC_REPLACE(desc, name)

#define DEFINE_DESC(ability_name, ...)            \
  std::string hint() const override {             \
    auto desc = get_desc(#ability_name);          \
    FOR_EACH(DESC_REPLACE_WITH_DESC, __VA_ARGS__) \
    return std::move(desc);                       \
  }

#define DEFINE_DESC_ZERO(ability_name)   \
  std::string hint() const override {    \
    auto desc = get_desc(#ability_name); \
    return std::move(desc);              \
  }

#define DEFINE_DESC_ONE(ability_name, field) \
  std::string hint() const override {        \
    auto desc = get_desc(#ability_name);     \
    DESC_REPLACE_WITH_DESC(field)            \
    return std::move(desc);                  \
  }
