#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "ability.h"
#include "core/turn_system.h"
#include <functional>
#include "effects/base_effect.h"

struct aura_setter {
	void set_aura(std::uint32_t index, const std::shared_ptr<effect>& aura);
	void remove_auras(std::uint32_t index);

	std::vector<std::uint32_t> effect_ids;
};

class moveable final : public ability, turn_callback_helper, aura_setter {
public:
    enum class types {
        path,
        straight
    };
	explicit moveable(std::int32_t range, types type = types::path)
		: range(range),
          type(type) {
		on_every_two_turns_from_next([this]() {
			used = false;
		});
	}

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::moveable;
	}

	void refresh_range() {
		used = false;
	}

	bool has_range() const {
		return !used;
	}

	void remove_range() {
		used = true;
	}

	void set_cost_callback(std::function<void(std::int32_t)> fn) {
		cost_callback = fn;
	}

	void remove_cost_callback() {
		cost_callback = std::function<void(std::int32_t)>();
	}

	void add_aura(const std::shared_ptr<effect>& aura) {
		auras.push_back(aura);
	}

private:
	void prepare(std::uint32_t for_index) override;
	void move(std::uint32_t index_to);

private:
	std::int32_t range;
	bool used{false};
    types type;

	std::function<void(std::int32_t)> cost_callback;

	std::vector<std::shared_ptr<effect>> effects;

	std::vector<std::shared_ptr<effect>> auras;
};


#endif