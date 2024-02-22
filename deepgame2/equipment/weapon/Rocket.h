#ifndef ROCKET_H
#define ROCKET_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../types.h"
#include "../../FX/Particle.h"

class Rocket
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
	std::vector<Particle> m_smokePath;
	sf::Color m_particleColor;
	sf::Texture m_particleSmokeTexture;
	sf::Vector2f m_particleInitialScale;
	sf::Vector2f m_particleMaxScale;
	u8 m_particleSpawnRateInMs;
	u8 m_particleInitialAlpha;
	u8 m_smokeAngleError;
	i16 m_particleRotationSpeed;
	u16 m_particleSpeed;
	float m_particleAcceleration;
	float m_particleUpwardForce;
	float m_particleLifeTime;

	std::vector<Particle> m_firePath;
	sf::Color m_particle2Color;
	sf::Texture m_particleFireTexture;
	sf::Vector2f m_particle2InitialScale;
	sf::Vector2f m_particle2MaxScale;
	u8 m_particle2SpawnRateInMs;
	u8 m_particle2InitialAlpha;
	u8 m_fireAngleError;
	i16 m_particle2RotationSpeed;
	u16 m_particle2Speed;
	float m_particle2Acceleration;
	float m_particle2UpwardForce;
	float m_particle2LifeTime;

private:
	bool m_isAlive;

private:
	sf::Clock m_clock;
	sf::Time m_elapsedTime;

private:
	void killIfOutRange();
	void spawnSmoke();
	void spawnFire();
	void updateSmoke(float deltaTime);
	void updateFire(float deltaTime);

public:
	Rocket(sf::Texture* _texture, sf::Texture* _smokeTexture, sf::Vector2f _initialPostition, u16 _speed, u8 _damage, float _angle, float _range);
	~Rocket();

public:
	void update(float deltaTime);
	void render(sf::RenderWindow* target) const;

public:
	__forceinline const u8 getDamage() const { return this->m_damage; }

	__forceinline const void kill() { this->m_isAlive = false; }
	__forceinline const bool isAlive() const { return this->m_isAlive; }
	__forceinline const bool isParticleAlive() const { return m_smokePath.size() > 0 ? true : false; }
};

#endif

