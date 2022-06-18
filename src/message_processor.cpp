#include <message_processor.h>

void message_processor::bind(const std::string& message_type, callback_type callback) {
  callbacks_.emplace(message_type, std::move(callback));
};

void message_processor::execute(const std::string& message) {
  json_data_type data;

  try {
    data = json_data_type::parse(message);
    execute(data);
  } catch (std::exception& e) {
    LOG(error) << "message parsing error in: " << message << ", what: " << e.what();
  }
}

void message_processor::execute(json_data_type data) {
  for (auto&& callback_entry : callbacks_) {
    if (data.count(callback_entry.first)) {
      LOG(debug) << "calling callback for data: " << callback_entry.first;
      callback_entry.second(data[callback_entry.first]);
    }
  }
}
