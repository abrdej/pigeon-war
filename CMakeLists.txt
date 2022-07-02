cmake_minimum_required(VERSION 3.5.1)
project(pigeon_war)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-fPIC)

configure_file(src/config.h.in ${CMAKE_SOURCE_DIR}/src/config.h @ONLY)

find_package(Boost COMPONENTS program_options log system REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(src/logging)
add_subdirectory(src/turn_based)
add_subdirectory(src/networking)

## entities plugins
add_subdirectory(src/entities/environment)
add_subdirectory(src/entities/native)
add_subdirectory(src/entities/saberhand)
add_subdirectory(src/entities/samurai_rat)
add_subdirectory(src/entities/saurian)
add_subdirectory(src/entities/shooter)
add_subdirectory(src/entities/wolf)
add_subdirectory(src/entities/destroyer)

## scenario plugins
add_subdirectory(src/scenarios/skirmish)
add_subdirectory(src/scenarios/saurian_web)
add_subdirectory(src/scenarios/wolves_dinner)

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
