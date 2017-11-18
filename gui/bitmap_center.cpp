#include <entities/tree.h>
#include <entities/samurai_rat.h>
#include <entities/troll.h>
#include <entities/droid.h>
#include <entities/mouse.h>
#include <entities/grenadier.h>
#include <abilities/bomb.h>
#include <entities/destroyer.h>
#include "gui/bitmap_center.h"
#include "animation/animation.h"
#include "entities/shooter.h"
#include "entities/saberhand.h"
#include "abilities/shoot.h"
#include "abilities/grenade.h"
#include "entities/wolf.h"
#include "entities/werewolf.h"
#include "abilities/drain.h"
#include "abilities/basic_melee_attack.h"
#include "entities/stone.h"
#include "entities/saurian.h"
#include "abilities/drain.h"
#include "entities/saurions_web.h"
#include "entities/native.h"


namespace view
{
std::unordered_map<std::type_index, bitmap_center::bitmap_type> bitmap_center::bitmaps_;
bitmap_center::bitmap_type bitmap_center::grass_move_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_attack_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_damage_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_selected_bitmap;

void bitmap_center::load()
{
    grass_move_bitmap.loadFromFile("grass_move.png");
    grass_attack_bitmap.loadFromFile("grass_attack.png");
    grass_damage_bitmap.loadFromFile("grass_damage.png");
    grass_selected_bitmap.loadFromFile("grass_sel.png");

    add_entity_image<shooter>("pigeon.png");
    add_entity_image<saberhand>("saberhand.png");
    add_entity_image<shoot>("bullet.png");
    add_entity_image<grenade>("grenade.png");
    add_entity_image<moveable>("moving.png");
    add_entity_image<wolf>("wolf.png");
    add_entity_image<werewolf>("werewolf.png");
    add_entity_image<drain>("wolfwere_claws.png");
    add_entity_image<basic_melee_attack>("damage.png");
    add_entity_image<animation::bum>("bum.png");
    add_entity_image<animation::claws>("claws.png");
    add_entity_image<stone>("stone.png");
    add_entity_image<tree>("tree.png");
    add_entity_image<saurian>("saurian.png");
    add_entity_image<tongue_of_fire>("tongue_of_fire.png");
    add_entity_image<sabers>("sabers.png");
    add_entity_image<invisibility>("invisibility.png");
    add_entity_image<saurions_web>("saurions_web.png");
    add_entity_image<native>("native.png");
    add_entity_image<samurai_rat>("samurai_rat.png");
    add_entity_image<sword_blow>("sword_blow.png");
    add_entity_image<troll>("troll.png");
    add_entity_image<bludgeon>("bludgeon.png");
    add_entity_image<rage>("hello.png");
    add_entity_image<mouse>("rattati.png");
    add_entity_image<poisoned_missile>("poisoned_missile.png");
    add_entity_image<droid>("droid.png");
    add_entity_image<laser>("laser.png");
    add_entity_image<teleport>("teleport.png");
    add_entity_image<dodge>("dodge.png");
    add_entity_image<grenadier>("grenadier.png");
    add_entity_image<bomb>("bomb.png");
    add_entity_image<bomb_instance>("bomb.png");
    add_entity_image<bomb_detonation>("bomb.png");
    add_entity_image<wolf_herd>("wolf_herd.png");
    add_entity_image<destroyer>("destroyer.png");
    add_entity_image<armor>("armor.png");
    add_entity_image<blow_the_ax>("blow_the_ax.png");
}
}