#ifndef ENTITY_BITMAPS
#define ENTITY_BITMAPS

#include <unordered_map>
#include <typeindex>
#include <SFML/Graphics/Texture.hpp>

namespace view
{
	class bitmap_center
	{
	public:
		using bitmap_type = sf::Texture;
		using path_type = std::string;

		static void load();

		template <typename Entity>
		static void add_entity_image(const path_type& image_path)
		{
			bitmap_type bm;
			if (!bm.loadFromFile(image_path))
				throw std::exception();

			bitmaps_.emplace(std::type_index(typeid(std::decay_t<Entity>)), bm);
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
		static std::unordered_map<std::type_index, const bitmap_type> bitmaps_;
	public:
		static bitmap_type grass_move_bitmap;
		static bitmap_type grass_attack_bitmap;
		static bitmap_type grass_damage_bitmap;
		static bitmap_type grass_selected_bitmap;
	};
};

/*#include <unordered_map>
#include <typeindex>
#include <nana\paint\image.hpp>

namespace view
{
	class bitmap_center
	{
	public:
		static void load();

		template <typename Entity>
		static void add_entity_image(const std::wstring& image_path)
		{
			bitmaps_.insert(std::make_pair(std::type_index(typeid(Entity)),
				nana::paint::image(image_path)));
		}
		static nana::paint::image get_image_for_entity(const std::type_index& object_type)
		{
			return bitmaps_.at(object_type);
		}
		template <typename Entity>
		static nana::paint::image get_image_for_entity(const Entity& entity)
		{
			return bitmaps_.at(std::type_index(typeid(entity)));
		}
		template <typename Entity>
		static nana::paint::image get_image_for_entity()
		{
			return bitmaps_.at(std::type_index(typeid(Entity)));
		}
	private:
		static std::unordered_map<std::type_index, const nana::paint::image> bitmaps_;
	};
};
*/
#endif