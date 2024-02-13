#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
private:
	sf::Vector2f m_size;
	sf::Color m_color;

protected:
	sf::Vector2f m_position;
	
public:
	Entity(sf::Vector2f _size, sf::Color _color, sf::Vector2f _position);
	virtual ~Entity() = 0;

	// Setters	
	__forceinline virtual void setColor(sf::Color color) = 0;
	__forceinline virtual void setSize(sf::Vector2f size) = 0;
	__forceinline virtual void setPosition(sf::Vector2f position) = 0;
	
	// Getters	
	__forceinline const virtual sf::Color getColor() const = 0;
	__forceinline const virtual sf::Vector2f getSize() const = 0;
	__forceinline const virtual sf::Vector2f getPosition() const = 0;
	__forceinline const virtual sf::Vector2f getVelocity() const = 0;

	// Other
	const virtual void kill() = 0;

};

#endif
