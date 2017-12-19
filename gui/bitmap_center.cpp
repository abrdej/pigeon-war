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
std::unordered_map<bitmap_key, bitmap_center::bitmap_type> bitmap_center::bitmaps;

bitmap_center::bitmap_type bitmap_center::grass_move_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_attack_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_damage_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_selected_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_friendly_bitmap;
bitmap_center::bitmap_type bitmap_center::grass_boost_bitmap;

void bitmap_center::load()
{
    grass_move_bitmap.loadFromFile(resources_directory + "grass_move.png");
    grass_attack_bitmap.loadFromFile(resources_directory + "grass_attack.png");
    grass_damage_bitmap.loadFromFile(resources_directory + "grass_damage.png");
    grass_selected_bitmap.loadFromFile(resources_directory + "grass_sel.png");
    grass_friendly_bitmap.loadFromFile(resources_directory + "grass_friendly.png");
    grass_boost_bitmap.loadFromFile(resources_directory + "grass_boost.png");

    add_bitmap(bitmap_key::shooter, "shooter.png");
    add_bitmap(bitmap_key::saberhand, "saberhand.png");
    add_bitmap(bitmap_key::saberhand_transparency, "saberhand_transparency.png");
    add_bitmap(bitmap_key::shoot, "bullet.png");
    add_bitmap(bitmap_key::grenade, "grenade.png");
    add_bitmap(bitmap_key::moveable, "moving.png");
    add_bitmap(bitmap_key::wolf, "wolf.png");
    add_bitmap(bitmap_key::werewolf, "werewolf.png");
    add_bitmap(bitmap_key::drain, "wolfwere_claws.png");
    add_bitmap(bitmap_key::basic_melee_attack, "damage.png");
    add_bitmap(bitmap_key::bum, "bum.png");
    add_bitmap(bitmap_key::claws, "claws.png");
    add_bitmap(bitmap_key::stone, "stone.png");
    add_bitmap(bitmap_key::tree, "tree.png");
    add_bitmap(bitmap_key::saurian, "saurian.png");
    add_bitmap(bitmap_key::tongue_of_fire, "tongue_of_fire.png");
    add_bitmap(bitmap_key::sabers, "sabers.png");
    add_bitmap(bitmap_key::invisibility, "invisibility.png");
    add_bitmap(bitmap_key::saurions_web, "saurions_web.png");
    add_bitmap(bitmap_key::native, "native.png");
    add_bitmap(bitmap_key::samurai_rat, "samurai_rat.png");
    add_bitmap(bitmap_key::sword_blow, "sword_blow.png");
    add_bitmap(bitmap_key::troll, "troll.png");
    add_bitmap(bitmap_key::bludgeon, "bludgeon.png");
    add_bitmap(bitmap_key::rage, "hello.png");
    add_bitmap(bitmap_key::mouse, "rattati.png");
    add_bitmap(bitmap_key::poisoned_missile, "poisoned_missile.png");
    add_bitmap(bitmap_key::droid, "droid.png");
    add_bitmap(bitmap_key::laser, "laser.png");
    add_bitmap(bitmap_key::teleport, "teleport.png");
    add_bitmap(bitmap_key::dodge, "dodge.png");
    add_bitmap(bitmap_key::grenadier, "grenadier.png");
    add_bitmap(bitmap_key::bomb, "bomb.png");
    add_bitmap(bitmap_key::bomb_instance, "bomb.png");
    add_bitmap(bitmap_key::bomb_detonation, "bomb.png");
    add_bitmap(bitmap_key::wolf_herd, "wolf_herd.png");
    add_bitmap(bitmap_key::destroyer, "destroyer.png");
    add_bitmap(bitmap_key::armor, "armor.png");
    add_bitmap(bitmap_key::blow_the_ax, "blow_the_ax.png");
    add_bitmap(bitmap_key::treant, "treant.png");
    add_bitmap(bitmap_key::entangling_instance, "entangling.png");
    add_bitmap(bitmap_key::entangling, "entangling.png");
    add_bitmap(bitmap_key::entangling_life_suck, "entangling.png");
    add_bitmap(bitmap_key::recovery, "recovery.png");
    add_bitmap(bitmap_key::fire, "fire.png");
    add_bitmap(bitmap_key::balloon, "balloon.png");
    add_bitmap(bitmap_key::build_cannon, "cannon.png");
    add_bitmap(bitmap_key::cannon, "cannon.png");
    add_bitmap(bitmap_key::build_barrack, "barrack.png");
    add_bitmap(bitmap_key::barrack, "barrack.png");
    add_bitmap(bitmap_key::thrower, "mouse.png");
    add_bitmap(bitmap_key::flame_thrower, "flame_thrower.png");
    add_bitmap(bitmap_key::counterattack, "native.png");
    add_bitmap(bitmap_key::guardian, "guardian.png");
    add_bitmap(bitmap_key::spear, "spear.png");
    add_bitmap(bitmap_key::shield, "shield.png");
    add_bitmap(bitmap_key::creature, "creature.png");
    add_bitmap(bitmap_key::creature_fired, "creature_fired.png");
    add_bitmap(bitmap_key::chopper, "chopper.png");
    add_bitmap(bitmap_key::spiral_of_fire, "spiral_of_fire.png");
    add_bitmap(bitmap_key::handthrower, "handthrower.png");
    add_bitmap(bitmap_key::handcannon, "handcannon.png");
    add_bitmap(bitmap_key::protection_field, "protection_field.png");
    add_bitmap(bitmap_key::warrior, "warrior.png");
    add_bitmap(bitmap_key::warrior_blow, "warrior_blow.png");
    add_bitmap(bitmap_key::immortality, "warrior_immortal.png");
    add_bitmap(bitmap_key::robot, "robot.png");
    add_bitmap(bitmap_key::spider, "spider.png");
    add_bitmap(bitmap_key::spider_web, "web.png");
    add_bitmap(bitmap_key::surroundings, "spider.png");
    add_bitmap(bitmap_key::detonation, "detonation.png");
    add_bitmap(bitmap_key::sniper, "sniper.png");
    add_bitmap(bitmap_key::sniper_shot, "sniper_shoot.png");
    add_bitmap(bitmap_key::hypnosis, "field_shoot.png");
    add_bitmap(bitmap_key::monk, "monk.png");
    add_bitmap(bitmap_key::magic_bullet, "magic_bullet.png");
    add_bitmap(bitmap_key::jaw_spider, "jaw_spider.png");
    add_bitmap(bitmap_key::long_range_missile, "flame_thrower.png");
    add_bitmap(bitmap_key::ninja, "ninja_shirukens.png");
    add_bitmap(bitmap_key::shiruken, "shiruken.png");
    add_bitmap(bitmap_key::assassin_slash, "assassin_slash.png");
    add_bitmap(bitmap_key::interception, "ninja.png");
    add_bitmap(bitmap_key::absorber, "absorber.png");
    add_bitmap(bitmap_key::absorption, "absorption.png");
    add_bitmap(bitmap_key::power_circle, "power_circle.png");
    add_bitmap(bitmap_key::water, "water.png");
    add_bitmap(bitmap_key::wall, "wall.png");
    add_bitmap(bitmap_key::fir, "fir.png");
    add_bitmap(bitmap_key::wretch, "wretch.png");
    add_bitmap(bitmap_key::wretch_moving, "moving.png");
    add_bitmap(bitmap_key::vicious_circle, "water.png");
}
}