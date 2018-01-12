#ifndef UTILITIES
#define UTILITIES

#include <SFML/Graphics.hpp>

namespace util {
namespace {

const double pi = 3.14159265359;

inline double distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return sqrt(powl(p1.x - p2.x, 2.) + powl(p1.y - p2.y, 2.));
}

inline double angle_rad(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return atan2(p1.y - p2.y, p1.x - p2.x);
}

inline sf::Vector2f angle_distance_offset(const sf::Vector2f& p, double radians, double distance)
{
	sf::Int32 x = static_cast<sf::Int32>(std::round(sin(radians) * distance));
	sf::Int32 y = static_cast<sf::Int32>(std::round(cos(radians) * distance));
	return p + sf::Vector2f(x, y);
}

inline double deg_to_rad(double degrees)
{
	return degrees * (pi / 180.);
}

inline double rad_to_deg(double radians)
{
	return radians * (180. / pi);
}

}
}

#endif