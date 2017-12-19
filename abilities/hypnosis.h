//
// Created by abrdej on 07.12.17.
//

#ifndef PIGEONWAR_HYPNOSIS_H
#define PIGEONWAR_HYPNOSIS_H

#include "abilities/ability.h"
#include "core/turn.h"

class hypnosis final : public ability
{
public:
	hypnosis();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::hypnosis;
	}
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t to_index);

private:
	bool used{false};
	const int range{4};
};

#endif //PIGEONWAR_HYPNOSIS_H
