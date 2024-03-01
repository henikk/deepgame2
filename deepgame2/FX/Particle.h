#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "../../types.h"
#include "../external/transition/SigmoidTrasition.hpp"

class Particle
{
private:
	sf::Clock m_clock;
	sf::Time m_elapsedTime;
	sf::Time m_startTime;

private:
	sf::Color m_color;
	sf::Texture m_texture;
	sf::Sprite m_body;

private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_initialPosition;
	sf::Vector2f m_initialScale;
	sf::Vector2f m_maxScale;
	u8 m_initialAlpha;
	i16 m_rotationSpeed;
	u16 m_initialSpeed;
	u16 m_speed;
	float m_acceleration;
	float m_initialAngle;
	float m_upwardForce;
	float m_lifeTime;

private:
	bool m_isAlive;

private:
	void killIfOutOfTime();
	void move(float deltaTime);
	void decreaseAlpha();
	void increaseScale();
	void increaseUpwardForce();

public:
	Particle(
		sf::Color _color,
		sf::Texture* _texture,
		sf::Vector2f _initialPosition,
		sf::Vector2f _initialScale,
		sf::Vector2f _maxScale,
		u8 _initialAlpha,
		i16 _rotationSpeed,
		u16 _initialSpeed,
		float _acceleration,
		float _initialAngle,
		float _upwardForce,
		float _lifeTime);
	~Particle();

public:
	void update(float deltaTime);
	void render(sf::RenderWindow* target) const;

public:
	__forceinline void setPosition(sf::Vector2f position) { this->m_body.setPosition(position); }
	__forceinline sf::Vector2f getPosition() const { return this->m_body.getPosition(); }

public:
	__forceinline const void kill() { this->m_isAlive = false; }
	__forceinline const bool isAlive() const { return this->m_isAlive; }

};

#endif
