#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

#include "../../types.h"

class Bullet
{
private:
	sf::Texture m_texture;
	sf::Sprite m_body;

private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_initialPosition;
	u8 m_damage;
	u16 m_speed;
	float m_angle;
	float m_range;

private:
	bool m_isAlive;

private:
	void killIfOutRange();

	void decreaseOpacity();

public:
	Bullet(sf::Texture *_texture, sf::Vector2f _initialPostition, u16 _speed, u8 _damage, float _angle, float _range);
	~Bullet();

public:
	void update(float deltaTime);
	void render(sf::RenderWindow* target) const;

public:
	__forceinline const u8 getDamage() const { return this->m_damage; }

	__forceinline const void kill() { this->m_isAlive = false; }
	__forceinline const bool isAlive() const { return this->m_isAlive; }

};

#endif