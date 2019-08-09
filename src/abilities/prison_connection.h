#pragma once

#include <abilities/path_target_ability.h>
#include <abilities/per_turn_usable.h>

class prison_connection : public path_target_ability, per_turn_usable {
public:
	explicit prison_connection(std::uint32_t entity_id);

	ADD_BITMAP_GETTER(prison_connection)

	DEFINE_DESC(prison_connection, base_damage, damage_per_entities_with_effect, duration)

	bool usable() const override {
		return !used;
	}

private:
	void use(std::uint32_t index_on) override;

	const std::uint32_t entity_id;
	const std::int32_t base_damage{6};
	const std::int32_t damage_per_entities_with_effect{2};
	const std::int32_t duration{3};
	std::deque<std::uint32_t> entities_with_effect;
};
