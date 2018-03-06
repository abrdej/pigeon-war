#include "entities_factory.h"

#include "scenarios/registered_entities.h"

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
            DEF_CREATOR(fir)
    };

    return creators.at(entity_name)();
}
