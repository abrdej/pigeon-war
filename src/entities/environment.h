#include <entities/entity.h>
#include <components/damage_taker.h>
#include <components/modification.h>

#define ENVIRONMENT(TYPE, NAME)\
struct TYPE { \
    static void create(base_entity& entity) { \
        entity.name = #NAME; \
        entity.add<health_field>(); \
    } \
}

#define ENVIRONMENT_DESTRUCTIBLE(TYPE, NAME, HEALTH) \
struct TYPE { \
    static void create(base_entity& entity) { \
        entity.name = #NAME; \
        entity.add<health_field>(HEALTH); \
        entity.add<damage_taker>(); \
        entity.add<modification>(); \
    } \
}

ENVIRONMENT(tree, Tree);
ENVIRONMENT(fir, Fir);
ENVIRONMENT(fire, Fire);
ENVIRONMENT(stone, Stone);
ENVIRONMENT(water, Water);

ENVIRONMENT_DESTRUCTIBLE(wall, Wall, 30);
