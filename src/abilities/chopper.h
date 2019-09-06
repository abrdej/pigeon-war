//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_CHOPPER_H
#define PIGEONWAR_CHOPPER_H

#include <boost/circular_buffer.hpp>
#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class spiral_of_fire;

class chopper final : public neighboring_target_ability<>, per_turn_usable {
 public:
  explicit chopper(std::uint32_t entity_id);

  bitmap_key get_bitmap_key() const override { return "chopper"; }

 private:
  void use(std::uint32_t index_on) override;

 private:
  const std::int32_t range = 1;
  const std::int32_t no_fired_damage = 5;
  const std::int32_t fired_damage = 10;
  std::uint32_t entity_id;
  std::int32_t damage{no_fired_damage};
  bool fired{false};
  std::int32_t fired_aura_dmg{3};
  std::int32_t fired_counter{0};

  boost::circular_buffer<std::uint32_t> last_attacked{2};

  void set_fired();
  void remove_fired();

  friend class spiral_of_fire;
};

#endif  // PIGEONWAR_CHOPPER_H
