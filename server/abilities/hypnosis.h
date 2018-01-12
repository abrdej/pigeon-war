//
// Created by abrdej on 07.12.17.
//

#ifndef PIGEONWAR_HYPNOSIS_H
#define PIGEONWAR_HYPNOSIS_H

#include "path_target_ability.h"

class hypnosis final : public path_target_ability<4, states::target_types::enemy, true>
{
public:
	bitmap_key get_bitmap_key() const override {
		return bitmap_key::hypnosis;
	}

	std::string hint() const override;

private:
	void use(size_t index_on);

private:
	bool used{false};
	const int range{4};
};

#endif //PIGEONWAR_HYPNOSIS_H
