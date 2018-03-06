#include "animations_service.h"
#include "animations_handlers.h"

std::unique_ptr<animations_service> animations_service::impl;

void animations_service::initialize() {

	add<shoot_handler>("shoot");
	add<blow_the_ax_handler>("blow_the_ax");
	add<dodge_handler>("dodge");
	add<magic_bullet_handler>("magic_bullet");
	add<magic_suck_handler>("magic_suck");
	add<sniper_shot_handler>("sniper_shot");
	add<teleport_handler>("teleport");
	add<poisoned_missile_handler>("poisoned_missile");
	add<laser_handler>("laser");
	add<drain_handler>("drain");
	add<grenade_handler>("grenade");
	add<power_bullet_handler>("power_bullet");
	add<protection_field_handler>("protection_field");
	add<sabers_handler>("sabers");
	add<move_handler>("move");
	add<aura_of_immunity_handler>("aura_of_immunity");
	add<aura_of_immunity_break_handler>("aura_of_immunity_break");
	add<basic_melee_attack_handler>("basic_melee_attack");
	add<chopper_handler>("chopper");
	add<counterattack_handler>("counterattack");
	add<flame_thrower_handler>("flame_thrower");
	add<giant_blow_handler>("giant_blow");
	add<giant_ram_handler>("giant_ram");
	add<handcannon_handler>("handcannon");
	add<hypnosis_handler>("hypnosis");
	add<jaw_spider_handler>("jaw_spider");
	add<kill_handler>("kill");
	add<set_killer_instinct_handler>("set_killer_instinct");
	add<remove_killer_instinct_handler>("remove_killer_instinct");
	add<prison_connection_handler>("prison_connection");
	add<spear_handler>("spear");
	add<spider_web_handler>("spider_web");
	add<spiral_of_fire_handler>("spiral_of_fire");
	add<sword_blow_handler>("sword_blow");
	add<tongue_of_fire_handler>("tongue_of_fire");
	add<vicious_circle_handler>("vicious_circle");
	add<warrior_blow_handler>("warrior_blow");
	add<set_immortality_handler>("set_immortality");
	add<bludgeon_push_handler>("bludgeon_push");
	add<bludgeon_handler>("bludgeon");
	add<rage_handler>("rage");
	add<shiruken_handler>("shiruken");
	add<death_mark_handler>("death_mark");
	add<set_invisibility_handler>("set_invisibility");
	add<remove_invisibility_handler>("remove_invisibility");
	add<poison_handler>("poison");
	add<start_sorcerer_attack_handler>("start_sorcerer_attack");
	add<end_sorcerer_attack_handler>("end_sorcerer_attack");
	add<change_health_handler>("change_health");
	add<rocket_launcher_handler>("rocket_launcher");
	add<portal_handler>("portal");
	add<cure_handler>("cure");
	add<lightning_prepare_handler>("lightning_prepare");
	add<lightning_handler>("lightning");
	add<soul_out_handler>("soul_out");
	add<saw_passing_handler>("saw_passing");
	add<arrow_handler>("arrow");
	add<destruction_handler>("destruction");
	add<fist_of_doom_handler>("fist_of_doom");
	add<uselessness_handler>("uselessness");
	add<meteorite_before_handler>("meteorite_before");
	add<meteorite_handler>("meteorite");
	add<purification_handler>("purification");
	add<flame_burning_handler>("flame_burning");
}