#pragma once

#include <turn_based/ability.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/components/modification.h>
#include <turn_based/game_controller.h>
#include <turn_based/path_finder.h>
#include <turn_based/states.h>

class path_target_ability : public ranged_ability {
public:
  path_target_ability(std::string name, std::int32_t range,
                               target_types target_type = target_types::enemy, bool all_fields = true)
      : ranged_ability(std::move(name)),
        entity_id_(std::numeric_limits<std::uint32_t>::max()),
        target_type(target_type),
        all_fields(all_fields) {
    this->range = range;
  }

  explicit path_target_ability(std::int32_t range, target_types target_type = target_types::enemy, bool all_fields = true)
    : path_target_ability("", range, target_type, all_fields) {}

  explicit path_target_ability(std::uint32_t entity_id,
                               std::int32_t range,
                               target_types target_type = target_types::enemy,
                               bool all_fields = true)
    : entity_id_(entity_id),
      target_type(target_type),
      all_fields(all_fields) {
    this->range = range;
  }

  void prepare(std::uint32_t for_index) override {
    auto range = this->range;

    if (entity_id_ != null_entity_id) {
      auto modifications = game_get<entity_manager>().get(entity_id_).get<modification>();

      switch (target_type) {
        case target_types::enemy:
          range += modifications->value(modifiers::shot_range);
          range = std::max(1, range);
          break;

        case target_types::moving:
          range += modifications->value(modifiers::move_range);
          range = std::max(1, range);
          break;

        case target_types::friendly:
        case target_types::caster:
        case target_types::neutral:
        case target_types::all:
        case target_types::non:
          break;
      }
    }

    game_control().selected_index_ = for_index;

    path_finder path_finder(all_fields);
    path_finder.calc(for_index);
    path_finder.get_possible_movements(game_control().possible_movements_,
                                       game_control().possible_movements_costs_,
                                       range);

    game_control().actual_targeting_type_ = target_type;
    game_control().wait_for_action([this](std::uint32_t index) {
      return use(index);
    });
  }

  virtual void use(std::uint32_t use_on_index) = 0;

protected:
  entity_id_t entity_id_;
  const target_types target_type;
  const bool all_fields;
};
