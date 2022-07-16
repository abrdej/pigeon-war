#include <logging/logger.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>
#include <boost/log/expressions/formatters/stream.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/log/utility/setup/file.hpp>

void init_logging() {
  namespace logging = boost::log;
//
//  logging::add_console_log(
//    std::cout,
//    logging::keywords::format =
//      (
//        boost::log::expressions::stream
//          << "["
//          << boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
//          << "] ["
//          << boost::log::expressions::format_named_scope("File", logging::keywords::format = "%s")
//          << "] " << boost::log::expressions::smessage
//      ));
//
//  logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::debug);
//  logging::core::get()->add_global_attribute("Scope", logging::attributes::named_scope());
//  logging::core::get()->add_global_attribute("TimeStamp", logging::attributes::local_clock());
//
//  logging::core::get()->add_global_attribute("Line", logging::attributes::mutable_constant<int>(5));
//  logging::core::get()->add_global_attribute("File", logging::attributes::mutable_constant<std::string>(""));
//  logging::core::get()->add_global_attribute("Function", logging::attributes::mutable_constant<std::string>(""));

  logging::add_common_attributes();

  logging::register_simple_filter_factory<logging::trivial::severity_level, char>("Severity");
  logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

  auto syslog_format(logging::expressions::stream
                         << "["
                         << logging::expressions::format_date_time<boost::posix_time::ptime>(
                             "TimeStamp",
                             "%Y-%m-%d %H:%M:%S") << "] ["
                         << logging::trivial::severity << "] ["
                         << logging::expressions::attr<std::string>("Filename") << ":"
                         << logging::expressions::attr<std::string>("Function") << ":"
                         << logging::expressions::attr<int>("Line") << "] "
                         << logging::expressions::smessage
  );

  logging::add_console_log(std::cout, logging::keywords::format = syslog_format);

  logging::add_file_log(logging::keywords::file_name  = "sys_%d_%m_%Y.%N.log",
                        logging::keywords::format = syslog_format);
}
