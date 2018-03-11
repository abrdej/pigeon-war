#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "ability.h"
#include "core/turn_system.h"
#include <functional>
#include "effects/base_effect.h"

class moveable_base : public active_ability {
    using move_callback_type = std::function<void(std::uint32_t, std::uint32_t, std::int32_t)>;

    std::unordered_map<std::uint32_t, moveable_base::move_callback_type> move_callbacks;

protected:
    void call_move_callbacks(std::uint32_t from_index, std::uint32_t to_index, std::int32_t cost) {
        for (auto&& callback_pack : move_callbacks) {
            callback_pack.second(from_index, to_index, cost);
        }
    }

public:
	MOVING_ABILITY()

    virtual void refresh_range() = 0;
    virtual bool has_range() const = 0;
    virtual void remove_range() = 0;
    virtual void set_slow_down(std::int32_t value) = 0;
    virtual void remove_slow_down() = 0;

    virtual std::uint32_t set_move_callback(move_callback_type callback) {
        static std::uint32_t callback_id_gen = 0;
        move_callbacks[callback_id_gen] = callback;
        return callback_id_gen++;
    }
    virtual void remove_move_callback(std::uint32_t callback_id) {
        move_callbacks.erase(callback_id);
    }
};

class moveable final : public moveable_base, turn_callback_helper  {
public:
    enum class types {
        path,
        straight
    };
	explicit moveable(std::int32_t range, types type = types::path)
		: range(range),
		  base_range(range),
		  movement_type(type) {
		on_every_two_turns_from_next([this]() {
			used = false;
		});
	}

	DEFINE_DESC_ONE(moveable, range)

	bitmap_key get_bitmap_key() const override {
		return "moveable";
	}

	void refresh_range() override {
		used = false;
	}

	bool has_range() const override {
		return !used;
	}

	void remove_range() override {
		used = true;
	}

	void set_slow_down(std::int32_t value) override {
		range = value;
	}
	void remove_slow_down() override {
		range = base_range;
	}

private:
	void prepare(std::uint32_t for_index) override;
	void move(std::uint32_t index_to);

private:
	std::int32_t range;
	const std::int32_t base_range;
	bool used{false};
    types movement_type;
};


#endif