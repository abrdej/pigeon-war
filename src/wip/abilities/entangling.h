//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_ENTANGLING_H
#define PIGEONWAR_ENTANGLING_H

#include <turn_based/turn_system.h>
#include <turn_based/entity.h>
#include <turn_based/ability.h>

//struct entangling_life_suck final : public active_ability, turn_callback_helper {
//    explicit entangling_life_suck();
//
//    bitmap_key get_name() const override {
//        return "entangling_life_suck;
//    }
//
//    void prepare(std::uint32_t for_index) override {}
//    void set_enemy_id(std::uint32_t id) {
//        enemy_id = id;
//    }
//    void set_caster_id(std::uint32_t id) {
//        caster_id = id;
//    }
//private:
//    std::uint32_t enemy_id{std::numeric_limits<std::uint32_t>::max()};
//    std::uint32_t caster_id{std::numeric_limits<std::uint32_t>::max()};
//    std::int32_t damage{4};
//};
//
//struct entangling_instance {
//    static auto create(base_entity& entity)
//    {
//        base_components components;
//        entity_name(components) = "Oplątanie";
//        entity_health(components).base_health = 5;
//        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<entangling_life_suck>());
//        return components;
//    }
//};
//
//class entangling final : public active_ability, turn_callback_helper
//{
//public:
//    explicit entangling(std::uint32_t id);
//
//    bitmap_key get_name() const override {
//        return "entangling;
//    }
//
//private:
//    void prepare(std::uint32_t for_index) override;
//    void use(std::uint32_t index_on);
//
//    const std::int32_t range = 2;
//    const std::int32_t damage = 5;
//    bool used{false};
//    std::uint32_t entity_id;
//};


#endif //PIGEONWAR_ENTANGLING_H
