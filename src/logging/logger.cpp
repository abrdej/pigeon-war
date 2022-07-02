#include <logging/logger.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>
#include <boost/log/expressions/formatters/stream.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/phoenix/operator.hpp>

void init_logging() {
  namespace logging = boost::log;

  logging::add_console_log(
    std::cout,
    logging::keywords::format =
      (
        boost::log::expressions::stream
          << "["
          << boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S")
          << "] ["
          << boost::log::expressions::format_named_scope("Scope", logging::keywords::format = "%n")
          << "] " << boost::log::expressions::smessage
      ));

  logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::debug);
  logging::core::get()->add_global_attribute("Scope", logging::attributes::named_scope());
  logging::core::get()->add_global_attribute("TimeStamp", logging::attributes::local_clock());

//  logging::core::get()->add_global_attribute("Line", logging::attributes::mutable_constant<int>(5));
//  logging::core::get()->add_global_attribute("File", logging::attributes::mutable_constant<std::string>(""));
//  logging::core::get()->add_global_attribute("Function", logging::attributes::mutable_constant<std::string>(""));
}
