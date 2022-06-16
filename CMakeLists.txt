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
#  src/abilities/absorption.cpp
#  src/abilities/absorption.h
#  src/abilities/armor.cpp
#  src/abilities/armor.cpp
#  src/abilities/armor.h
#  src/abilities/armor.h
#  src/abilities/arrow.cpp
#  src/abilities/arrow.h
#  src/abilities/assassin_slash.cpp
#  src/abilities/assassin_slash.h
#  src/abilities/assassin_slash.h
#  src/abilities/aura_of_destruction.cpp
#  src/abilities/aura_of_destruction.h
#  src/abilities/aura_of_immunity.cpp
#  src/abilities/aura_of_immunity.h
#  src/abilities/ball_and_chain.cpp
#  src/abilities/ball_and_chain.h
#  src/abilities/barrier.cpp
#  src/abilities/barrier.h
#  src/abilities/blow_the_ax.cpp
#  src/abilities/blow_the_ax.cpp
#  src/abilities/blow_the_ax.h
#  src/abilities/blow_the_ax.h
#  src/abilities/bludgeon.cpp
#  src/abilities/bludgeon.h
#  src/abilities/bomb.cpp
#  src/abilities/bomb.cpp
#  src/abilities/bomb.h
#  src/abilities/bomb.h
#  src/abilities/caster_target_ability.h
#  src/abilities/change_rocket_type.cpp
#  src/abilities/change_rocket_type.h
#  src/abilities/charge.cpp
#  src/abilities/charge.h
#  src/abilities/chopper.cpp
#  src/abilities/chopper.h
#  src/abilities/claws.cpp
#  src/abilities/cleaver.cpp
#  src/abilities/cleaver.h
#  src/abilities/cure.cpp
#  src/abilities/cure.h
  src/abilities/damage_dealer.cpp
  src/abilities/damage_dealers.h
#  src/abilities/death_mark.cpp
#  src/abilities/death_mark.h
#  src/abilities/defender.cpp
#  src/abilities/defender.h
#  src/abilities/detonation.cpp
#  src/abilities/detonation.h
#  src/abilities/dodge.cpp
#  src/abilities/dodge.cpp
#  src/abilities/dodge.h
#  src/abilities/dodge.h
#  src/abilities/dragon_skin.cpp
#  src/abilities/dragon_skin.h
#  src/abilities/entangling.cpp
#  src/abilities/entangling.cpp
#  src/abilities/entangling.h
#  src/abilities/entangling.h
#  src/abilities/eye_shoot.cpp
#  src/abilities/eye_shoot.h
#  src/abilities/fast_draw.cpp
#  src/abilities/fast_draw.h
#  src/abilities/fist_of_doom.cpp
#  src/abilities/fist_of_doom.h
#  src/abilities/flame_burning.cpp
#  src/abilities/flame_burning.h
#  src/abilities/flame_thrower.cpp
#  src/abilities/flame_thrower.h
#  src/abilities/giant_blow.cpp
#  src/abilities/giant_blow.h
#  src/abilities/giant_ram.cpp
#  src/abilities/giant_ram.h
#  src/abilities/handcannon.cpp
#  src/abilities/handcannon.h
#  src/abilities/havoc.cpp
#  src/abilities/havoc.h
#  src/abilities/hiding.cpp
#  src/abilities/hiding.h
#  src/abilities/hypnosis.cpp
#  src/abilities/hypnosis.h
#  src/abilities/immateriality.cpp
#  src/abilities/immateriality.h
#  src/abilities/immortality.cpp
#  src/abilities/immortality.h
#  src/abilities/interception.cpp
#  src/abilities/interception.h
#  src/abilities/jaw_spider.cpp
#  src/abilities/jaw_spider.h
#  src/abilities/kill.cpp
#  src/abilities/killer_instinct.cpp
#  src/abilities/killer_instinct.h
#  src/abilities/laser.cpp
#  src/abilities/laser.h
#  src/abilities/lightning.cpp
#  src/abilities/lightning.h
#  src/abilities/long_range_missile.cpp
#  src/abilities/long_range_missile.h
#  src/abilities/magic_bullet.cpp
#  src/abilities/magic_bullet.h
#  src/abilities/meteorite.cpp
#  src/abilities/meteorite.h
#  src/abilities/missile_of_doom.cpp
#  src/abilities/missile_of_doom.h
#  src/abilities/mortar_thrower.cpp
#  src/abilities/mortar_thrower.h
  src/abilities/moveable.cpp
#  src/abilities/neighboring_target_ability.h
#  src/abilities/path_target_ability.h
#  src/abilities/per_turn_usable.h
#  src/abilities/poisoned_missile.cpp
#  src/abilities/poisoned_missile.h
#  src/abilities/poke.cpp
#  src/abilities/poke.h
#  src/abilities/portal.cpp
#  src/abilities/portal.h
#  src/abilities/possible_move_helper.cpp
#  src/abilities/possible_move_helper.h
#  src/abilities/power_bullet.cpp
#  src/abilities/power_bullet.h
#  src/abilities/power_circle.cpp
#  src/abilities/power_circle.h
#  src/abilities/power_cost_ability.h
#  src/abilities/prison_connection.cpp
#  src/abilities/prison_connection.h
#  src/abilities/protection_field.cpp
#  src/abilities/protection_field.h
#  src/abilities/purification.cpp
#  src/abilities/purification.h
#  src/abilities/rage.cpp
#  src/abilities/rage.h
#  src/abilities/recovery.cpp
#  src/abilities/recovery.cpp
#  src/abilities/recovery.h
#  src/abilities/recovery.h
#  src/abilities/regeneration.cpp
#  src/abilities/regeneration.h
#  src/abilities/repair.cpp
#  src/abilities/repair.h
#  src/abilities/revolver.cpp
#  src/abilities/revolver.h
#  src/abilities/rocket_launcher.cpp
#  src/abilities/rocket_launcher.h
#  src/abilities/saw_passing.cpp
#  src/abilities/saw_passing.h
#  src/abilities/shield.cpp
#  src/abilities/shield.h
#  src/abilities/shiruken.cpp
#  src/abilities/shiruken.h
#  src/abilities/smokescreen.cpp
#  src/abilities/smokescreen.h
#  src/abilities/sniper_shot.cpp
#  src/abilities/sniper_shot.h
#  src/abilities/sparks.cpp
#  src/abilities/sparks.h
#  src/abilities/spear.cpp
#  src/abilities/spear.h
#  src/abilities/spider_web.cpp
#  src/abilities/spider_web.h
#  src/abilities/spiral_of_fire.cpp
#  src/abilities/spiral_of_fire.h
#  src/abilities/stamp.cpp
#  src/abilities/stamp.h
#  src/abilities/stone_skin.cpp
#  src/abilities/stone_skin.h
#  src/abilities/straight_target_ability.cpp
#  src/abilities/straight_target_ability.h
#  src/abilities/suck_the_soul.cpp
#  src/abilities/suck_the_soul.h
#  src/abilities/surroundings.cpp
#  src/abilities/surroundings.h
#  src/abilities/sword_blow.cpp
#  src/abilities/sword_blow.h
#  src/abilities/talons.cpp
#  src/abilities/talons.h
#  src/abilities/teleport.cpp
#  src/abilities/teleport.h
#  src/abilities/teleport.h
#  src/abilities/transmission.cpp
#  src/abilities/transmission.h
#  src/abilities/trash_trail.cpp
#  src/abilities/trash_trail.h
#  src/abilities/uselessness.cpp
#  src/abilities/uselessness.h
#  src/abilities/vicious_circle.cpp
#  src/abilities/vicious_circle.h
#  src/abilities/warrior_blow.cpp
#  src/abilities/warrior_blow.h
#  src/abilities/wolf_herd.cpp
#  src/abilities/wolf_herd.cpp
#  src/abilities/wolf_herd.h
#  src/abilities/wolf_herd.h
#  src/abilities/wretch_moving.cpp
#  src/abilities/wretch_moving.h
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
#  src/entities/absorber.cpp
#  src/entities/absorber.h
#  src/entities/all_entities.h
#  src/entities/bomb_instance.cpp
#  src/entities/bomb_instance.h
#  src/entities/combat_robot.cpp
#  src/entities/combat_robot.h
#  src/entities/commander.cpp
#  src/entities/commander.h
#  src/entities/creature.h
#  src/entities/destroyer.cpp
#  src/entities/destroyer.h
#  src/entities/destroyer.h
#  src/entities/dragon.cpp
#  src/entities/dragon.h
#  src/entities/droid.h
#  src/entities/druid.h
  src/entities/entities_factory.cpp
  src/entities/entities_factory.h
#  src/entities/entity.h
#  src/entities/eye.cpp
#  src/entities/eye.h
#  src/entities/giant.h
#  src/entities/gin.h
#  src/entities/golem.h
#  src/entities/grenadier.h
#  src/entities/grenadier.h
#  src/entities/guardian.cpp
#  src/entities/guardian.h
#  src/entities/handthrower.h
#  src/entities/killer.h
#  src/entities/mechanical_saw.h
#  src/entities/monk.h
  #  src/entities/ninja.h
#  src/entities/pixie.cpp
#  src/entities/pixie.h
#  src/entities/poisoner.cpp
#  src/entities/poisoner.h
#  src/entities/reaper.cpp
#  src/entities/reaper.h
#  src/entities/robot.h
#  src/entities/rocket_thrower.cpp
#  src/entities/rocket_thrower.h
#  src/entities/samurai_rat.h
#  src/entities/sentinel.cpp
#  src/entities/sentinel.h
#  src/entities/snake.cpp
#  src/entities/snake.h
#  src/entities/sniper.h
#  src/entities/sorcerer.cpp
#  src/entities/sorcerer.h
#  src/entities/soul_hunter.h
#  src/entities/spectre.cpp
#  src/entities/spectre.h
#  src/entities/spider.h
#  src/entities/trailer.cpp
#  src/entities/trailer.h
#  src/entities/treant.h
#  src/entities/treant.h
#  src/entities/troll.h
#  src/entities/warrior.cpp
#  src/entities/warrior.h
#  src/entities/werewolf.h
#  src/entities/wizzard.h
#  src/entities/wolf.h
#  src/entities/wretch.h
  src/managers/get_entities.cpp
  src/managers/get_entities.h
  src/managers/get_entity_names.h
  src/managers/players_manager.cpp
  src/messages/from_to_json.h
  src/messages/massages_makers.cpp
  src/messages/massages_makers.h
#  src/scenarios/battle_with_a_golem_scenario.cpp
#  src/scenarios/battle_with_a_golem_scenario.h
  src/scenarios/creator_helper.cpp
#  src/scenarios/dark_forest.cpp
#  src/scenarios/dark_forest.h
  src/scenarios/entities_reader.cpp
  src/scenarios/entities_reader.h
  src/scenarios/map_reader.cpp
  src/scenarios/map_reader.h
  src/scenarios/saurian_web_scenario.cpp
  src/scenarios/saurian_web_scenario.h
  src/scenarios/scenario_helper.h
  src/scenarios/scenario_helper.h
#  src/scenarios/skirmish.cpp
#  src/scenarios/skirmish.h
#  src/scenarios/total_destruction.cpp
#  src/scenarios/total_destruction.h
#  src/scenarios/wolves_dinner.cpp
#  src/scenarios/wolves_dinner.h
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

add_library(game_core ${SOURCE_FILES})
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
