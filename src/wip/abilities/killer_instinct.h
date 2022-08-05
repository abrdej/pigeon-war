//
// Created by abrdej on 08.01.18.
//

#ifndef PIGEONWAR_KILLER_INSTINCT_H
#define PIGEONWAR_KILLER_INSTINCT_H

#include <turn_based/path_target_ability.h>
#include <turn_based/move.h>

class killer_instinct : public path_target_ability {
public:
	explicit killer_instinct(std::uint32_t entity_id);
	bitmap_key get_name() const override {
		return "killer_jump";
	}

private:
	void prepare(std::uint32_t for_index) override;
	void use(std::uint32_t index) override;

	std::uint32_t entity_id;
	const std::int32_t range{7};
	bool used{false};
};


#endif //PIGEONWAR_KILLER_INSTINCT_H
