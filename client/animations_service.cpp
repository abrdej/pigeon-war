#include "animations_service.h"
#include "animations_handlers.h"

std::unique_ptr<animations_service> animations_service::impl;

void animations_service::initialize() {

	add<shoot_handler>(animation_def::shoot);
	add<blow_the_ax_handler>(animation_def::blow_the_ax);
	add<dodge_handler>(animation_def::dodge);
	add<magic_bullet_handler>(animation_def::magic_bullet);
	add<magic_suck_handler>(animation_def::magic_suck);
	add<sniper_shot_handler>(animation_def::sniper_shot);
	add<teleport_handler>(animation_def::teleport);
	add<poisoned_missile_handler>(animation_def::poisoned_missile);
	add<laser_handler>(animation_def::laser);
	add<drain_handler>(animation_def::drain);
	add<grenade_handler>(animation_def::grenade);
	add<power_bullet_handler>(animation_def::power_bullet);
	add<protection_field_handler>(animation_def::protection_field);
	add<sabers_handler>(animation_def::sabers);
	add<move_handler>(animation_def::move);
	add<aura_of_immunity_handler>(animation_def::aura_of_immunity);
	add<aura_of_immunity_break_handler>(animation_def::aura_of_immunity_break);
	add<basic_melee_attack_handler>(animation_def::basic_melee_attack);
	add<chopper_handler>(animation_def::chopper);
	add<counterattack_handler>(animation_def::counterattack);
	add<flame_thrower_handler>(animation_def::flame_thrower);
	add<giant_blow_handler>(animation_def::giant_blow);
	add<giant_ram_handler>(animation_def::giant_ram);
	add<handcannon_handler>(animation_def::handcannon);
	add<hypnosis_handler>(animation_def::hypnosis);
	add<jaw_spider_handler>(animation_def::jaw_spider);
	add<kill_handler>(animation_def::kill);
	add<set_killer_instinct_handler>(animation_def::set_killer_instinct);
	add<remove_killer_instinct_handler>(animation_def::remove_killer_instinct);
	add<prison_connection_handler>(animation_def::prison_connection);
	add<spear_handler>(animation_def::spear);
	add<spider_web_handler>(animation_def::spider_web);
	add<spiral_of_fire_handler>(animation_def::spiral_of_fire);
	add<sword_blow_handler>(animation_def::sword_blow);
	add<tongue_of_fire_handler>(animation_def::tongue_of_fire);
	add<vicious_circle_handler>(animation_def::vicious_circle);
	add<warrior_blow_handler>(animation_def::warrior_blow);
	add<set_immortality_handler>(animation_def::set_immortality);
	add<bludgeon_push_handler>(animation_def::bludgeon_push);
	add<bludgeon_handler>(animation_def::bludgeon);
	add<rage_handler>(animation_def::rage);
	add<shiruken_handler>(animation_def::shiruken);
	add<death_mark_handler>(animation_def::death_mark);
	add<set_invisibility_handler>(animation_def::set_invisibility);
	add<remove_invisibility_handler>(animation_def::remove_invisibility);
	add<poison_handler>(animation_def::poison);
	add<start_sorcerer_attack_handler>(animation_def::start_sorcerer_attack);
	add<end_sorcerer_attack_handler>(animation_def::end_sorcerer_attack);
	add<change_health_handler>(animation_def::change_health);
	add<rocket_launcher_handler>(animation_def::rocket_launcher);
}