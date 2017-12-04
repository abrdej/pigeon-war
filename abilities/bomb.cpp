#include "bomb.h"
#include "damage_dealers.h"
#include <core/states.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <animation/animation.h>
#include <unordered_map>

bomb_detonation::bomb_detonation(std::size_t bomb_id) : bomb_id(bomb_id) {
//	onEveryRound([this]() {
//
//		if (waited) {
//			auto index = board::index_for(this->bomb_id);
//			use(index);
//		}
//
//		waited = true;
//	});
}

void bomb_detonation::look_for_bombs() {

}

void bomb_detonation::prepare(size_t for_index) {
//	states::state_controller::actual_state_ = states::states_types::wait_for_action;
//	states::state_controller::possible_movements_.push_back(for_index);
//	states::state_controller::actual_targeting_type_ = states::target_types::caster;
//	states::state_controller::wait_for_action([this](size_t index)
//											  {
//												  return use(index);
//											  });
}

void bomb_detonation::use(size_t for_index) {

	std::vector<size_t> neightbords;
	board_helper::neighboring_fields(for_index, neightbords, false);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(for_index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();

	auto final_damage = damage;

	for (auto& index : neightbords)
	{
		auto id = board::at(index);
		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
			return *ptr == id;
		});
		if (it != buffer->end()) {
			final_damage += 5;
		}
	}

	for (auto& index : neightbords)
	{
		if (!board::empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index)));
		}
	}

	entity_manager::destroy(bomb_id);
}

void bomb_detonation(std::size_t bomb_id, int damage) {

	auto index = board::index_for(bomb_id);

	std::vector<size_t> neightbords;
	board_helper::neighboring_fields(index, neightbords, false);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();

//	auto final_damage = damage;
//
//	for (auto& index : neightbords)
//	{
//		auto id = board::at(index);
//		auto it = std::find_if(buffer->begin(), buffer->end(), [id](auto& ptr) {
//			return *ptr == id;
//		});
//		if (it != buffer->end()) {
//			final_damage += 5;
//		}
//	}

	for (auto& index : neightbords)
	{
		if (!board::empty(index)) {
			damage_dealers::standard_damage_dealer(special_damage(damage, board::at(index)));
		}

	}

	entity_manager::destroy(bomb_id);
}

bomb::bomb() : bombs(3) {

	onEveryRound([this]() {
		bombs_to_throw = 2;
	});

	onTwoTurns([this]() {

		//static int counter = 0;

		//if (counter++ % 2 == 0) {

			std::unordered_map<std::size_t, int> damages;

			for (auto&& bomb : bombs) {
				if (bomb.second) {

					damages[*bomb.first] = 5;

					auto index = board::index_for(*bomb.first);

					std::vector<size_t> neightbords;
					board_helper::neighboring_fields(index, neightbords, false);

					for (auto& idx : neightbords) {
						auto id = board::at(idx);
						auto it = std::find_if(bombs.begin(), bombs.end(), [id](auto& pack) {
							return *pack.first == id;
						});
						if (it != bombs.end()) {
							damages[*bomb.first] += 5;
						}
					}
				}
			}

			for (auto&& bomb : bombs) {
				if (bomb.second) {
					bomb_detonation(*bomb.first, damages[*bomb.first]);
				}
			}
			for (auto&& bomb : bombs) {
				bomb.second = true;
			}
		//}
	});
}

void bomb::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;
	states::state_controller::actual_state_ = states::states_types::wait_for_action;

	path_finder path_finder;
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
									   states::state_controller::possible_movements_costs_,
									   range);

	states::state_controller::actual_targeting_type_ = states::target_types::moving;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void bomb::use(size_t index) {

	if (bombs_to_throw == 0) {
		return;
	}

	--bombs_to_throw;

	auto bomb_id = entity_manager::create<bomb_instance>();

//	auto ability = abilities_manager::component_for(bomb_id).type(abilities::ability_types::passive);
//	std::shared_ptr<bomb_detonation> bd = std::static_pointer_cast<bomb_detonation>(ability);
//	bd->set_bomb_buffer(&bombs);

	auto player = players::active_player_name();
	players::add_entity_for_player(player, bomb_id);

	board::insert(index, bomb_id);

	bombs.push_back(std::make_pair(std::shared_ptr<std::size_t>(new std::size_t(bomb_id), [](std::size_t *id){
		entity_manager::destroy(*id);
		delete id;
	}), false));
}