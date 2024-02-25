#ifndef ROCKET_H
#define ROCKET_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../types.h"
#include "../../FX/Particle.h"
#include "Bullet.h"

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
	std::vector<Particle> m_particles;
	std::vector<Bullet> m_debris;

	// Smoke
	sf::Color m_smokeParticleColor;
	sf::Texture m_smokeParticleTexture;
	sf::Vector2f m_smokeParticleInitialScale;
	sf::Vector2f m_smokeParticleMaxScale;
	u8 m_particleSpawnRateInMs;
	u8 m_smokeParticleInitialAlpha;
	u8 m_smokeAngleError;
	i16 m_smokeParticleRotationSpeed;
	u16 m_smokeParticleSpeed;
	float m_smokeParticleAcceleration;
	float m_smokeParticleUpwardForce;
	float m_smokeParticleLifeTime;

	// Fire
	sf::Color m_fireParticleColor;
	sf::Texture m_fireParticleTexture;
	sf::Vector2f m_fireParticleInitialScale;
	sf::Vector2f m_fireParticleMaxScale;
	u8 m_fireParticleInitialAlpha;
	u8 m_fireAngleError;
	u8 m_particleLifeTimeError;
	i16 m_fireParticleRotationSpeed;
	u16 m_fireParticleSpeed;
	float m_fireParticleAcceleration;
	float m_fireParticleUpwardForce;
	float m_fireParticleLifeTime;

	// Explosion
	sf::Color m_explosionParticleColor;
	sf::Texture m_explosionParticleTexture;
	sf::Vector2f m_explosionParticleInitialScale;
	sf::Vector2f m_explosionParticleMaxScale;
	u8 m_explosionParticleInitialAlpha;
	u8 m_explosionParticlesAmount;
	i16 m_explosionParticleRotationSpeed;
	u16 m_explosionParticleSpeed;
	u16 m_explosionParticleSpeedError;
	float m_explosionParticleAcceleration;
	float m_explosionParticleUpwardForce;
	float m_explosionParticleLifeTime;

	// Debris
	sf::Texture m_debrisTexture;
	u8 m_debrisAmount;
	u16 m_debrisSpeed;
	u16 m_debrisSpeedError;
	u16 m_debrisRangeError;
	float m_debrisRange;

	// Flash
	sf::Texture m_explosionTexture;
	sf::Sprite m_explosionSprite;
	sf::IntRect m_explosionFrame;
	u8 m_explosionFrameCount;
	float m_explosionAnimationTimeInS;

private:
	bool m_isAlive;
	bool m_isExplosionFlashShown;
	bool m_isExplosionFlashAnimating;

private:
	sf::Clock m_clock;
	sf::Clock m_flashAnimationClock;
	sf::Time m_elapsedTime;
	sf::Time m_flashAnimationElapsedTime;

private:
	void killIfOutRange();
	void spawnPathParticles();
	void showExplosionFlash();

private:
	void move(float deltaTime);
	
	void animateExplosion();
		
	void updateParticles(float deltaTime);
	void updateDebris(float deltaTime);
	
	void renderExplosionFlash(sf::RenderWindow* target);

private:
	void initBody();
	void initParticles();
	void initExplosionFlash();

public:
	Rocket(sf::Texture* _texture, sf::Vector2f _initialPostition, u16 _speed, u8 _damage, float _angle, float _range);
	~Rocket();

public:
	void update(float deltaTime);
	void render(sf::RenderWindow* target);

public:
	__forceinline const u8 getDamage() const { return this->m_damage; }

	__forceinline const void kill() { this->m_isAlive = false; }
	__forceinline const bool isAlive() const { return this->m_isAlive; }
	__forceinline const bool isParticleAlive() const { return std::fmaxl(this->m_particles.size(), this->m_debris.size()) > 0 ? true : false;
}
	const void explode();
};

#endif

