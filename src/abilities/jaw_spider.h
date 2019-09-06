#ifndef PIGEONWAR_JAW_SPIDER_H
#define PIGEONWAR_JAW_SPIDER_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class jaw_spider final : public neighboring_target_ability<>, per_turn_usable {
 public:
  bitmap_key get_bitmap_key() const override { return "jaw_spider"; }

  DEFINE_DESC(jaw_spider, damage, bonus_for_spider_web_effect)

  void set_used();

  bool usable() const override { return !used; }

 private:
  void use(std::uint32_t index_on) override;

 private:
  const std::int32_t damage = 8;
  const std::int32_t bonus_for_spider_web_effect = 6;
};

#endif  // PIGEONWAR_JAW_SPIDER_H
