cmake_minimum_required(VERSION 3.5.1)
project(pigeon_war)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

configure_file(src/config.h.in ${CMAKE_SOURCE_DIR}/src/config.h @ONLY)

find_package(Boost COMPONENTS log system REQUIRED)

add_compile_options(-fPIC)

set(SOURCE_FILES
  src/abilities/abilities.h
  src/abilities/ability.h
  src/abilities/damage_dealer.cpp
  src/abilities/damage_dealers.h
  src/abilities/moveable.cpp
  src/ai/action_makers.cpp
  src/ai/action_makers.h
  src/ai/ai_factories.h
  src/ai/ai_knowledge.h
  src/ai/ai_manager.cpp
  src/ai/behavior_node.cpp
  src/ai/behavior_node.h
  src/ai/movers.cpp
  src/ai/movers.h
  src/ai/nodes_compositions.h
  src/ai/target_finders.cpp
  src/ai/target_finders.h
  src/components/applied_effects.cpp
  src/components/applied_effects.h
  src/components/damage_pack.h
  src/components/damage_taker.cpp
  src/components/damage_taker.h
  src/components/health_field.h
  src/components/modification.cpp
  src/components/modification.h
  src/components/power_field.h
  src/core/bitmap_key.h src/config.h.in
  src/core/board.cpp
  src/core/board.cpp
  src/core/board_container.h
  src/core/defs.h
  src/core/game.cpp
  src/core/game_controller.cpp
  src/core/game_state.h
  src/core/get_button_description.cpp
  src/core/get_button_description.h
  src/core/get_effect_description.cpp
  src/core/get_effect_description.h
  src/core/get_game_state.cpp
  src/core/get_game_state.h
  src/core/logger.cpp
  src/core/module_holder.h
  src/core/path_finder.cpp
  src/core/states.h
  src/core/turn_system.cpp
  src/effects/aura_of_armor_effect.cpp
  src/effects/aura_of_armor_effect.h
  src/effects/aura_of_destruction_effect.cpp
  src/effects/aura_of_destruction_effect.h
  src/effects/auras_observer.cpp
  src/effects/auras_observer.h
  src/effects/base_effect.h
  src/effects/hypnosis_effect.h
  src/effects/poison_effect.h
  src/effects/web_effect.h
  src/entities/entities_factory.cpp
  src/entities/entities_factory.h
  src/managers/get_entities.cpp
  src/managers/get_entities.h
  src/managers/get_entity_names.h
  src/managers/players_manager.cpp
  src/messages/from_to_json.h
  src/messages/massages_makers.cpp
  src/messages/massages_makers.h
  src/scenarios/creator_helper.cpp
  src/scenarios/entities_reader.cpp
  src/scenarios/entities_reader.h
  src/scenarios/map_reader.cpp
  src/scenarios/map_reader.h
  src/scenarios/saurian_web_scenario.cpp
  src/scenarios/saurian_web_scenario.h
  src/scenarios/scenario_helper.h
  src/scenarios/scenario_helper.h
  src/server/message.h
  src/server/new_server.cpp
  src/server/new_server.h
  src/server/sender.cpp
  src/server/sender.h
  src/server/server.cpp src/managers/get_entity_names.cpp
  src/server/server.h
  src/server/web_socket_connection.h
  src/utils/algorithm.h
  src/utils/callback_holder.h
  src/utils/control_ptr.h
  src/utils/create_methods.h
  src/utils/descriptions.h
  src/utils/for_each_in_tuple.h
  src/utils/graph.h
  src/utils/message_joiner.h)

add_library(game_core SHARED ${SOURCE_FILES})
target_include_directories(game_core PUBLIC src external)
target_link_libraries(game_core PUBLIC Boost::headers Boost::system Boost::log pthread dl)

# entities plugins
add_subdirectory(src/entities/environment)
add_subdirectory(src/entities/native)
add_subdirectory(src/entities/saberhand)
add_subdirectory(src/entities/saurian)
add_subdirectory(src/entities/shooter)

add_executable(pigeon_war src/main.cpp)
target_link_libraries(pigeon_war game_core)

add_executable(tester src/tester.cpp)
target_link_libraries(tester game_core)
target_link_libraries(tester)
