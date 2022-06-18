#include <rocket_launcher.h>

#include <turn_based/abilities.h>
#include <change_rocket_type.h>
#include <turn_based/managers/entity_manager.h>

change_rocket_type::change_rocket_type(std::uint32_t entity_id)
        : entity_id(entity_id) {}

void change_rocket_type::use(std::uint32_t index_on) {
    if (used)
        return;

    auto entity = game::get<entity_manager>().get(entity_id);
    auto rocket_launcher_ptr = entity.get<abilities>()->get<rocket_launcher>();

    if (rocket_launcher_ptr->was_used()) {
        return;
    }

    used = true;
}
