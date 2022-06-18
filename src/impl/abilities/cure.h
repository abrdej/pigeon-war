#pragma once

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class cure : public path_target_ability, per_turn_usable {
public:
	explicit cure(std::uint32_t entity_id);

	ADD_BITMAP_GETTER(cure)

	DEFINE_DESC(cure, healing_amount_per_turn_, healing_duration_, power_cost_)

	bool usable() const override;

private:
	void use(std::uint32_t index_on) override;

	std::uint32_t entity_id_;
	std::int32_t healing_amount_per_turn_{4};
	std::int32_t healing_duration_{4};
	std::int32_t power_cost_{8};
};
