#include "saurian_web.h"

#include <components/damage_taker.h>
#include <components/health_field.h>

void saurian_web::create(base_entity& entity)
{
    entity.name = "Saurian Web";

    entity.add<health_field>(20);
    entity.add<damage_taker>();
}
