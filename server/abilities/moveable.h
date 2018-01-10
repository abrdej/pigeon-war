#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "ability.h"
#include "core/turn.h"
#include <functional>

class moveable final : public ability, turn_events_helper::every_turn_callback_helper {
public:
    enum class types {
        path,
        straight
    };
	explicit moveable(int range, types type = types::path)
		: range(range),
          type(type) {
		onEveryRound([this]() {
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

	void set_cost_callback(std::function<void(int)> fn) {
		cost_callback = fn;
	}

	void remove_cost_callback() {
		cost_callback = std::function<void(int)>();
	}

private:
	void prepare(size_t for_index) override;
	void move(size_t index_to);

private:
	int range;
	bool used{false};
    types type;

	std::function<void(int)> cost_callback;
};


#endif