#pragma once

#include <memory>

#include <boost/process.hpp>

#include <logging/logger.h>

// encapsulates executable which is boost::process::child with RAII using unique_ptr.

using executable_process = boost::process::child;

struct executable_terminator {
  void operator()(executable_process* p) {
    std::error_code ec;
    p->terminate(ec);
    LOG(debug) << "terminated executable with error code: " << ec.message();
    delete p;
  }
};

using executable_ptr = std::unique_ptr<executable_process, executable_terminator>;

template <typename... Args>
executable_ptr make_executable(const boost::filesystem::path& executable_path, Args&& ...args) {
  return executable_ptr(new executable_process(executable_path,
                                               std::forward<Args>(args)...,
                                               boost::process::std_out > stdout,
                                               boost::process::std_err > stderr,
                                               boost::process::std_in < stdin));
}
