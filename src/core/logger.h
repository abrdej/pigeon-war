#pragma once

#include <boost/exception/all.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/exception.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/utility/setup/console.hpp>

namespace logging = boost::log;

using logger_t = logging::sources::severity_logger<logging::trivial::severity_level>;

BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(my_logger, logger_t) {
  namespace logging = boost::log;
  logger_t lg;
  return lg;
}

#define LOG(LEVEL) BOOST_LOG_SEV(my_logger::get(), logging::trivial::LEVEL)

#define LOG_LOCATION(LEVEL)      \
  BOOST_LOG_SEV(my_logger::get(), logging::trivial::LEVEL)     \
    << boost::log::add_value("Line", __LINE__)          \
    << boost::log::add_value("File", __FILE__)          \
    << boost::log::add_value("Function", __FUNCTION__)

void init_logging();
