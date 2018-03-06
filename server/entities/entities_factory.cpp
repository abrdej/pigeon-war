#include "entities_factory.h"

#include "scenarios/registered_entities.h"
#include "grenadier.h"

using creator = std::pair<std::string, std::function<std::uint32_t()>>;

template <typename T>
creator def_creator(const std::string& entity_name) {
    return creator(entity_name, []() {
        return entity_manager::create<T>();
    });
}

#define DEF_CREATOR(name) \
    def_creator<name>(#name) \

std::uint32_t entities_factory::create(const std::string& entity_name) {

    static std::unordered_map<std::string, std::function<std::uint32_t()>> creators = {
            DEF_CREATOR(stone),
            DEF_CREATOR(wall),
            DEF_CREATOR(tree),
            DEF_CREATOR(fir),
            DEF_CREATOR(wretch),
            DEF_CREATOR(wizzard),
            DEF_CREATOR(warrior),
            DEF_CREATOR(troll),
            DEF_CREATOR(thrower),
            DEF_CREATOR(spider),
            DEF_CREATOR(soul_hunter),
            DEF_CREATOR(sorcerer),
            DEF_CREATOR(sniper),
            DEF_CREATOR(shooter),
            DEF_CREATOR(samurai_rat),
            DEF_CREATOR(saberhand),
            DEF_CREATOR(robot),
            DEF_CREATOR(poisoner),
            DEF_CREATOR(native),
            DEF_CREATOR(monk),
            DEF_CREATOR(mechanical_saw),
            DEF_CREATOR(killer),
            DEF_CREATOR(handthrower),
            DEF_CREATOR(guardian),
            DEF_CREATOR(grenadier),
            DEF_CREATOR(golem),
            DEF_CREATOR(gin),
            DEF_CREATOR(giant),
            DEF_CREATOR(druid),
            DEF_CREATOR(droid),
            DEF_CREATOR(dragon),
            DEF_CREATOR(destroyer),
            DEF_CREATOR(creature),
            DEF_CREATOR(commander),
            DEF_CREATOR(combat_robot)
    };

    return creators.at(entity_name)();
}
