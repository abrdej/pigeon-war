//
// Created by abrdej on 11.01.18.
//

#ifndef PIGEONWAR_DEATH_MARK_H
#define PIGEONWAR_DEATH_MARK_H

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>


class death_mark : public path_target_ability {
public:
	explicit death_mark(std::uint32_t entity_id);
	~death_mark();

	bitmap_key get_name() const override {
		return "assassin_slash";
	}

private:
	void use(std::uint32_t index_on) override;

	std::uint32_t entity_id;
	std::uint32_t enemy_id{std::numeric_limits<std::uint32_t>::max()};
	std::int32_t death_mark_duration{5};
	bool used{false};
	bool mark_removed{false};
};


#endif //PIGEONWAR_DEATH_MARK_H
