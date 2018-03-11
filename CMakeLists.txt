cmake_minimum_required(VERSION 3.5.1)
project(pigeonwar)

include_directories(${CMAKE_SOURCE_DIR}/client)
include_directories(${CMAKE_SOURCE_DIR}/server)
include_directories(${CMAKE_SOURCE_DIR})


set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(RES_DIR "${CMAKE_SOURCE_DIR}/res")

configure_file(config.h.in ${CMAKE_SOURCE_DIR}/config.h @ONLY)

if(WIN32)
    set(SFML_ROOT "C:/Biblioteki/SFML-2.4.2")
    link_directories("${CMAKE_SOURCE_DIR}/lib")
endif()

if(UNIX)
    set(PLATFORM_LIBS pthread)
    set(BOOST_INCLUDEDIR "/usr/include")
    set(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu")
endif()

find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})

if (WIN32)
    set(BOOST_INCLUDEDIR "C:/local/boost_1_65_1/")
    set(BOOST_LIBRARYDIR "C:/local/boost_1_65_1/lib64-msvc-14.1")
    set(BOOST_ROOT "C:/local/boost_1_65_1/boost")
endif()

set(Boost_USE_STATIC_LIBS ON)
add_definitions(-DBOOST_ALL_DYN_LINK)
add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

#include_directories(/home/abrdej/Libraries/beast/include/)

# Locate GTest
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

set(SERVER_SOURCE_FILES
        server/entities/entity.h
        server/ai/ai.cpp
        server/ai/ai_manager.cpp
        server/abilities/basic_melee_attack.cpp
        server/core/board.cpp
        utils/creator_helper.cpp
        server/abilities/damage_dealers.h
        server/abilities/damage_dealer.cpp
        server/abilities/drain.cpp
        server/managers/entity_manager.cpp
        server/core/game.cpp
        server/abilities/grenade.cpp
        server/abilities/invisibility.cpp
        server/abilities/moveable.cpp
        server/core/turn_system.cpp
        server/abilities/tongue_of_fire.cpp
        server/core/states_controller.cpp
        server/abilities/shoot.cpp
        server/abilities/sabers.cpp
        server/core/path_finder.cpp
        server/managers/players_manager.cpp
        server/core/board.cpp
        utils/scenario_helper.h
        server/entities/tree.h
        server/abilities/sword_blow.cpp
        server/abilities/sword_blow.h
        server/abilities/bludgeon.h
        server/abilities/bludgeon.cpp
        server/entities/poisoner.h
        server/abilities/poisoned_missile.cpp
        server/abilities/poisoned_missile.h
        utils/scenario_helper.h
        server/entities/stone.h
        server/entities/tree.h
        server/entities/samurai_rat.h
        server/entities/troll.h
        server/abilities/rage.cpp
        server/abilities/rage.h
        server/entities/droid.h
        server/abilities/laser.cpp
        server/abilities/laser.h
        server/abilities/teleport.cpp
        server/abilities/teleport.h
        server/abilities/wolf_herd.cpp
        server/abilities/wolf_herd.h
        server/abilities/dodge.cpp
        server/abilities/dodge.h
        server/entities/grenadier.h
        server/abilities/bomb.cpp
        server/abilities/bomb.h
        server/entities/destroyer.h
        server/abilities/armor.cpp
        server/abilities/armor.h
        server/abilities/blow_the_ax.cpp
        server/abilities/blow_the_ax.h
        server/entities/treant.h
        server/abilities/entangling.cpp
        server/abilities/entangling.h
        server/abilities/recovery.cpp
        server/abilities/recovery.h
        server/entities/fire.h
        server/abilities/teleport.h
        server/abilities/wolf_herd.cpp
        server/abilities/wolf_herd.h
        server/abilities/dodge.cpp
        server/abilities/dodge.h
        server/entities/grenadier.h
        server/abilities/bomb.cpp
        server/abilities/bomb.h
        server/entities/destroyer.h
        server/abilities/armor.cpp
        server/abilities/armor.h
        server/abilities/blow_the_ax.cpp
        server/abilities/blow_the_ax.h
        server/entities/treant.h
        server/abilities/entangling.cpp
        server/abilities/entangling.h
        server/abilities/recovery.cpp
        server/abilities/recovery.h
        server/entities/fire.h
        server/entities/thrower.h
        server/abilities/flame_thrower.cpp
        server/abilities/flame_thrower.h
        server/abilities/counterattack.cpp
        server/abilities/counterattack.h
        server/entities/guardian.h
        server/abilities/spear.cpp
        server/abilities/spear.h
        server/abilities/shield.cpp
        server/abilities/shield.h
        server/components/applied_effects.cpp
        server/components/applied_effects.h
        server/entities/creature.h
        server/abilities/chopper.cpp
        server/abilities/chopper.h
        server/abilities/spiral_of_fire.cpp
        server/abilities/spiral_of_fire.h
        server/entities/handthrower.h
        server/abilities/handcannon.cpp
        server/abilities/handcannon.h
        server/abilities/protection_field.cpp
        server/abilities/protection_field.h
        server/entities/warrior.h
        server/abilities/warrior_blow.cpp
        server/abilities/warrior_blow.h
        server/abilities/immortality.cpp
        server/abilities/immortality.h
        server/entities/robot.h
        server/abilities/spider_web.cpp
        server/abilities/spider_web.h
        server/entities/spider.h
        server/abilities/surroundings.cpp
        server/abilities/surroundings.h
        server/abilities/detonation.cpp
        server/abilities/detonation.h
        server/entities/sniper.h
        server/abilities/sniper_shot.cpp
        server/abilities/sniper_shot.h
        server/abilities/hypnosis.cpp
        server/abilities/hypnosis.h
        server/entities/monk.h
        server/abilities/magic_bullet.cpp
        server/abilities/magic_bullet.h
        server/abilities/jaw_spider.cpp
        server/abilities/jaw_spider.h
        server/abilities/long_range_missile.cpp
        server/abilities/long_range_missile.h
        server/entities/ninja.h
        server/abilities/interception.cpp
        server/abilities/interception.h
        server/entities/absorber.h
        server/abilities/absorption.cpp
        server/abilities/absorption.h
        server/abilities/power_circle.cpp
        server/abilities/power_circle.h
        server/abilities/shiruken.cpp
        server/abilities/shiruken.h
        server/abilities/assassin_slash.cpp
        server/abilities/assassin_slash.h
        server/abilities/assassin_slash.h
        server/entities/water.h
        server/entities/wall.h
        server/entities/fir.h
        server/entities/wretch.h
        server/abilities/vicious_circle.cpp
        server/abilities/vicious_circle.h
        server/abilities/wretch_moving.cpp
        server/abilities/wretch_moving.h
        server/abilities/kill.cpp
        common/bitmaps.h config.h.in
        server/components/power_field.h
        server/abilities/possible_move_helper.h
        server/abilities/possible_move_helper.cpp
        server/abilities/abilities.h
        server/abilities/ability.h
        server/entities/wolf.h
        server/entities/werewolf.h
        server/entities/shooter.h
        server/entities/saurian.h
        server/entities/native.h
        server/entities/killer.h
        server/entities/giant.h

        server/effects/aura_of_immunity_effect.cpp
        server/effects/aura_of_immunity_effect.h
        server/effects/auras_observer.cpp
        server/effects/auras_observer.h

        server/server.h server/packets_makers.h
        server/abilities/defender.cpp
        server/abilities/defender.h
        server/abilities/giant_blow.cpp
        server/abilities/giant_blow.h
        server/abilities/giant_ram.cpp
        server/abilities/giant_ram.h
        server/abilities/stone_skin.cpp

        server/abilities/stone_skin.h
        server/abilities/power_bullet.cpp
        server/abilities/power_bullet.h
        server/abilities/straight_target_ability.cpp
        server/abilities/straight_target_ability.h
        server/abilities/per_turn_usable.h
        server/sender.h
        server/sender.cpp
        server/abilities/neighboring_target_ability.h
        server/abilities/path_target_ability.h
        server/abilities/caster_target_ability.h
        server/abilities/prison_connection.cpp
        server/abilities/prison_connection.h
        server/abilities/killer_instinct.cpp
        server/abilities/killer_instinct.h
        server/abilities/aura_of_immunity.cpp
        server/abilities/aura_of_immunity.h
        server/components/modification.cpp
        server/components/modification.h
        server/abilities/ball_and_chain.cpp
        server/abilities/ball_and_chain.h
        server/abilities/death_mark.cpp
        server/abilities/death_mark.h
        server/components/damage_taker.cpp
        server/components/damage_taker.h
        server/components/damage_pack.h
        server/abilities/regeneration.cpp
        server/abilities/regeneration.h
        server/abilities/rocket_launcher.cpp
        server/abilities/rocket_launcher.h
        server/abilities/change_rocket_type.cpp
        server/abilities/change_rocket_type.h
        server/abilities/missile_of_doom.cpp
        server/abilities/missile_of_doom.h
        server/abilities/barrier.cpp
        server/abilities/barrier.h
        server/core/board_effects.cpp
        server/core/board_effects.h
        server/abilities/portal.cpp
        server/abilities/portal.h
        server/abilities/cure.cpp
        server/abilities/cure.h
        server/abilities/lightning.cpp
        server/abilities/lightning.h
        server/abilities/suck_the_soul.cpp
        server/abilities/suck_the_soul.h
        server/abilities/saw_passing.cpp
        server/abilities/saw_passing.h
        server/abilities/arrow.cpp
        server/abilities/arrow.h
        server/abilities/aura_of_destruction.cpp
        server/abilities/aura_of_destruction.h
        server/effects/aura_of_destruction_effect.cpp
        server/effects/aura_of_destruction_effect.h
        server/abilities/fist_of_doom.cpp
        server/abilities/fist_of_doom.h
        server/abilities/uselessness.cpp
        server/abilities/uselessness.h
        server/abilities/meteorite.cpp
        server/abilities/meteorite.h
        server/effects/web_effect.h
        server/effects/hypnosis_effect.h
        server/effects/base_effect.h
        server/effects/poison_effect.h
        server/entities/druid.h
        server/entities/soul_hunter.h
        server/entities/mechanical_saw.h
        server/entities/commander.h
        server/entities/gin.h
        server/entities/wizzard.h
        server/entities/combat_robot.h
        server/entities/golem.h
        server/entities/sorcerer.h
        server/entities/combat_robot.cpp
        server/entities/entities_factory.cpp
        server/entities/entities_factory.h
        server/entities/absorber.cpp
        utils/control_ptr.h
        utils/callback_holder.h
        server/descriptions.h
        server/abilities/purification.cpp
        server/abilities/purification.h
        server/abilities/power_cost_ability.h
        server/scenarios/skirmish.cpp
        server/scenarios/skirmish.h
        server/scenarios/registered_entities.h
        server/scenarios/map_reader.cpp
        server/scenarios/map_reader.h
        common/make_message.cpp
        common/make_message.h server/entities/dragon.cpp server/entities/dragon.h server/abilities/dragon_skin.cpp server/abilities/dragon_skin.h server/abilities/flame_burning.cpp server/abilities/flame_burning.h server/abilities/hiding.cpp server/abilities/hiding.h server/abilities/mortar_thrower.cpp server/abilities/mortar_thrower.h)

set(CLIENT_SOURCE_FILES
        client/gui/bitmap_center.cpp
        client/gui/bitmap_center.h
        client/gui/board_panel.cpp
        client/gui/board_panel.h
        client/gui/buttons_panel.cpp
        client/gui/buttons_panel.h
        client/gui/drawable.cpp
        client/gui/drawable.h
        client/gui/drawer.cpp
        client/gui/drawer.h
        client/gui/drawing_manager.cpp
        client/gui/drawing_manager.h
        client/gui/entities_renderer.h
        client/gui/entity_drawer.cpp
        client/gui/entity_drawer.h
        client/gui/my_button.cpp
        client/gui/my_button.h
        client/pigeon_war_client.cpp
        client/pigeon_war_client.h
        client/gui/shooter_drawing.h
        client/gui/view_constants.h
        client/animation/animation.cpp
        client/animation/animation.h
        client/animation/animation_impl.cpp
        client/animation/animation_impl.h
        client/animation/animations_objects.cpp
        client/animation/animations_objects.h
        common/health_field.h
        common/bitmap_field.h
        common/game_state.h
        common/states.h
        common/animations.h
        common/turn_status.h
        common/add_enum.h
        common/packet_helper.h
        common/define_packet.h
        common/utils.h
        caller.h
        client/requests.cpp
        client/requests.h
        common/message_types.h
        client/animations_service.cpp
        client/animations_service.h
        client/animations_handlers.cpp
        client/animations_handlers.h
        client/menu/menu.cpp
        client/menu/menu.h
        common/effects.h
        client/gui/hint.cpp
        client/gui/hint.h
        client/screen.h
        client/menu_screen.cpp
        client/menu_screen.h
        client/gui/drawer_factory.cpp
        client/gui/drawer_factory.h
        common/messages/messages.cpp
        common/messages/messages.h
        common/logging.h
        common/read_message.cpp
        common/read_message.h)

add_executable(pigeonwar_client client/main.cpp ${CLIENT_SOURCE_FILES})
target_link_libraries(pigeonwar_client ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${PLATFORM_LIBS})

add_executable(pigeonwar_server server/main.cpp ${SERVER_SOURCE_FILES})
target_link_libraries(pigeonwar_server ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${PLATFORM_LIBS} ${Boost_LOG_LIBRARY} ${Boost_SYSTEM_LIBRARY})

add_executable(pigeonwar_hot_seat hot_seat.cpp)
target_link_libraries(pigeonwar_hot_seat ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

add_executable(pigeonwar_matching_server matching_server/matching_server.cpp matching_server/matcher.cpp matching_server/matcher.h)
target_link_libraries(pigeonwar_matching_server ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

#add_executable(run_tests tests/shoot.cpp)
#target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)