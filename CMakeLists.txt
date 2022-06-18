cmake_minimum_required(VERSION 3.5.1)
project(pigeon_war)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-fPIC)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

configure_file(src/config.h.in ${CMAKE_SOURCE_DIR}/src/config.h @ONLY)

find_package(Boost COMPONENTS log system REQUIRED)
find_package(GTest REQUIRED)

set(SOURCE_FILES
  src/turn_based/game_state.h
  src/impl/game_state/get_button_description.cpp
  src/impl/game_state/get_button_description.h
  src/impl/game_state/get_effect_description.cpp
  src/impl/game_state/get_effect_description.h
  src/impl/game_state/get_game_state.cpp
  src/impl/game_state/get_game_state.h
  src/impl/effects/aura_of_armor_effect.cpp
  src/impl/effects/aura_of_armor_effect.h
  src/impl/effects/aura_of_destruction_effect.cpp
  src/impl/effects/aura_of_destruction_effect.h
  src/impl/effects/auras_observer.cpp
  src/impl/effects/auras_observer.h
  src/turn_based/base_effect.h
  src/impl/effects/hypnosis_effect.h
  src/impl/effects/poison_effect.h
  src/impl/effects/web_effect.h
  src/impl/game_state/get_entities.cpp
  src/impl/game_state/get_entities.h
  src/impl/game_state/get_entity_names.h
  src/impl/scenarios/creator_helper.cpp
  src/impl/scenarios/entities_reader.cpp
  src/impl/scenarios/entities_reader.h
  src/impl/scenarios/map_reader.cpp
  src/impl/scenarios/map_reader.h
  src/impl/scenarios/scenario_helper.h
  src/impl/scenarios/scenario_helper.h
  src/impl/game_state/get_entity_names.cpp)

add_subdirectory(src/turn_based)
add_subdirectory(src/networking)
add_subdirectory(src/impl)

## entities plugins
add_subdirectory(src/entities/environment)
add_subdirectory(src/entities/native)
add_subdirectory(src/entities/saberhand)
add_subdirectory(src/entities/saurian)
add_subdirectory(src/entities/shooter)

## scenario plugins
add_subdirectory(src/scenarios/saurian_web)

add_executable(pigeon_war src/main.cpp src/message_processor.cpp)
target_link_libraries(pigeon_war turn_based impl networking)

#add_executable(tester src/tester.cpp)
#target_link_libraries(tester game_core)
#target_link_libraries(tester)
