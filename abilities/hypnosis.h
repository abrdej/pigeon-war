//
// Created by abrdej on 07.12.17.
//

#ifndef PIGEONWAR_HYPNOSIS_H
#define PIGEONWAR_HYPNOSIS_H

#include "abilities/ability.h"
#include "core/turn.h"

struct hypnosis_effect {
	hypnosis_effect(std::size_t receiver_entity_id);
	std::shared_ptr<std::function<void()>> rec;
	std::function<void()> destroyer;
	std::shared_ptr<ability> moveable_backup;
};

class hypnosis final : public ability
{
public:
	hypnosis();
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t to_index);

private:
	bool used{false};
	const int range{5};
};

#endif //PIGEONWAR_HYPNOSIS_H
