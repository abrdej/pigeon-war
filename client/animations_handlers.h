//
// Created by abrdej on 10.01.18.
//

#ifndef PIGEONWAR_ANIMATIONS_HANDLERS_H
#define PIGEONWAR_ANIMATIONS_HANDLERS_H

#include "animations_service.h"

template <typename... DataTypes>
void extract(nlohmann::json& data, DataTypes&... x) {

	std::size_t index = 1;

	auto extractor = [&data, &index](auto& y) {
			y = data[index++].get<std::decay_t<decltype(y)>>();
	};
	std::int32_t tab[] = {(extractor(x), 0)...};
}

template <bitmap_key shot_bitmap_key, bitmap_key explosion_bitmap_key = "none>
struct shot_base_handler : base_handler {
	std::uint32_t from_index, to_index;

	void handle(nlohmann::json& data, game_state& g_state) override {

		extract(data, from_index, to_index);

		animation::player<animation::move>::launch(animation::move(from_index, to_index, shot_bitmap_key));
		animation::base_player::play();

		if (explosion_bitmap_key != "none) {
			animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), explosion_bitmap_key));
			animation::base_player::play();
		}
	}
};

struct move_base_handler : base_handler {
	std::uint32_t from_index, to_index;

	void handle(nlohmann::json& data, game_state& g_state) override {
		extract(data, from_index, to_index);

		auto entity_id = g_state.board.take(from_index);

		animation::player<animation::move_entity>::launch(animation::move_entity(from_index, to_index, entity_id));
		animation::base_player::play();

		g_state.board.give_back(entity_id, to_index);
	}
};

template <bitmap_key middle_bitmap_flush = "none>
struct move_with_return_base_handler : base_handler {
	std::uint32_t from_index, to_index;

	void handle(nlohmann::json& data, game_state& g_state) override {
		extract(data, from_index, to_index);

		auto entity_id = g_state.board.take(from_index);

		animation::player<animation::move>::launch(animation::move(from_index, to_index, entity_id));
		animation::base_player::play();

		if (middle_bitmap_flush != "none) {
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

	void handle(nlohmann::json& data, game_state& g_state) override {
		extract(data, index);

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

	void handle(nlohmann::json& data, game_state& g_state) override {
		extract(data, entity_id);

		drawing_manager::typed_drawer_for<entity_drawer>(entity_id)->change_bitmap(new_bitmap_key);
	}
};

struct shoot_handler : shot_base_handler<"shoot, "bum> {

};

struct blow_the_ax_handler : move_with_return_base_handler<> {

};

struct dodge_handler : bitmap_flush_base_handler<"dodge, true> {

};

struct magic_bullet_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct magic_suck_handler : bitmap_flush_base_handler<"magic_suck> {

};

struct sniper_shot_handler : shot_base_handler<"sniper_shot, "sniper_bum> {

};

struct teleport_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct poisoned_missile_handler : shot_base_handler<"poisoned_missile, "poisoned_missile_splush> {

};

struct laser_handler : shot_base_handler<"laser, "none> {

};

struct drain_handler : move_with_return_base_handler<"native_attack> {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct grenade_handler : shot_base_handler<"grenade> {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct power_bullet_handler : shot_base_handler<"power_bullet, "power_bullet_bum> {

};

struct protection_field_handler : shot_base_handler<"protection_field, "field_shoot> {

};

struct sabers_handler : move_with_return_base_handler<"sabers_attack> {

};

struct move_handler : move_base_handler {

};

struct aura_of_immunity_handler : bitmap_flush_base_handler<"defender> {

};

struct aura_of_immunity_break_handler : bitmap_flush_base_handler<"defender_attack> {

};

struct basic_melee_attack_handler : move_with_return_base_handler<"claws> {

};

struct chopper_handler : move_with_return_base_handler<"creature_fired> {

};

struct counterattack_handler : move_with_return_base_handler<"native_attack> {

};

struct flame_thrower_handler : shot_base_handler<"flame_thrower> {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct giant_blow_handler : move_with_return_base_handler<"giant_blow> {

};

struct giant_ram_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};


struct handcannon_handler : shot_base_handler<"handcannon, "handcannonbum> {
};

struct hypnosis_handler : bitmap_flush_base_handler<"field_shoot> {
};

struct jaw_spider_handler : bitmap_flush_base_handler<"jaw_spider> {
};

struct kill_handler : move_with_return_base_handler<"killer_attack> {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct set_killer_instinct_handler : change_bitmap_base_handler<"killer_jump> {

};

struct remove_killer_instinct_handler : change_bitmap_base_handler<"killer> {

};

struct prison_connection_handler : bitmap_flush_base_handler<"protection_field> {
};

struct spear_handler : move_with_return_base_handler<"guardian_attack> {
};

struct spider_web_handler : shot_base_handler<"spider_web> {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct spiral_of_fire_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct sword_blow_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct tongue_of_fire_handler : shot_base_handler<"tongue_of_fire> {

};

struct vicious_circle_handler : bitmap_flush_base_handler<"magic_energy, false, 200> {

};

struct warrior_blow_handler : move_with_return_base_handler<"warrior_attack> {

};

struct set_immortality_handler : change_bitmap_base_handler<"warrior_immortal> {

};

struct bludgeon_push_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct bludgeon_handler : move_with_return_base_handler<"bum> {

};

struct rage_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct shiruken_handler : shot_base_handler<"shiruken, "shiruken_splash> {

};

struct death_mark_handler : bitmap_flush_base_handler<"assassin_slash> {

};

struct set_invisibility_handler : change_bitmap_base_handler<"saberhand_transparency> {

};

struct remove_invisibility_handler : change_bitmap_base_handler<"saberhand> {

};

struct poison_handler : bitmap_flush_base_handler<"poison_effect> {

};

struct start_sorcerer_attack_handler : change_bitmap_base_handler<"sorcerer_attack> {

};

struct end_sorcerer_attack_handler : change_bitmap_base_handler<"sorcerer> {

};

struct change_health_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct change_power_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct rocket_launcher_handler : shot_base_handler<"rocket, "bum> {

};

struct portal_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct cure_handler : bitmap_flush_base_handler<"cure_anim> {

};

struct lightning_prepare_handler : bitmap_flush_base_handler<"lightning_prepare> {

};

struct lightning_handler : bitmap_flush_base_handler<"lightning> {

};

struct soul_out_handler : bitmap_flush_base_handler<"suck_the_soul> {

};

struct saw_passing_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct arrow_handler : shot_base_handler<"arrow_anim> {

};

struct destruction_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct fist_of_doom_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct uselessness_handler : bitmap_flush_base_handler<"uselessness> {

};

struct meteorite_before_handler : bitmap_flush_base_handler<"uselessness> {

};

struct meteorite_handler : base_handler {
	void handle(nlohmann::json& data, game_state& g_state) override;
};

struct purification_handler : bitmap_flush_base_handler<"uselessness> {

};

struct flame_burning_handler : shot_base_handler<"power_bullet, "power_bullet_bum> {

};



#endif //PIGEONWAR_ANIMATIONS_HANDLERS_H
