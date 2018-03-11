//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_ANIMATIONS_H
#define PIGEONWAR_ANIMATIONS_H

#include <tuple>
#include <iostream>
#include "bitmaps.h"

enum class animation_types {
	move,
	flash_bitmap,
	change_health,
	hide_show,
	change_bitmap
};

enum class animation_def {
	shoot,
	blow_the_ax,
	dodge,
	magic_bullet,
	magic_suck,
	sniper_shot,
	teleport,
	poisoned_missile,
	laser,
	drain,
	grenade,
	power_bullet,
	protection_field,
	sabers,
	move,
	aura_of_immunity,
	aura_of_immunity_break,
	basic_melee_attack,
	chopper,
	counterattack,
	flame_thrower,
	giant_blow,
	giant_ram,
	handcannon,
	hypnosis,
	jaw_spider,
	kill,
	set_killer_instinct,
	remove_killer_instinct,
	prison_connection,
	spear,
	spider_web,
	spiral_of_fire,
	sword_blow,
	tongue_of_fire,
	vicious_circle,
	warrior_blow,
	set_immortality,
	bludgeon_push,
	bludgeon,
	rage,
	shiruken,
	death_mark,
	set_invisibility,
	remove_invisibility,
	poison,
	start_sorcerer_attack,
	end_sorcerer_attack,
	change_health,
	rocket_launcher,
	portal,
	cure,
	lightning_prepare,
	lightning,
	soul_out,
	saw_passing,
	arrow,
	destruction,
	fist_of_doom,
	uselessness,
	meteorite_before,
	meteorite,
	purification
};

struct animation_def_key_hash
{
	template <typename T>
	std::uint32_t operator()(T t) const
	{
		return static_cast<std::uint32_t>(t);
	}
};

struct animation_pack {
	animation_pack() = default;
	animation_pack(const animation_types& a, std::int32_t x, std::int32_t y, std::int32_t z, bitmap_key k)
			: animation_type(a), x(x), y(y), z(z), btm_key(k) {
	}

	animation_types animation_type;

	std::int32_t x;
	std::int32_t y;
	std::int32_t z;

	bitmap_key btm_key;
};

#endif //PIGEONWAR_ANIMATIONS_H
