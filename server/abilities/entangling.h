//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_ENTANGLING_H
#define PIGEONWAR_ENTANGLING_H

#include <core/turn.h>
#include <entities/entity.h>
#include "ability.h"

//struct entangling_life_suck final : public ability, turn_events_helper::every_turn_callback_helper {
//    explicit entangling_life_suck();
//
//    bitmap_key get_bitmap_key() const override {
//        return bitmap_key::entangling_life_suck;
//    }
//
//    void prepare(sf::Uint64 for_index) override {}
//    void set_enemy_id(sf::Uint64 id) {
//        enemy_id = id;
//    }
//    void set_caster_id(sf::Uint64 id) {
//        caster_id = id;
//    }
//private:
//    sf::Uint64 enemy_id{std::numeric_limits<sf::Uint64>::max()};
//    sf::Uint64 caster_id{std::numeric_limits<sf::Uint64>::max()};
//    sf::Int32 damage{4};
//};
//
//struct entangling_instance {
//    static auto create(sf::Uint64 id)
//    {
//        base_components components;
//        entity_name(components) = "Oplątanie";
//        entity_health(components).base_health = 5;
//        entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<entangling_life_suck>());
//        return components;
//    }
//};
//
//class entangling final : public ability, turn_events_helper::every_turn_callback_helper
//{
//public:
//    explicit entangling(sf::Uint64 id);
//
//    bitmap_key get_bitmap_key() const override {
//        return bitmap_key::entangling;
//    }
//
//private:
//    void prepare(sf::Uint64 for_index) override;
//    void use(sf::Uint64 index_on);
//
//    const sf::Int32 range = 2;
//    const sf::Int32 damage = 5;
//    bool used{false};
//    sf::Uint64 entity_id;
//};


#endif //PIGEONWAR_ENTANGLING_H
