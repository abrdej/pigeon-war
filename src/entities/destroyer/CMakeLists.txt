configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

add_library(destroyer SHARED
  armor.cpp
  blow_the_ax.cpp
  destroyer.cpp)
target_link_libraries(destroyer turn_based)
target_include_directories(destroyer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
