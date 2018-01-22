//
// Created by abrde on 16.12.2017.
//

#ifndef PIGEONWAR_BITMAPS_H
#define PIGEONWAR_BITMAPS_H

#include "common/add_enum.h"

enum class bitmap_key {
    none,
    shooter,
    saberhand,
    saberhand_transparency,
	sabers_attack,
    shoot,
    grenade,
    moveable,
    wolf,
    werewolf,
    drain,
    basic_melee_attack,
    bum,
	shards,
    claws,
	hello,
    stone,
    tree,
    saurian,
    tongue_of_fire,
	samurai_rat_sword,
    sabers,
    invisibility,
    saurions_web,
    native,
	native_attack,
    samurai_rat,
    sword_blow,
    troll,
    bludgeon,
    rage,
    mouse,
    poisoned_missile,
	poisoned_missile_splush,
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
	handcannonbum,
    protection_field,
	field_shoot,
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
	sniper_bum,
    hypnosis,
    monk,
    magic_bullet,
    jaw_spider,
    long_range_missile,
    ninja,
	ninja_attack,
    shiruken,
	shiruken_splash,
    assassin_slash,
    interception,
    absorber,
    absorption,
	absorber_orbit,
    power_circle,
    water,
    wall,
    fir,
    wretch,
    wretch_moving,
    vicious_circle,
	monk_use_1,
	monk_use_2,
	monk_use_3,
	magic_splash,
	warrior_attack,
	guardian_attack,
	healthing,
	troll_rage,
	detonation_anim,
	magic_suck,
	killer,
	giant,
	kill,
	magic_energy,
	killer_jump,
	killer_attack,
	defender,
	defender_attack,
	giant_blow,
	giant_blow_special,
	giant_ram,
	golem,
	stone_skin,
	power_bullet,
	power_bullet_bum,
	sorcerer,
	sorcerer_attack,
	warrior_immortal,
	prison_connection,
	poison_effect,
	rocket,
	combat_robot,
	druid,
    cure,
    cure_anim,
    portal,
	portal_1,
	portal_2,
	portal_3,
	lightning,
	lightning_prepare,
	change_rocket_type,
	ball_and_chain,
    soul_hunter,
	suck_the_soul
};

struct bitmaps_key_hash
{
	template <typename T>
	std::uint32_t operator()(T t) const
	{
		return static_cast<std::uint32_t>(t);
	}
};

PACKET_ADD_ENUM(bitmap_key)

#endif //PIGEONWAR_BITMAPS_H
