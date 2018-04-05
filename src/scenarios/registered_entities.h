//
// Created by abrdej on 06.02.18.
//

#ifndef PIGEONWAR_REGISTERED_ENTITIES_H
#define PIGEONWAR_REGISTERED_ENTITIES_H

#include <core/states_controller.h>
#include <entities/shooter.h>
#include <entities/destroyer.h>
#include <entities/droid.h>
#include <entities/saberhand.h>
#include <entities/treant.h>
#include <entities/native.h>
#include <entities/fire.h>
#include <entities/thrower.h>
#include <entities/guardian.h>
#include <entities/creature.h>
#include <entities/handthrower.h>
#include <entities/robot.h>
#include <entities/spider.h>
#include <entities/sniper.h>
#include <entities/monk.h>
#include <entities/ninja.h>
#include <entities/absorber.h>
#include <entities/water.h>
#include <entities/samurai_rat.h>
#include <entities/wall.h>
#include <entities/warrior.h>
#include <entities/fir.h>
#include <entities/wretch.h>
#include <entities/killer.h>
#include <entities/giant.h>
#include <entities/tree.h>
#include <entities/stone.h>
#include <entities/golem.h>
#include <entities/sorcerer.h>
#include <entities/combat_robot.h>
#include <entities/druid.h>
#include <entities/troll.h>
#include <entities/poisoner.h>
#include <entities/soul_hunter.h>
#include <entities/mechanical_saw.h>
#include <entities/commander.h>
#include <entities/gin.h>
#include <entities/wizzard.h>
#include <entities/dragon.h>
#include <entities/reaper.h>
#include <entities/bomb_instance.h>
#include <entities/grenadier.h>
#include <entities/eye.h>

template <typename Tuple, typename F, size_t ...Indices>
void for_each_impl(Tuple&& tuple, F&& f, std::index_sequence<Indices...>) {
    using swallow = int[];
    (void)swallow{1,
                  (f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...
    };
}

template <typename Tuple, typename F>
void for_each(Tuple&& tuple, F&& f) {
    constexpr size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
    for_each_impl(std::forward<Tuple>(tuple), std::forward<F>(f),
                  std::make_index_sequence<N>{});
}

using Entites = std::tuple<shooter,
        destroyer,
        samurai_rat,
        droid,
        saberhand,
        native,
        troll,
        sniper,
        poisoner,
        //werewolf,
//        robot,
        monk,
//        grenadier,
        //ninja,
        //treant,
        thrower,
//        killer,
        wizzard,
        druid,
//        absorber,
        //saurian,
        giant,
        guardian,
        sorcerer,
        creature,
        wretch,
        warrior,
        commander,
//        handthrower,
        //combat_robot,
        dragon,
        golem,

//        mechanical_saw,
        //gin,
        reaper,
        soul_hunter,
        spider>;

#endif //PIGEONWAR_REGISTERED_ENTITIES_H
