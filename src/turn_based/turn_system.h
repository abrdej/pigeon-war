#pragma once

#include <functional>

#include <boost/signals2.hpp>

#include <turn_based/game.h>
#include <turn_based/managers/players_manager.h>

enum class frequency_types {
  every_turn, every_two_turns_from_this, every_two_turns_from_next, after_n_rounds, after_n_turns
};

using turn_scoped_connection = boost::signals2::scoped_connection;
using turn_connection = boost::signals2::connection;
using turn_signal = boost::signals2::signal<void()>;
using turn_slot = turn_signal::slot_type;
using extended_turn_slot = turn_signal::extended_slot_type;

struct turn_callback_info {
  bool is_ending{false};
  turn_connection connection;
};

using turn_callback = std::function<void()>;
using extended_turn_callback = std::function<void(turn_callback_info&)>;

/**
 * @brief Controls turns in the game and handles turn-related callbacks.
 */
class turn_system {
  class turn_callback_wrapper {
   public:
    turn_callback_wrapper(const frequency_types& frequency,
                          int32_t duration,
                          extended_turn_callback callback)
        : frequency_(frequency), duration_(duration), number_of_calls_(0), callback_(std::move(callback)) {}

    void operator()(const turn_connection& conn) {
      if (frequency_ == frequency_types::every_turn) {
        turn_callback_info info{duration_ && ++number_of_calls_ == duration_, conn};
        callback_(info);
        if (info.is_ending) {
          conn.disconnect();
        }

      } else if (frequency_ == frequency_types::every_two_turns_from_this) {
        turn_callback_info info{duration_ && ++number_of_calls_ == duration_, conn};
        callback_(info);
        frequency_ = frequency_types::every_two_turns_from_next;
        if (info.is_ending) {
          conn.disconnect();
        }

      } else if (frequency_ == frequency_types::every_two_turns_from_next) {
        frequency_ = frequency_types::every_two_turns_from_this;

      } else if (frequency_ == frequency_types::after_n_rounds) {
        if (++number_of_calls_ == duration_ * 2) {
          turn_callback_info info{true, conn};
          callback_(info);
          conn.disconnect();
        }

      } else if (frequency_ == frequency_types::after_n_turns) {
        if (++number_of_calls_ == duration_) {
          turn_callback_info info{true, conn};
          callback_(info);
          conn.disconnect();
        }
      }
    }

   private:
    frequency_types frequency_;
    int32_t duration_;
    int32_t number_of_calls_;
    extended_turn_callback callback_;
  };

 public:
  void end_turn();

  void on_turn(std::uint32_t n, const turn_callback& callback);

  turn_scoped_connection set_callback(const frequency_types& frequency,
                                      int32_t duration,
                                      const extended_turn_callback& callback) {
    return {next_turn_signal_.connect_extended(turn_callback_wrapper(frequency,
                                                                     duration,
                                                                     callback))};
  }

  turn_scoped_connection set_callback(const frequency_types& frequency,
                                      int32_t duration,
                                      const turn_callback& callback) {
    return {next_turn_signal_.connect_extended(
        turn_callback_wrapper(frequency,
                              duration,
                              [callback](turn_callback_info&) { return callback(); }))};
  }

 private:
  std::uint32_t this_turn_{0};
  std::unordered_multimap<std::uint32_t, turn_callback> on_turn_scheduled_;
  turn_signal next_turn_signal_;
};

template <typename Callback>
inline auto make_every_turn_callback_holder(std::int32_t duration, Callback callback) {
  return game::get<turn_system>().set_callback(frequency_types::every_turn, duration, callback);
}

template <typename Callback>
inline void set_every_turn_callback(std::int32_t duration, Callback callback) {
  game::get<turn_system>().set_callback(frequency_types::every_turn, duration, callback).release();
}

template <typename Callback>
inline auto make_every_two_turns_from_next_callback_holder(std::int32_t duration, Callback callback) {
  return game::get<turn_system>().set_callback(frequency_types::every_two_turns_from_next, duration, callback);
}

template <typename Callback>
inline void set_every_two_turns_from_next_callback(std::int32_t duration, Callback callback) {
  game::get<turn_system>().set_callback(frequency_types::every_two_turns_from_next, duration, callback).release();
}

template <typename Callback>
inline auto make_after_n_round_callback_holder(std::int32_t duration, Callback callback) {
  return game::get<turn_system>().set_callback(frequency_types::after_n_rounds, duration, callback);
}

template <typename Callback>
inline auto make_after_n_turns_callback_holder(std::int32_t duration, Callback callback) {
  return game::get<turn_system>().set_callback(frequency_types::after_n_turns, duration, callback);
}

template <typename Callback>
inline void set_after_n_round_callback(std::int32_t duration, Callback callback) {
  game::get<turn_system>().set_callback(frequency_types::after_n_rounds, duration, callback).release();
}

class turn_callback_helper {
 protected:
  template <typename Callback>
  void on_every_turn(Callback callback) {
    on_every_turn_holder_ = std::move(game::get<turn_system>().set_callback(frequency_types::every_turn, 0, callback));
  }

  template <typename Callback>
  void on_every_two_turns_from_this(Callback callback) {
    on_every_two_turns_from_this_holder_ =
        std::move(game::get<turn_system>().set_callback(frequency_types::every_two_turns_from_this, 0, callback));
  }

  template <typename Callback>
  void after_player_turn(entity_id_t entity_id, Callback callback) {
    after_player_turn_holder_ =
        std::move(game::get<turn_system>().set_callback(frequency_types::every_turn, 0, [entity_id, callback]() {
          if (game::get<players_manager>().active_player_entity(entity_id)) {
            callback();
          }
        }));
  }

  template <typename Callback>
  void on_every_two_turns_from_next(Callback callback) {
    on_every_two_turns_from_next_holder_ =
        std::move(game::get<turn_system>().set_callback(frequency_types::every_two_turns_from_next, 0, callback));
  }

 private:
  turn_scoped_connection on_every_turn_holder_;
  turn_scoped_connection on_every_two_turns_from_this_holder_;
  turn_scoped_connection on_every_two_turns_from_next_holder_;
  turn_scoped_connection after_player_turn_holder_;
};
