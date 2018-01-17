//
// Created by abrdej on 10.01.18.
//

#ifndef PIGEONWAR_ANIMATIONS_HANDLERS_H
#define PIGEONWAR_ANIMATIONS_HANDLERS_H

#include "animations_service.h"

template <bitmap_key shot_bitmap_key, bitmap_key explosion_bitmap_key = bitmap_key::none>
struct shot_base_handler : base_handler {
	std::uint32_t from_index, to_index;

	void handle(sf::Packet& packet, game_state& g_state) override {

		unpack(packet, from_index);
		unpack(packet, to_index);

		animation::player<animation::move>::launch(animation::move(from_index, to_index, shot_bitmap_key));
		animation::base_player::play();

		if (explosion_bitmap_key != bitmap_key::none) {
			animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), explosion_bitmap_key));
			animation::base_player::play();
		}
	}
};

struct move_base_handler : base_handler {
	std::uint32_t from_index, to_index;

	void handle(sf::Packet& packet, game_state& g_state) override {
		unpack(packet, from_index);
		unpack(packet, to_index);

		auto entity_id = g_state.board.take(from_index);

		animation::player<animation::move_entity>::launch(animation::move_entity(from_index, to_index, entity_id));
		animation::base_player::play();

		g_state.board.give_back(entity_id, to_index);
	}
};

template <bitmap_key middle_bitmap_flush = bitmap_key::none>
struct move_with_return_base_handler : base_handler {
	std::uint32_t from_index, to_index;

	void handle(sf::Packet& packet, game_state& g_state) override {
		unpack(packet, from_index);
		unpack(packet, to_index);

		auto entity_id = g_state.board.take(from_index);

		animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
		animation::base_player::play();

		if (middle_bitmap_flush != bitmap_key::none) {
			animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
																					   std::chrono::milliseconds(150),
																					   middle_bitmap_flush));
			animation::base_player::play();
		}

		animation::player<animation::move>::launch(animation::move(to_index, from_index, entity_id));
		animation::base_player::play();

		g_state.board.give_back(entity_id, from_index);
	}
};

template <bitmap_key flush_bitmap_key, bool hide_index = false, long time = 150>
struct bitmap_flush_base_handler : base_handler {
	std::uint32_t index;

	void handle(sf::Packet& packet, game_state& g_state) override {
		unpack(packet, index);

		std::uint32_t entity_id{0};

		if (hide_index) {
			entity_id = g_state.board.take(index);
		}

		animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index,
																				   std::chrono::milliseconds(time),
																				   flush_bitmap_key));
		animation::base_player::play();

		if (hide_index) {
			g_state.board.give_back(entity_id, index);
		}
	}
};

template <bitmap_key new_bitmap_key>
struct change_bitmap_base_handler : base_handler {
	std::uint32_t entity_id;

	void handle(sf::Packet& packet, game_state& g_state) override {
		unpack(packet, entity_id);

		drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap(new_bitmap_key);
	}
};

struct shoot_handler : shot_base_handler<bitmap_key::shoot, bitmap_key::bum> {

};

struct blow_the_ax_handler : move_with_return_base_handler<> {

};

struct dodge_handler : bitmap_flush_base_handler<bitmap_key::dodge, true> {

};

struct magic_bullet_handler : base_handler {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct magic_suck_handler : bitmap_flush_base_handler<bitmap_key::magic_suck> {

};

struct sniper_shot_handler : shot_base_handler<bitmap_key::sniper_shot, bitmap_key::sniper_bum> {

};

struct teleport_handler : base_handler {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct poisoned_missile_handler : shot_base_handler<bitmap_key::poisoned_missile, bitmap_key::poisoned_missile_splush> {

};

struct laser_handler : shot_base_handler<bitmap_key::laser, bitmap_key::none> {

};

struct drain_handler : move_with_return_base_handler<bitmap_key::native_attack> {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct grenade_handler : shot_base_handler<bitmap_key::grenade> {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct power_bullet_handler : shot_base_handler<bitmap_key::power_bullet, bitmap_key::power_bullet_bum> {

};

struct protection_field_handler : shot_base_handler<bitmap_key::protection_field, bitmap_key::field_shoot> {

};

struct sabers_handler : move_with_return_base_handler<bitmap_key::sabers_attack> {

};

struct move_handler : move_base_handler {

};

struct aura_of_immunity_handler : bitmap_flush_base_handler<bitmap_key::defender> {

};

struct aura_of_immunity_break_handler : bitmap_flush_base_handler<bitmap_key::defender_attack> {

};

struct basic_melee_attack_handler : move_with_return_base_handler<bitmap_key::claws> {

};

struct chopper_handler : move_with_return_base_handler<bitmap_key::creature_fired> {

};

struct counterattack_handler : move_with_return_base_handler<bitmap_key::native_attack> {

};

struct flame_thrower_handler : shot_base_handler<bitmap_key::flame_thrower> {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct giant_blow_handler : move_with_return_base_handler<bitmap_key::giant_blow> {

};

struct giant_ram_handler : base_handler {
	void handle(sf::Packet& packet, game_state& g_state) override;
};


struct handcannon_handler : shot_base_handler<bitmap_key::handcannon, bitmap_key::handcannonbum> {
};

struct hypnosis_handler : bitmap_flush_base_handler<bitmap_key::field_shoot> {
};

struct jaw_spider_handler : bitmap_flush_base_handler<bitmap_key::jaw_spider> {
};

struct kill_handler : move_with_return_base_handler<bitmap_key::killer_attack> {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct set_killer_instinct_handler : change_bitmap_base_handler<bitmap_key::killer_jump> {

};

struct remove_killer_instinct_handler : change_bitmap_base_handler<bitmap_key::killer> {

};

struct prison_connection_handler : bitmap_flush_base_handler<bitmap_key::protection_field> {
};

struct spear_handler : move_with_return_base_handler<bitmap_key::guardian_attack> {
};

struct spider_web_handler : shot_base_handler<bitmap_key::spider_web> {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct spiral_of_fire_handler : base_handler {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct sword_blow_handler : base_handler {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct tongue_of_fire_handler : shot_base_handler<bitmap_key::tongue_of_fire> {

};

struct vicious_circle_handler : bitmap_flush_base_handler<bitmap_key::magic_energy, false, 200> {

};

struct warrior_blow_handler : move_with_return_base_handler<bitmap_key::warrior_attack> {

};

struct set_immortality_handler : change_bitmap_base_handler<bitmap_key::warrior_immortal> {

};

struct bludgeon_push_handler : base_handler {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct bludgeon_handler : move_with_return_base_handler<bitmap_key::bum> {

};

struct rage_handler : base_handler {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct shiruken_handler : shot_base_handler<bitmap_key::shiruken, bitmap_key::shiruken_splash> {

};

struct death_mark_handler : bitmap_flush_base_handler<bitmap_key::assassin_slash> {

};

struct set_invisibility_handler : change_bitmap_base_handler<bitmap_key::saberhand_transparency> {

};

struct remove_invisibility_handler : change_bitmap_base_handler<bitmap_key::saberhand> {

};

struct poison_handler : bitmap_flush_base_handler<bitmap_key::poison_effect> {

};

struct start_sorcerer_attack_handler : change_bitmap_base_handler<bitmap_key::sorcerer_attack> {

};

struct end_sorcerer_attack_handler : change_bitmap_base_handler<bitmap_key::sorcerer> {

};

struct change_health_handler : base_handler {
	void handle(sf::Packet& packet, game_state& g_state) override;
};

struct rocket_launcher_handler : shot_base_handler<bitmap_key::rocket, bitmap_key::bum> {

};


#endif //PIGEONWAR_ANIMATIONS_HANDLERS_H
