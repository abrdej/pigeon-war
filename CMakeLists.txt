cmake_minimum_required(VERSION 3.5.1)
project(pigeon_war)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-fPIC)

configure_file(src/config.h.in ${CMAKE_SOURCE_DIR}/src/config.h @ONLY)

find_package(Boost COMPONENTS program_options log log_setup system REQUIRED)
find_package(TBB REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(external/type_safe)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/utilities.cmake)

add_subdirectory(src/logging)
add_subdirectory(src/turn_based)
add_subdirectory(src/networking)

## entities plugins
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/entities.cmake)
add_subdirectory(src/entities/environment)
add_subdirectory(src/entities/golem)
add_subdirectory(src/entities/monk)
add_subdirectory(src/entities/native)
add_subdirectory(src/entities/saberhand)
add_subdirectory(src/entities/samurai_rat)
add_subdirectory(src/entities/saurian)
add_subdirectory(src/entities/shooter)
add_subdirectory(src/entities/sniper)
add_subdirectory(src/entities/wolf)
add_subdirectory(src/entities/destroyer)

## scenario plugins
add_subdirectory(src/scenarios/skirmish)
add_subdirectory(src/scenarios/saurian_web)
add_subdirectory(src/scenarios/wolves_dinner)
add_subdirectory(src/scenarios/wolfs_night)

set(SOURCE_FILES
  src/get_button_description.cpp
  src/get_effect_description.cpp
  src/get_entities.cpp
  src/get_entity_names.cpp
  src/get_game_state.cpp
  src/message_processor.cpp
)

add_executable(pigeon_war src/main.cpp ${SOURCE_FILES})
target_link_libraries(pigeon_war turn_based networking)

add_executable(tester src/tester.cpp)
target_link_libraries(tester turn_based)

add_subdirectory(src/lobby)

add_executable(server_test src/server_test.cpp)
target_link_libraries(server_test networking)

add_executable(client_test src/client_test.cpp)
target_link_libraries(client_test networking)
