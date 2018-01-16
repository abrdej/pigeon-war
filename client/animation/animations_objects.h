#ifndef ANIMATIONS_OBJECTS_H
#define ANIMATIONS_OBJECTS_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <typeindex>
#include "animation.h"

namespace animation
{
enum class turn_types { right, left };

class move_object_animation final
{
public:
    move_object_animation(move move_data);
    void draw(sf::RenderWindow& window);
    bool run();

private:
    std::uint64_t index_from_;
    std::uint64_t index_to_;
    sf::Vector2f start_pos_;
    sf::Vector2f actual_pos_;
    sf::Vector2f end_pos_;
    sf::Vector2f translation_;
    double velocity_;
    const sf::Texture& bitmap_;
    sf::Sprite sprite;
    turn_types turn_;
};

class move_object_animation2 final
{
public:
    move_object_animation2(move_entity move_data);
    void draw(sf::RenderWindow& window);
    bool run();

private:
    std::uint64_t index_from_;
    std::uint64_t index_to_;
    sf::Vector2f start_pos_;
    sf::Vector2f actual_pos_;
    sf::Vector2f end_pos_;
    sf::Vector2f translation_;
    double velocity_;
    std::uint64_t entity_id_;
    sf::Sprite& sprite;
    turn_types turn_;
};

class flash_bitmap_animation
{
public:
    flash_bitmap_animation(flash_bitmap flash_bitmap_data);
    void draw(sf::RenderWindow& window);
    bool run();
private:
    sf::Texture bitmap_;
    sf::Vector2f on_point_;
    std::chrono::system_clock::time_point start_time_;
    std::chrono::milliseconds duration_;
};

class change_health_animation
{
public:
    explicit change_health_animation(change_health change_health_data);
    void draw(sf::RenderWindow& window);
    bool run();
private:
    sf::Font font_;
    sf::Vector2f point_;
    std::int32_t change_by_;
    std::chrono::system_clock::time_point start_time_;
    std::chrono::milliseconds duration_;
};
}

#endif