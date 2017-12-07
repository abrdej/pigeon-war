#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "abilities/ability.h"
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

private:
	void prepare(size_t for_index) override;
	void move(size_t index_to);

private:
	int range;
	bool used{false};
    types type;
};

struct move_command {
    std::size_t entity_id;
    std::size_t from_index;
    std::size_t to_index;

    void operator()();
};


#endif