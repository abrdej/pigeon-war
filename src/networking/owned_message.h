#pragma once

#include <memory>

#include <networking/message.h>

namespace networking {

template <typename connection_type>
using owned_message_type = std::pair<std::shared_ptr<connection_type>, message_type>;

}  // namespace networking
