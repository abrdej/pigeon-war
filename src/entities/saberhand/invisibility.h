#pragma once

#include "abilities/caster_target_ability.h"
#include "core/turn_system.h"

class invisibility final : public caster_target_ability
{
public:
	explicit invisibility(std::uint32_t id);

	ADD_BITMAP_GETTER(invisibility);
	DEFINE_DESC_ONE(invisibility, duration)

	bool usable() const override {
		return !used_;
	}

private:
	void use(std::uint32_t on_index) override;
	void hide_me();
	void show_me();
private:
	bool used_{false};
	const std::uint32_t entity_id;
	std::uint32_t index{0};
	std::int32_t turn_counter_{0};
	const std::int32_t duration{2};
	turn_scoped_connection invisibility_callback;
};
