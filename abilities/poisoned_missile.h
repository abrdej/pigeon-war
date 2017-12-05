//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_POISONED_MISSILE_H
#define PIGEONWAR_POISONED_MISSILE_H

#include "abilities/ability.h"
#include "core/turn.h"

struct poisoned_missile_callback {
    poisoned_missile_callback(int poison_damage, int poison_last, std::size_t receiver_entity_id);
    std::shared_ptr<std::function<void()>> rec;
    std::function<void()> destroyer;
};

class poisoned_missile final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    poisoned_missile();
private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);

private:
    const size_t range_{4};
    const size_t damage_{6};
    const int poison_power_{3};
    const int poison_last_{3};
    bool used{false};

    std::unordered_map<int, std::shared_ptr<std::function<void()>>> rec;
};

#endif //PIGEONWAR_POISONED_MISSILE_H
