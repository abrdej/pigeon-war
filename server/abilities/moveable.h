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
	explicit moveable(sf::Int32 range, types type = types::path)
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

	void set_cost_callback(std::function<void(sf::Int32)> fn) {
		cost_callback = fn;
	}

	void remove_cost_callback() {
		cost_callback = std::function<void(sf::Int32)>();
	}

private:
	void prepare(sf::Uint64 for_index) override;
	void move(sf::Uint64 index_to);

private:
	sf::Int32 range;
	bool used{false};
    types type;

	std::function<void(sf::Int32)> cost_callback;
};


#endif