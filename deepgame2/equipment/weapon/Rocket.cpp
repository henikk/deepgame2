#include "Rocket.h"

Rocket::Rocket(sf::Texture* _texture, sf::Texture* _smokeTexture, sf::Vector2f _initialPostition, u16 _speed, u8 _damage, float _angle, float _range)
	: m_texture(*_texture), m_particleSmokeTexture(*_smokeTexture), m_initialPosition(_initialPostition), m_speed(_speed), m_damage(_damage), m_angle(_angle), m_range(_range), m_isAlive(true)
{
	this->m_particleColor = sf::Color::White;
	this->m_particleInitialScale = { 0.16f, 0.16f };
	this->m_particleMaxScale = { 0.4f, 0.4f };
	this->m_particleSpawnRateInMs = 150u;
	this->m_smokeAngleError = 100u;
	this->m_particleRotationSpeed = 50;
	this->m_particleInitialAlpha = 150u;
	this->m_particleSpeed = 5u;
	this->m_particleAcceleration = 0.0f;
	this->m_particleUpwardForce = 5.0f;
	this->m_particleLifeTime = 5.0f;

	this->m_particle2Color = sf::Color::White;
	this->m_particleFireTexture.loadFromFile("textures/particles/fireball2.png"); // TEMP
	this->m_particle2InitialScale = { 0.05f, 0.05f };
	this->m_particle2MaxScale = { 0.06f, 0.06f };
	this->m_particle2SpawnRateInMs = 150u;
	this->m_fireAngleError = 100u;
	this->m_particle2RotationSpeed = 50;
	this->m_particle2InitialAlpha = 200u;
	this->m_particle2Speed = 5u;
	this->m_particle2Acceleration = 0.0f;
	this->m_particle2UpwardForce = 5.0f;
	this->m_particle2LifeTime = 0.1f;

	this->m_body.setTexture(*_texture);
	//this->m_body.setScale(sf::Vector2f(0.1f, 0.1f)); // TEMP
	this->m_body.setOrigin(sf::Vector2f(0.0f, this->m_texture.getSize().y / 2));
	this->m_body.setPosition(this->m_initialPosition);
	this->m_body.setRotation(this->m_angle);

	this->m_elapsedTime = this->m_clock.getElapsedTime();
}

Rocket::~Rocket(){}

void Rocket::killIfOutRange()
{
	if (this->m_body.getPosition().x >= this->m_initialPosition.x + this->m_range ||
		this->m_body.getPosition().y <= this->m_initialPosition.y - this->m_range ||
		this->m_body.getPosition().x <= this->m_initialPosition.x - this->m_range ||
		this->m_body.getPosition().y >= this->m_initialPosition.y + this->m_range)
	{
		this->kill();
	}
}

void Rocket::spawnSmoke()
{
	this->m_smokePath.emplace_back(Particle
	(
		this->m_particleColor,
		&this->m_particleSmokeTexture,
		this->m_body.getPosition(),
		this->m_particleInitialScale,
		this->m_particleMaxScale,
		this->m_particleInitialAlpha,
		this->m_particleRotationSpeed,
		this->m_particleSpeed,
		this->m_particleAcceleration,
		180.0f - this->m_angle + rand() % (this->m_smokeAngleError + 1) - static_cast<float>(this->m_smokeAngleError / 2),
		this->m_particleUpwardForce,
		this->m_particleLifeTime
	));
}

void Rocket::spawnFire()
{
	this->m_firePath.emplace_back(Particle
	(
		this->m_particle2Color,
		&this->m_particleFireTexture,
		this->m_body.getPosition(),
		this->m_particle2InitialScale,
		this->m_particle2MaxScale,
		this->m_particle2InitialAlpha,
		this->m_particle2RotationSpeed,
		this->m_particle2Speed,
		this->m_particle2Acceleration,
		180.0f - this->m_angle + rand() % (this->m_fireAngleError + 1) - static_cast<float>(this->m_fireAngleError / 2),
		this->m_particle2UpwardForce,
		this->m_particle2LifeTime
	));
}

void Rocket::updateSmoke(float deltaTime)
{
	for (auto it = this->m_smokePath.begin(); it != this->m_smokePath.end();)
	{
		if (!it->isAlive())
		{
			it = this->m_smokePath.erase(it);
		}
		else
		{
			it->update(deltaTime);
			++it;
		}
	}
}

void Rocket::updateFire(float deltaTime)
{
	for (auto it = this->m_firePath.begin(); it != this->m_firePath.end();)
	{
		if (!it->isAlive())
		{
			it = this->m_firePath.erase(it);
		}
		else
		{
			it->update(deltaTime);
			++it;
		}
	}
}

void Rocket::update(float deltaTime)
{
	if (this->m_isAlive)
	{
		this->m_elapsedTime = this->m_clock.getElapsedTime();
		float radians = this->m_angle * (3.14f / 180.0f);

		this->m_velocity = sf::Vector2f(this->m_speed * std::cos(radians), this->m_speed * std::sin(radians));
		this->m_body.move(this->m_velocity * deltaTime);

		if (this->m_elapsedTime.asMilliseconds() >= (100.0f / this->m_speed) * this->m_particleSpawnRateInMs)
		{
			this->m_clock.restart();
			spawnSmoke();
			spawnFire();
		}

		killIfOutRange();
	}
	updateSmoke(deltaTime);
	updateFire(deltaTime);
}

void Rocket::render(sf::RenderWindow* target) const
{
	if (this->m_isAlive)
		target->draw(this->m_body);

	for (auto& particle : this->m_smokePath)
		particle.render(target);
	for (auto& particle : this->m_firePath)
		particle.render(target);
}
