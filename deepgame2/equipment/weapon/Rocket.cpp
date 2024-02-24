#include "Rocket.h"

Rocket::Rocket(sf::Texture* _texture, sf::Vector2f _initialPostition, u16 _speed, u8 _damage, float _angle, float _range)
	: m_texture(*_texture), m_initialPosition(_initialPostition), m_speed(_speed), m_damage(_damage), m_angle(_angle), m_range(_range), m_isAlive(true)
{	
	this->m_elapsedTime = this->m_clock.getElapsedTime();

	this->m_body.setTexture(*_texture);
	this->initBody();
	this->initParticles();
}

Rocket::~Rocket(){}

void Rocket::killIfOutRange()
{
	if (this->m_body.getPosition().x >= this->m_initialPosition.x + this->m_range ||
		this->m_body.getPosition().y <= this->m_initialPosition.y - this->m_range ||
		this->m_body.getPosition().x <= this->m_initialPosition.x - this->m_range ||
		this->m_body.getPosition().y >= this->m_initialPosition.y + this->m_range)
	{
		this->explode();
		this->kill();
	}
}

void Rocket::spawnPathParticles()
{
	// Smoke
	this->m_particles.emplace_back(Particle
	(
		this->m_smokeParticleColor,
		&this->m_smokeParticleTexture,
		this->m_body.getPosition(),
		this->m_smokeParticleInitialScale,
		this->m_smokeParticleMaxScale,
		this->m_smokeParticleInitialAlpha,
		this->m_smokeParticleRotationSpeed,
		this->m_smokeParticleSpeed,
		this->m_smokeParticleAcceleration,
		180.0f - this->m_angle + rand() % (this->m_smokeAngleError + 1) - static_cast<float>(this->m_smokeAngleError / 2),
		this->m_smokeParticleUpwardForce,
		this->m_smokeParticleLifeTime
	));

	// Fire
	this->m_particles.emplace_back(Particle
	(
		this->m_fireParticleColor,
		&this->m_fireParticleTexture,
		this->m_body.getPosition(),
		this->m_fireParticleInitialScale,
		this->m_fireParticleMaxScale,
		this->m_fireParticleInitialAlpha,
		this->m_fireParticleRotationSpeed,
		this->m_fireParticleSpeed,
		this->m_fireParticleAcceleration,
		180.0f - this->m_angle + rand() % (this->m_fireAngleError + 1) - static_cast<float>(this->m_fireAngleError / 2),
		this->m_fireParticleUpwardForce,
		this->m_fireParticleLifeTime
	));
}

void Rocket::updateParticles(float deltaTime)
{
	for (auto it = this->m_particles.begin(); it != this->m_particles.end();)
	{
		if (!it->isAlive())
		{
			it = this->m_particles.erase(it);
		}
		else
		{
			it->update(deltaTime);
			++it;
		}
	}
}

void Rocket::move(float deltaTime)
{
	float radians = this->m_angle * (3.14f / 180.0f);

	this->m_velocity = sf::Vector2f(this->m_speed * std::cos(radians), this->m_speed * std::sin(radians));
	this->m_body.move(this->m_velocity * deltaTime);
}

void Rocket::initBody()
{
	this->m_body.setOrigin(sf::Vector2f(0.0f, this->m_texture.getSize().y / 2));
	this->m_body.setPosition(this->m_initialPosition);
	this->m_body.setRotation(this->m_angle);
}

void Rocket::initParticles()
{
	// Smoke
	this->m_smokeParticleColor = sf::Color::White;
	this->m_smokeParticleTexture.loadFromFile("textures/particles/smoke.png");
	this->m_smokeParticleInitialScale = { 0.16f, 0.16f };
	this->m_smokeParticleMaxScale = { 0.4f, 0.4f };
	this->m_smokeParticleSpawnRateInMs = 150u;
	this->m_smokeAngleError = 70u;
	this->m_smokeParticleRotationSpeed = 50;
	this->m_smokeParticleInitialAlpha = 150u;
	this->m_smokeParticleSpeed = 5u;
	this->m_smokeParticleAcceleration = 0.0f;
	this->m_smokeParticleUpwardForce = 5.0f;
	this->m_smokeParticleLifeTime = 5.0f;

	// Fire
	this->m_fireParticleColor = sf::Color::White;
	this->m_fireParticleTexture.loadFromFile("textures/particles/fireball2.png");
	this->m_fireParticleInitialScale = { 0.05f, 0.05f };
	this->m_fireParticleMaxScale = { 0.06f, 0.06f };
	this->m_fireParticleSpawnRateInMs = 150u;
	this->m_fireAngleError = 100u;
	this->m_fireParticleRotationSpeed = 50;
	this->m_fireParticleInitialAlpha = 200u;
	this->m_fireParticleSpeed = 5u;
	this->m_fireParticleAcceleration = 0.0f;
	this->m_fireParticleUpwardForce = 5.0f;
	this->m_fireParticleLifeTime = 0.1f;

	// Explosion
	this->m_explosionParticleColor = sf::Color::White;
	this->m_explosionParticleTexture = this->m_smokeParticleTexture;
	this->m_explosionParticleInitialScale = { 0.5f, 0.5f };
	this->m_explosionParticleMaxScale = { 0.9f, 0.9f };
	this->m_explosionParticlesAmount = 20u;
	this->m_explosionParticleRotationSpeed = 50;
	this->m_explosionParticleInitialAlpha = 100u;
	this->m_explosionParticleSpeed = 0u;
	this->m_explosionParticleSpeedError = 700u;
	this->m_explosionParticleAcceleration = 3.0f;
	this->m_explosionParticleUpwardForce = 30.0f;
	this->m_explosionParticleLifeTime = this->m_smokeParticleLifeTime;
}

void Rocket::update(float deltaTime)
{
	if (this->m_isAlive)
	{
		this->m_elapsedTime = this->m_clock.getElapsedTime();

		if (this->m_elapsedTime.asMilliseconds() >= (100.0f / this->m_speed) * this->m_smokeParticleSpawnRateInMs)
		{
			this->m_clock.restart();

			this->spawnPathParticles();
		}

		this->move(deltaTime);
		this->killIfOutRange();
	}
	this->updateParticles(deltaTime);
}

void Rocket::render(sf::RenderWindow* target) const
{
	if (this->m_isAlive)
		target->draw(this->m_body);

	for (auto& particle : this->m_particles)
		particle.render(target);
}

const void Rocket::explode()
{
	float angleIncrement = 360.0f / this->m_explosionParticlesAmount;
	float currentAngle = 0.0f;

	for (int i = 0; i < this->m_explosionParticlesAmount; i++)
	{
		this->m_particles.emplace_back(Particle
		(
			this->m_explosionParticleColor,
			&this->m_explosionParticleTexture,
			this->m_body.getPosition(),
			this->m_explosionParticleInitialScale,
			this->m_explosionParticleMaxScale,
			this->m_explosionParticleInitialAlpha,
			this->m_explosionParticleRotationSpeed,
			this->m_explosionParticleSpeed + rand() % this->m_explosionParticleSpeedError,
			this->m_explosionParticleAcceleration,
			currentAngle,
			this->m_explosionParticleUpwardForce,
			this->m_explosionParticleLifeTime
		));

		currentAngle += angleIncrement;
	}
}
