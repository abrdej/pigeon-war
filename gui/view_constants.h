#ifndef constants_H
#define constants_H

#include <SFML/Graphics.hpp>

namespace view
{
namespace constants
{
static const sf::Vector2i top_left_point(0, 0);
static const size_t field_size = 60;

static const sf::Color selected_field_color(80, 100, 200);
static const sf::Color selected_field_color_borders(60, 80, 100);

static const sf::Color possible_movement_color(80, 200, 120);
static const sf::Color possible_target_color(255, 90, 90);

static const sf::Color movement_range_color(80, 220, 200);
static const sf::Color target_range_color(255, 160, 160);
};
};

#endif