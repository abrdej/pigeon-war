#include <entities/tree.h>
#include <entities/samurai_rat.h>
#include <entities/troll.h>
#include <entities/droid.h>
#include <entities/mouse.h>
#include <entities/grenadier.h>
#include <abilities/bomb.h>
#include <entities/destroyer.h>
#include <entities/treant.h>
#include <entities/fire.h>
#include <entities/balloon.h>
#include <entities/cannon.h>
#include <entities/barrack.h>
#include <entities/fissure.h>
#include <entities/thrower.h>
#include <abilities/counterattack.h>
#include <entities/guardian.h>
#include <entities/creature.h>
#include <abilities/spiral_of_fire.h>
#include <entities/handthrower.h>
#include <abilities/handcannon.h>
#include <entities/warrior.h>
#include <entities/robot.h>
#include <entities/spider.h>
#include <entities/sniper.h>
#include <abilities/sniper_shot.h>
#include <entities/monk.h>
#include <abilities/long_range_missile.h>
#include <entities/ninja.h>
#include <entities/absorber.h>
#include <entities/water.h>
#include <entities/wall.h>
#include <entities/fir.h>
#include <entities/wretch.h>
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
std::unordered_map<bitmap_center::key_type, bitmap_center::bitmap_type> bitmap_center::bb;
bitmap_center::bitmap_type bitmap_center::grass_move_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_attack_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_damage_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_selected_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_friendly_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_boost_bitmap;

void bitmap_center::load()
{
    std::cout << "Load\n";

    grass_move_bitmap.loadFromFile("grass_move.png");
    grass_attack_bitmap.loadFromFile("grass_attack.png");
    grass_damage_bitmap.loadFromFile("grass_damage.png");
    grass_selected_bitmap.loadFromFile("grass_sel.png");
    grass_friendly_bitmap.loadFromFile("grass_friendly.png");
    grass_boost_bitmap.loadFromFile("grass_boost.png");

    add_entity_image<shooter>("shooter.png");
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
    add_entity_image<treant>("treant.png");
    add_entity_image<entangling_instance>("entangling.png");
    add_entity_image<entangling>("entangling.png");
    add_entity_image<entangling_life_suck>("entangling.png");
    add_entity_image<recovery>("recovery.png");
    add_entity_image<fire>("fire.png");
    add_entity_image<balloon>("balloon.png");
    add_entity_image<build_cannon>("cannon.png");
    add_entity_image<cannon>("cannon.png");
    add_entity_image<build_barrack>("barrack.png");
    add_entity_image<barrack>("barrack.png");
    add_entity_image<builder<barrack>>("barrack.png");
    add_entity_image<builder<shooter>>("shooter.png");
    add_entity_image<builder<drilling_rig>>("drilling_rig.png");
    add_entity_image<drilling_rig>("drilling_rig.png");
    add_entity_image<fissure>("fissure.png");
    add_entity_image<thrower>("mouse.png");
    add_entity_image<flame_thrower>("flame_thrower.png");
    add_entity_image<counterattack>("native.png");
    add_entity_image<guardian>("guardian.png");
    add_entity_image<spear>("spear.png");
    add_entity_image<shield>("shield.png");
    add_entity_image<creature>("creature.png");
    add_entity_image<chopper>("chopper.png");
    add_entity_image<spiral_of_fire>("spiral_of_fire.png");
    add_entity_image<handthrower>("handthrower.png");
    add_entity_image<handcannon>("handcannon.png");
    add_entity_image<protection_field>("protection_field.png");
    add_entity_image<warrior>("warrior.png");
    add_entity_image<warrior_blow>("warrior_blow.png");
    add_entity_image<immortality>("warrior_immortal.png");
    add_entity_image<robot>("robot.png");
    add_entity_image<spider>("spider.png");
    add_entity_image<spider_web>("web.png");
    add_entity_image<surroundings>("spider.png");
    add_entity_image<detonation>("detonation.png");
    add_entity_image<sniper>("sniper.png");
    add_entity_image<sniper_shot>("sniper_shoot.png");
    add_entity_image<hypnosis>("field_shoot.png");
    add_entity_image<monk>("monk.png");
    add_entity_image<magic_bullet>("magic_bullet.png");
    add_entity_image<jaw_spider>("jaw_spider.png");
    add_entity_image<long_range_missile>("flame_thrower.png");
    add_entity_image<ninja>("ninja_shirukens.png");
    add_entity_image<shiruken>("shiruken.png");
    add_entity_image<assassin_slash>("assassin_slash.png");
    add_entity_image<interception>("ninja.png");
    add_entity_image<absorber>("absorber.png");
    add_entity_image<absorption>("absorption.png");
    add_entity_image<power_circle>("power_circle.png");
    add_entity_image<water>("water.png");
    add_entity_image<wall>("wall.png");
    add_entity_image<fir>("fir.png");
    add_entity_image<wretch>("wretch.png");
    add_entity_image<wretch_moving>("moving.png");

    // bitmaps
    add_bitmap("shooter", "shooter.png");
    add_bitmap("shooter_shoot", "shooter_shoot.png");
}
}