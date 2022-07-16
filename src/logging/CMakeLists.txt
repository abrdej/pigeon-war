add_library(logging SHARED
  logger.cpp)
target_include_directories(logging PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(logging PUBLIC Boost::log Boost::log_setup pthread)
