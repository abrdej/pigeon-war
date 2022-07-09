#pragma once

#include <ctime>
#include <iostream>
#include <unistd.h>

std::string random_string(const int length) {
  static const char alphanum[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";

  std::string string;
  string.reserve(length);
  for (int i = 0; i < length; ++i) {
    string += alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return string;
}
