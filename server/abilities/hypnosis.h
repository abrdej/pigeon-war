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
	void use(std::uint64_t index_on);

private:
	bool used{false};
	const std::int32_t range{4};
};

#endif //PIGEONWAR_HYPNOSIS_H
