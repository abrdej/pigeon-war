#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>
#include <typeinfo>
#include <unordered_map>
#include <functional>
#include <common/bitmaps.h>
#include <descriptions.h>

/**
 * Base class for all abilities.
 * Abilities can be active and passive.
 *
 */

enum class ability_types { moving = 0, offensive, special, defensive, passive, not_defined };

class ability
{
protected:
	virtual ~ability() = default;

public:
	virtual std::string hint() const {
        std::string desc("desc");
        return std::move(desc);
	}
    virtual ability_types type() const {
        return ability_types::not_defined;
    }

	virtual bitmap_key get_bitmap_key() const = 0;
};

struct active_ability : ability {
	virtual void prepare(std::uint32_t for_index) = 0;
};

struct passive_ability : ability {

};

inline void try_prepare_ability(ability& x, std::uint32_t for_index) {
    try {
        dynamic_cast<active_ability&>(x).prepare(for_index);
    } catch (std::bad_cast&) {

    }
}

#define MOVING_ABILITY() \
ability_types type() const override { \
    return ability_types::moving; \
} \

#endif