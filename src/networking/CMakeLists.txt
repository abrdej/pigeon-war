add_library(networking SHARED
  server.cpp)
target_include_directories(networking PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/external)
target_link_libraries(networking PUBLIC logging)
