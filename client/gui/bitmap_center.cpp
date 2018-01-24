#include <client/gui/bitmap_center.h>

namespace view
{
std::unordered_map<bitmap_key, bitmap_center::bitmap_type, bitmaps_key_hash> bitmap_center::bitmaps;

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
    add_bitmap(bitmap_key::drain, "drain.png");
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
    add_bitmap(bitmap_key::rage, "rage.png");
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
    add_bitmap(bitmap_key::counterattack, "counter_attack.png");
    add_bitmap(bitmap_key::guardian, "guardian.png");
    add_bitmap(bitmap_key::spear, "spear.png");
    add_bitmap(bitmap_key::shield, "shield.png");
    add_bitmap(bitmap_key::creature, "creature.png");
    add_bitmap(bitmap_key::creature_fired, "creature_fired.png");
    add_bitmap(bitmap_key::chopper, "chopper.png");
    add_bitmap(bitmap_key::spiral_of_fire, "spiral_of_fire.png");
    add_bitmap(bitmap_key::handthrower, "handthrower.png");
    add_bitmap(bitmap_key::handcannon, "handcannon.png");
    add_bitmap(bitmap_key::handcannonbum, "handcannonbum.png");
    add_bitmap(bitmap_key::protection_field, "protection_field.png");
    add_bitmap(bitmap_key::warrior, "warrior.png");
    add_bitmap(bitmap_key::warrior_blow, "warrior_blow.png");
    add_bitmap(bitmap_key::immortality, "warrior_immortal.png");
    add_bitmap(bitmap_key::robot, "robot.png");
    add_bitmap(bitmap_key::spider, "spider.png");
    add_bitmap(bitmap_key::spider_web, "web.png");
    add_bitmap(bitmap_key::surroundings, "surroundings.png");
    add_bitmap(bitmap_key::detonation, "detonation.png");
    add_bitmap(bitmap_key::sniper, "sniper.png");
    add_bitmap(bitmap_key::sniper_shot, "sniper_shoot.png");
    add_bitmap(bitmap_key::hypnosis, "field_shoot.png");
    add_bitmap(bitmap_key::monk, "monk.png");
    add_bitmap(bitmap_key::magic_bullet, "magic_bullet.png");
    add_bitmap(bitmap_key::jaw_spider, "jaw_spider.png");
    add_bitmap(bitmap_key::long_range_missile, "flame_thrower.png");
    add_bitmap(bitmap_key::ninja, "ninja_shirukens.png");
    add_bitmap(bitmap_key::ninja_attack, "ninja_attack.png");
    add_bitmap(bitmap_key::shiruken, "shiruken.png");
    add_bitmap(bitmap_key::native_attack, "native_attack.png");
    add_bitmap(bitmap_key::shards, "shards.png");
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
    add_bitmap(bitmap_key::monk_use_1, "monk_use_1.png");
    add_bitmap(bitmap_key::monk_use_2, "monk_use_2.png");
    add_bitmap(bitmap_key::monk_use_3, "monk_use_3.png");
    add_bitmap(bitmap_key::magic_splash, "magic_splash.png");
    add_bitmap(bitmap_key::warrior_attack, "warrior_attack.png");
    add_bitmap(bitmap_key::samurai_rat_sword, "samurai_rat_sword.png");
    add_bitmap(bitmap_key::guardian_attack, "guardian_attack.png");
    add_bitmap(bitmap_key::sniper_bum, "sniper_bum.png");
    add_bitmap(bitmap_key::shiruken_splash, "shiruken_splash.png");
    add_bitmap(bitmap_key::sabers_attack, "sabers_attack.png");
    add_bitmap(bitmap_key::healthing, "healthing.png");
    add_bitmap(bitmap_key::field_shoot, "field_shoot.png");
    add_bitmap(bitmap_key::poisoned_missile_splush, "poisoned_missile_splush.png");
    add_bitmap(bitmap_key::absorber_orbit, "absorber_orbit2.png");
    add_bitmap(bitmap_key::troll_rage, "troll_rage.png");
    add_bitmap(bitmap_key::hello, "hello.png");
    add_bitmap(bitmap_key::detonation_anim, "detonation_anim.png");
    add_bitmap(bitmap_key::magic_suck, "magic_suck.png");
    add_bitmap(bitmap_key::vicious_circle, "magic_energy.png");
    add_bitmap(bitmap_key::killer, "killer.png");
    add_bitmap(bitmap_key::giant, "giant.png");
    add_bitmap(bitmap_key::kill, "kill.png");
    add_bitmap(bitmap_key::magic_energy, "magic_energy.png");
    add_bitmap(bitmap_key::killer_jump, "killer_jump.png");
    add_bitmap(bitmap_key::killer_attack, "killer_attack.png");
    add_bitmap(bitmap_key::defender, "defender.png");
    add_bitmap(bitmap_key::giant_blow, "giant_blow.png");
    add_bitmap(bitmap_key::giant_blow_special, "giant_blow_special.png");
    add_bitmap(bitmap_key::defender_attack, "defender_attack.png");
    add_bitmap(bitmap_key::giant_ram, "giant_ram.png");
    add_bitmap(bitmap_key::golem, "golem.png");
    add_bitmap(bitmap_key::stone_skin, "stone_skin.png");
    add_bitmap(bitmap_key::power_bullet, "power_bullet.png");
    add_bitmap(bitmap_key::power_bullet_bum, "power_bullet_bum.png");
    add_bitmap(bitmap_key::sorcerer, "sorcerer.png");
    add_bitmap(bitmap_key::sorcerer_attack, "sorcerer_attack.png");
    add_bitmap(bitmap_key::warrior_immortal, "warrior_imm.png");
    add_bitmap(bitmap_key::prison_connection, "prison_connection.png");
    add_bitmap(bitmap_key::poison_effect, "poison_effect.png");
    add_bitmap(bitmap_key::rocket, "rocket_thrower.png");
    add_bitmap(bitmap_key::change_rocket_type, "mortar_thrower.png");
    add_bitmap(bitmap_key::combat_robot, "combat_robot.png");
    add_bitmap(bitmap_key::druid, "druid.png");
    add_bitmap(bitmap_key::cure, "cure.png");
    add_bitmap(bitmap_key::cure_anim, "cure_anim.png");
    add_bitmap(bitmap_key::portal, "portal.png");
    add_bitmap(bitmap_key::portal_1, "portal_1.png");
    add_bitmap(bitmap_key::portal_2, "portal_2.png");
    add_bitmap(bitmap_key::portal_3, "portal_3.png");
    add_bitmap(bitmap_key::lightning, "lightning.png");
    add_bitmap(bitmap_key::lightning_prepare, "lightning_prepare.png");
    add_bitmap(bitmap_key::ball_and_chain, "ball_and_chain.png");
    add_bitmap(bitmap_key::soul_hunter, "soul_hunter.png");
    add_bitmap(bitmap_key::suck_the_soul, "soul.png");
    add_bitmap(bitmap_key::mechanical_saw, "mechanical_saw.png");
}
}