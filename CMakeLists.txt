cmake_minimum_required(VERSION 3.5.1)
project(pigeonwar)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(RES_DIR "${CMAKE_SOURCE_DIR}/res")

configure_file(config.h.in ${CMAKE_SOURCE_DIR}/config.h @ONLY)

if(WIN32)
    set(SFML_ROOT "C:/Biblioteki/SFML-2.4.2")
    link_directories("${CMAKE_SOURCE_DIR}/lib")
endif()

find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})

if (WIN32)
    set(BOOST_ROOT "C:/local/boost_1_65_1")
    set(BOOST_INCLUDEDIR=/usr/local/include/boost)
endif()

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
        core/turn.cpp
        abilities/tongue_of_fire.cpp
        core/states.cpp
        abilities/shoot.cpp
        abilities/sabers.cpp
        core/path_finder.cpp
        managers/names_manager.cpp
        core/players.cpp
        core/board.cpp
        managers/entity_remover.cpp
        managers/entity_remover.h
        utils/scenario_helper.h
        scenarios/scenarios.h
        scenarios/scenarios.cpp
        entities/tree.h
        abilities/sword_blow.cpp
        abilities/sword_blow.h
        abilities/bludgeon.h
        abilities/bludgeon.cpp
        entities/mouse.h
        abilities/poisoned_missile.cpp
        abilities/poisoned_missile.h
        managers/entity_remover.cpp
        managers/entity_remover.h
        utils/scenario_helper.h
        entities/tree.h
        entities/samurai_rat.h
        entities/troll.h
        abilities/rage.cpp
        abilities/rage.h
        managers/health_manager.cpp
        entities/droid.h
        abilities/laser.cpp
        abilities/laser.h
        abilities/teleport.cpp
        abilities/teleport.h
        abilities/wolf_herd.cpp
        abilities/wolf_herd.h
        abilities/dodge.cpp
        abilities/dodge.h
        entities/grenadier.h
        abilities/bomb.cpp
        abilities/bomb.h
        entities/destroyer.h
        abilities/armor.cpp
        abilities/armor.h
        abilities/blow_the_ax.cpp
        abilities/blow_the_ax.h
        gui/drawable.cpp
        gui/drawable.h
        gui/drawing_manager.cpp
        gui/drawing_manager.h
        gui/entity_drawer.h
        entities/treant.h
        abilities/entangling.cpp
        abilities/entangling.h
        abilities/recovery.cpp
        abilities/recovery.h
        entities/fire.h
        entities/balloon.h
        abilities/build_cannon.cpp
        abilities/build_cannon.h
        entities/cannon.h
        abilities/build_barrack.cpp
        abilities/build_barrack.h
        entities/barrack.h
        abilities/teleport.h
        abilities/wolf_herd.cpp
        abilities/wolf_herd.h
        abilities/dodge.cpp
        abilities/dodge.h
        entities/grenadier.h
        abilities/bomb.cpp
        abilities/bomb.h
        entities/destroyer.h
        abilities/armor.cpp
        abilities/armor.h
        abilities/blow_the_ax.cpp abilities/blow_the_ax.h gui/drawable.cpp gui/drawable.h gui/drawing_manager.cpp gui/drawing_manager.h gui/entity_drawer.h entities/treant.h abilities/entangling.cpp abilities/entangling.h abilities/recovery.cpp abilities/recovery.h entities/fire.h entities/balloon.h abilities/build_cannon.cpp abilities/build_cannon.h entities/cannon.h abilities/build_barrack.cpp abilities/build_barrack.h
        entities/barrack.h
        abilities/builder.cpp
        abilities/builder.h entities/drilling_rig.h entities/fissure.h entities/thrower.h abilities/flame_thrower.cpp abilities/flame_thrower.h abilities/counterattack.cpp abilities/counterattack.h entities/guardian.h abilities/spear.cpp abilities/spear.h abilities/shield.cpp abilities/shield.h managers/additions_manager.cpp managers/additions_manager.h entities/creature.h abilities/chopper.cpp abilities/chopper.h abilities/spiral_of_fire.cpp abilities/spiral_of_fire.h entities/handthrower.h abilities/handcannon.cpp abilities/handcannon.h abilities/protection_field.cpp abilities/protection_field.h gui/shooter_drawing.h managers/animation_manager.cpp managers/animation_manager.h
        entities/warrior.h abilities/warrior_blow.cpp abilities/warrior_blow.h abilities/immortality.cpp abilities/immortality.h entities/robot.h core/command_manager.cpp core/command_manager.h abilities/spider_web.cpp abilities/spider_web.h entities/spider.h abilities/surroundings.cpp abilities/surroundings.h abilities/detonation.cpp abilities/detonation.h entities/sniper.h abilities/sniper_shot.cpp abilities/sniper_shot.h abilities/hypnosis.cpp abilities/hypnosis.h entities/monk.h abilities/magic_bullet.cpp abilities/magic_bullet.h abilities/jaw_spider.cpp abilities/jaw_spider.h abilities/long_range_missile.cpp abilities/long_range_missile.h entities/ninja.h abilities/interception.cpp abilities/interception.h entities/absorber.h abilities/absorption.cpp abilities/absorption.h abilities/power_circle.cpp abilities/power_circle.h abilities/shiruken.cpp abilities/shiruken.h abilities/assassin_slash.cpp abilities/assassin_slash.h abilities/assassin_slash.h entities/water.h entities/wall.h entities/fir.h entities/wretch.h abilities/vicious_circle.cpp abilities/vicious_circle.h abilities/wretch_moving.cpp abilities/wretch_moving.h gui/bitmaps.h config.h.in gui/entity_drawer.cpp managers/power_manager.h abilities/possible_move_helper.h abilities/possible_move_helper.cpp entities/killer.h entities/giant.h abilities/kill.cpp abilities/kill.h)

add_executable(pigeonwar ${SOURCE_FILES})
target_link_libraries(pigeonwar ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
