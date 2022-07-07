add_library(sniper SHARED
  hypnosis.cpp
  sniper.cpp
  sniper_shot.cpp)
target_link_libraries(sniper turn_based)
target_include_directories(sniper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
