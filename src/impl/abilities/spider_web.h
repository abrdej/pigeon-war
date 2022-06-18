#pragma once

#include <turn_based/per_turn_usable.h>
#include <straight_target_ability.h>

class spider_web final : public straight_target_ability<5>, per_turn_usable
{
public:
    explicit spider_web(std::uint32_t entity_id);

	ADD_BITMAP_GETTER(spider_web)

	DEFINE_DESC(spider_web, damage, range);

	void set_used();

	bool usable() const override {
		return !used;
	}

private:
    void use(std::uint32_t index_on) override;

private:
    std::uint32_t caster_id;
    std::int32_t damage = 6;
	std::int32_t duration = 3;
};
