#include <unordered_map>
#include "drawer_factory.h"
#include "entity_drawer.h"

std::shared_ptr<drawable> drawer_factory::create(std::uint32_t entity_id, const std::string& entity_name) {

	const std::unordered_map<std::string, bitmap_key> bitmaps = {
			{"Absorber", bitmap_key::absorber},
			{"Combat Robot", bitmap_key::combat_robot},
			{"Fiery Hedgehog", bitmap_key::creature},
			{"Destroyer", bitmap_key::destroyer},
			{"Droid", bitmap_key::droid},
			{"Fir", bitmap_key::fir},
			{"Fire", bitmap_key::fire},
			{"Giant", bitmap_key::giant},
			{"Golem", bitmap_key::golem},
			{"Grenadier", bitmap_key::grenadier},
			{"Guardian", bitmap_key::guardian},
			{"Handthrower", bitmap_key::handthrower},
			{"Killer", bitmap_key::killer},
			{"Monk", bitmap_key::monk},
			{"Native", bitmap_key::native},
			{"Ninja", bitmap_key::ninja},
			{"Poisoner", bitmap_key::mouse},
			{"Robot", bitmap_key::robot},
			{"Saberhand", bitmap_key::saberhand},
			{"Samurai", bitmap_key::samurai_rat},
			{"Saurian", bitmap_key::saurian},
			{"Shooter", bitmap_key::shooter},
			{"Sniper", bitmap_key::sniper},
			{"Sorcerer", bitmap_key::sorcerer},
			{"Spider", bitmap_key::spider},
			{"Stone", bitmap_key::stone},
			{"Rocket Thrower", bitmap_key::thrower},
			{"Treant", bitmap_key::treant},
			{"Tree", bitmap_key::tree},
			{"Troll", bitmap_key::troll},
			{"Wall", bitmap_key::wall},
			{"Warrior", bitmap_key::warrior},
			{"Water", bitmap_key::water},
			{"Werewolf", bitmap_key::werewolf},
			{"Wolf", bitmap_key::wolf},
			{"Wretch", bitmap_key::wretch},
			{"Druid", bitmap_key::druid},
			{"Soul Hunter", bitmap_key::soul_hunter},
			{"Mechanical Saw", bitmap_key::mechanical_saw}
	};



	try {
		bitmap_key bmt_key = bitmaps.at(entity_name);
		return std::make_shared<entity_drawer>(entity_id, bmt_key);

	} catch (const std::out_of_range& e) {
		std::cout << "No bitmap key for " << entity_name << "\n";

		return nullptr;
	}
}