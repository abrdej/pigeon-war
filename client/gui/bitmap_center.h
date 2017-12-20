#ifndef ENTITY_BITMAPS
#define ENTITY_BITMAPS

#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "common/bitmaps.h"
#include "config.h"

namespace view
{
class bitmap_center
{
public:
	using bitmap_type = sf::Texture;
	using path_type = std::string;

	static void load();

	static void add_bitmap(const bitmap_key & key, const path_type& path) {
		bitmap_type bitmap;
		if (!bitmap.loadFromFile(resources_directory + path))
			std::cerr << "Could not load bitmap file: " << path << "\n";
		bitmaps.emplace(key, bitmap);
	}
	static const bitmap_type& get_bitmap(const bitmap_key& key) {
		return bitmaps.at(key);
	}
private:
	static std::unordered_map<bitmap_key, bitmap_type, bitmaps_key_hash> bitmaps;
public:
	static bitmap_type grass_move_bitmap;
	static bitmap_type grass_attack_bitmap;
	static bitmap_type grass_damage_bitmap;
	static bitmap_type grass_selected_bitmap;
	static bitmap_type grass_friendly_bitmap;
	static bitmap_type grass_boost_bitmap;
};
};

#endif