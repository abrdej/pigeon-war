cmake_minimum_required(VERSION 3.5.1)
project(pigeonwar)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

set(SFML_ROOT "C:/Biblioteki/SFML-2.4.2")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})

set(BOOST_ROOT "C:/local/boost_1_65_1")
set(BOOST_INCLUDEDIR=/usr/local/include/boost)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp
        entities/entity.h
        managers/abilities_manager.cpp
        abilities/ability.cpp
        ai/ai.cpp
        ai/ai_manager.cpp
        animation/animation.cpp
        animation/animation_impl.cpp
        animation/animations_objects.cpp
        abilities/basic_melee_attack.cpp
        gui/bitmap_center.cpp
        core/board.cpp
        gui/board_panel.cpp
        abilities/bullet.cpp
        gui/buttons_panel.cpp
        utils/creator_helper.cpp
        abilities/damage_dealer.cpp
        managers/directions_manager.cpp
        abilities/drain.cpp
        gui/drawer.cpp
        managers/entity_manager.cpp
        core/game.cpp
        gui/gui.cpp
        abilities/grenade.cpp
        abilities/invisibility.cpp
        abilities/moveable.cpp
        gui/my_button.cpp
        entities/wolf.cpp
        entities/werewolf.cpp
        managers/types_manager.cpp
        core/turn.cpp
        abilities/tongue_of_fire.cpp
        core/states.cpp
        abilities/shoot.cpp
        abilities/sabers.cpp
        core/path_finder.cpp
        managers/names_manager.cpp
        core/players.cpp
        core/board.cpp
        entities/shooter.cpp
        managers/entity_remover.cpp
        managers/entity_remover.h
        utils/scenario_helper.h
        scenarios/scenarios.h
        scenarios/scenarios.cpp
        entities/tree.cpp entities/tree.h
        entities/samurai_rat.h
        abilities/sword_blow.cpp
        abilities/sword_blow.h
        abilities/poison.cpp
        abilities/poison.h
        entities/troll.h
        abilities/bludgeon.h
        abilities/bludgeon.cpp
        abilities/rage.cpp
        abilities/rage.h
        managers/health_manager.cpp
        entities/mouse.h
        abilities/poisoned_missile.cpp
        abilities/poisoned_missile.h
        managers/entity_remover.cpp
        managers/entity_remover.h
        utils/scenario_helper.h
        scenarios/scenarios.h
        scenarios/scenarios.cpp
        entities/tree.cpp
        entities/tree.h
        entities/samurai_rat.h
        abilities/sword_blow.cpp
        abilities/sword_blow.h
        abilities/poison.cpp
        abilities/poison.h
        entities/troll.h
        abilities/bludgeon.h
        abilities/bludgeon.cpp
        abilities/rage.cpp
        abilities/rage.h
        managers/health_manager.cpp
        entities/droid.h
        abilities/laser.cpp
        abilities/laser.h
        abilities/teleport.cpp
        abilities/teleport.h abilities/wolf_herd.cpp abilities/wolf_herd.h abilities/dodge.cpp abilities/dodge.h entities/grenadier.h abilities/bomb.cpp abilities/bomb.h entities/destroyer.h abilities/armor.cpp abilities/armor.h abilities/blow_the_ax.cpp abilities/blow_the_ax.h gui/drawable.cpp gui/drawable.h gui/drawing_manager.cpp gui/drawing_manager.h gui/entity_drawer.h entities/treant.h abilities/entangling.cpp abilities/entangling.h abilities/recovery.cpp abilities/recovery.h entities/fire.h entities/balloon.h abilities/build_cannon.cpp abilities/build_cannon.h entities/cannon.h abilities/build_barrack.cpp abilities/build_barrack.h abilities/possible_movement.cpp abilities/possible_movement.h entities/barrack.h abilities/builder.cpp abilities/builder.h entities/drilling_rig.h entities/fissure.h entities/thrower.h abilities/flame_thrower.cpp abilities/flame_thrower.h abilities/counterattack.cpp abilities/counterattack.h)

add_executable(pigeonwar ${SOURCE_FILES})
target_link_libraries(pigeonwar ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
