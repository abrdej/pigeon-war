add_library(native SHARED
  counterattack.cpp
  drain.cpp
  native.cpp)
target_link_libraries(native turn_based)
target_include_directories(native PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
