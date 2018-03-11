#include <unordered_map>
#include "drawer_factory.h"
#include "entity_drawer.h"

std::shared_ptr<drawable> drawer_factory::create(std::uint32_t entity_id, const std::string& entity_name) {

	const std::unordered_map<std::string, bitmap_key> bitmaps = {
			{"Absorber", "absorber},
			{"Combat Robot", "combat_robot},
			{"Fiery Hedgehog", "creature},
			{"Destroyer", "destroyer},
			{"Droid", "droid},
			{"Fir", "fir},
			{"Fire", "fire},
			{"Giant", "giant},
			{"Golem", "golem},
			{"Grenadier", "grenadier},
			{"Guardian", "guardian},
			{"Handthrower", "handthrower},
			{"Killer", "killer},
			{"Monk", "monk},
			{"Native", "native},
			{"Ninja", "ninja},
			{"Poisoner", "mouse},
			{"Robot", "robot},
			{"Saberhand", "saberhand},
			{"Samurai", "samurai_rat},
			{"Saurian", "saurian},
			{"Shooter", "shooter},
			{"Sniper", "sniper},
			{"Sorcerer", "sorcerer},
			{"Spider", "spider},
			{"Stone", "stone},
			{"Rocket Thrower", "thrower},
			{"Treant", "treant},
			{"Tree", "tree},
			{"Troll", "troll},
			{"Wall", "wall},
			{"Warrior", "warrior},
			{"Water", "water},
			{"Werewolf", "werewolf},
			{"Wolf", "wolf},
			{"Wretch", "wretch},
			{"Druid", "druid},
			{"Soul Hunter", "soul_hunter},
			{"Mechanical Saw", "mechanical_saw},
			{"Commander", "commander},
			{"Gin", "gin},
			{"Wizzard", "wizzard},
			{"Dragon", "dragon}
	};



	try {
		bitmap_key bmt_key = bitmaps.at(entity_name);
		return std::make_shared<entity_drawer>(entity_id, bmt_key);

	} catch (const std::out_of_range& e) {
		std::cout << "No bitmap key for " << entity_name << "\n";

		return nullptr;
	}
}