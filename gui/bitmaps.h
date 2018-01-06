//
// Created by abrde on 16.12.2017.
//

#ifndef PIGEONWAR_BITMAPS_H
#define PIGEONWAR_BITMAPS_H

enum class bitmap_key {
    none,
    shooter,
    saberhand,
    saberhand_transparency,
    shoot,
    grenade,
    moveable,
    wolf,
    werewolf,
    drain,
    basic_melee_attack,
    bum,
    claws,
    stone,
    tree,
    saurian,
    tongue_of_fire,
    sabers,
    invisibility,
    saurions_web,
    native,
    samurai_rat,
    sword_blow,
    troll,
    bludgeon,
    rage,
    mouse,
    poisoned_missile,
    droid,
    laser,
    teleport,
    dodge,
    grenadier,
    bomb,
    bomb_instance,
    bomb_detonation,
    wolf_herd,
    destroyer,
    armor,
    blow_the_ax,
    treant,
    entangling_instance,
    entangling,
    entangling_life_suck,
    recovery,
    fire,
    balloon,
    build_cannon,
    cannon,
    build_barrack,
    barrack,
    thrower,
    flame_thrower,
    counterattack,
    guardian,
    spear,
    shield,
    creature,
    creature_fired,
    chopper,
    spiral_of_fire,
    handthrower,
    handcannon,
    protection_field,
    warrior,
    warrior_blow,
    immortality,
    robot,
    spider,
    spider_web,
    surroundings,
    detonation,
    sniper,
    sniper_shot,
    hypnosis,
    monk,
    magic_bullet,
    jaw_spider,
    long_range_missile,
    ninja,
    shiruken,
    assassin_slash,
    interception,
    absorber,
    absorption,
    power_circle,
    water,
    wall,
    fir,
    wretch,
    wretch_moving,
    vicious_circle,
	killer,
	giant,
	kill
};

struct bitmaps_key_hash
{
	template <typename T>
	std::size_t operator()(T t) const
	{
		return static_cast<std::size_t>(t);
	}
};

#endif //PIGEONWAR_BITMAPS_H
