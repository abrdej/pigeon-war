add_library(networking SHARED
  server.cpp)
target_include_directories(networking PUBLIC ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/external)
#target_link_libraries(networking PRIVATE turn_based) # TODO: extract logging from turn based?
target_link_libraries(networking PUBLIC turn_based) # TODO: extract logging from turn based?
