//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_SPIDER_WEB_H
#define PIGEONWAR_SPIDER_WEB_H

#include "abilities/ability.h"
#include "core/turn.h"

struct spider_web_slowdown {
    spider_web_slowdown(float slow_down_to, int slow_last, std::size_t receiver_entity_id);
    std::shared_ptr<std::function<void()>> rec;
    std::function<void()> destroyer;
    std::shared_ptr<ability> moveable_backup;
};

class spider_web final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    explicit spider_web(std::size_t entity_id);
private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);

private:
    std::size_t entity_id;
    int range = 5;
    int damage = 6;
    bool used{false};
};

#endif //PIGEONWAR_SPIDER_WEB_H
