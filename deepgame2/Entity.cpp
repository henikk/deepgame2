#include "Entity.h"

Entity::Entity(sf::Vector2f _size, sf::Color _color, sf::Vector2f _position)
	: m_size(_size), m_color(_color), m_position(_position)
{}

Entity::~Entity()
{}