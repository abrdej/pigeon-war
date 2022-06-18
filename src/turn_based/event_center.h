#include <boost/signals2.hpp>

#include <turn_based/events.h>

using event_signal = boost::signals2::signal<void()>;
using event_slot = event_signal::slot_type;

class event_center {
 public:
  void emit(events event) {
    auto it = signals_.find(event);
    if (it != std::end(signals_)) {
      it->second();
    }
  }

  void register_on(events event, const event_slot& callback) {
    signals_[event].connect(callback);
  }

 private:
  std::unordered_map<events, event_signal> signals_;
};
