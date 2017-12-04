#ifndef ENTITY_BITMAPS
#define ENTITY_BITMAPS

#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>

enum class BitmapKey {
	shooter,
	shooter_shoot
};

namespace view
{
class bitmap_center
{
public:
	using bitmap_type = sf::Texture;
	using path_type = std::string;

	static void load();

	static void add_bitmap(const BitmapKey& key, const path_type& path) {
		bitmap_type bitmap;
		if (!bitmap.loadFromFile(path))
			std::cerr << "Could not load bitmap file: " << path << "\n";
		bb.emplace(key, bitmap);
	}
	static const bitmap_type& get_bitmap(const BitmapKey& key) {
		return bb.at(key);
	}

	template <typename Entity>
	static void add_entity_image(const path_type& image_path)
	{
		bitmap_type bm;
		if (!bm.loadFromFile(image_path))
			std::cout << "Error loaded: " << image_path << "\n";
		//throw std::exception();

		bitmaps_.emplace(std::type_index(typeid(std::decay_t<Entity>)), bm);
	}
	template <typename Entity>
	static void change_entity_image(const path_type& image_path)
	{
		bitmap_type bm;
		if (!bm.loadFromFile(image_path))
			throw std::exception();

		bitmaps_[std::type_index(typeid(std::decay_t<Entity>))] = bm;
	}
	static const bitmap_type& get_image_for_entity(const std::type_index& object_type)
	{
		return bitmaps_.at(object_type);
	}
	template <typename Entity>
	static const bitmap_type& get_image_for_entity(const Entity& entity)
	{
		return bitmaps_.at(std::type_index(typeid(entity)));
	}
	template <typename Entity>
	static const bitmap_type& get_image_for_entity()
	{
		return bitmaps_.at(std::type_index(typeid(std::decay_t<Entity>)));
	}
private:
	static std::unordered_map<std::type_index, bitmap_type> bitmaps_;
	static std::unordered_map<BitmapKey, bitmap_type> bb;
public:
	static bitmap_type grass_move_bitmap;
	static bitmap_type grass_attack_bitmap;
	static bitmap_type grass_damage_bitmap;
	static bitmap_type grass_selected_bitmap;
};
};

#endif