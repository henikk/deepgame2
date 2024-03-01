#include "Rocket.h"

Rocket::Rocket(sf::Texture* _texture, sf::Vector2f _initialPostition, u16 _speed, u8 _damage, float _angle, float _range)
	: m_texture(*_texture), m_initialPosition(_initialPostition), m_speed(_speed), m_damage(_damage), m_angle(_angle), m_range(_range), m_isAlive(true), m_isExplosionFlashShown(false)
{	
	this->m_elapsedTime = this->m_clock.getElapsedTime();

	_texture->setSmooth(true);
	this->m_body.setTexture(*_texture);

	this->initBody();
	this->initParticles();
	this->initExplosionFlash();
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
		this->m_smokeParticleLifeTime + rand() % this->m_particleLifeTimeError
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

void Rocket::showExplosionFlash()
{
	if (!this->m_isExplosionFlashShown)
	{
		//this->m_flashAnimationlock.restart();
		this->m_explosionSprite.setTexture(this->m_explosionTexture);
		this->m_explosionSprite.setPosition(this->m_body.getPosition());
		this->m_isExplosionFlashShown = true;
	}
}

void Rocket::updateParticles(float deltaTime)
{
	this->m_particles.erase(std::remove_if(this->m_particles.begin(), this->m_particles.end(), [](const auto& particles) {
		return !particles.isAlive();
		}), this->m_particles.end());

	for (auto& particle : this->m_particles)
		particle.update(deltaTime);
}

void Rocket::updateDebris(float deltaTime)
{
	this->m_debris.erase(std::remove_if(this->m_debris.begin(), this->m_debris.end(), [](const auto& debris) {
		return !debris.isAlive();
		}), this->m_debris.end());

	for (auto& debris : this->m_debris)
		debris.update(deltaTime);
}

void Rocket::move(float deltaTime)
{
	float radians = this->m_angle * (3.14f / 180.0f);

	this->m_velocity = sf::Vector2f(this->m_speed * std::cos(radians), this->m_speed * std::sin(radians));
	this->m_body.move(this->m_velocity * deltaTime);
}

void Rocket::animateExplosion()
{
	this->m_flashAnimationElapsedTime = this->m_flashAnimationClock.getElapsedTime();

	if (this->m_isExplosionFlashAnimating && this->m_isExplosionFlashShown)
	{
		if (this->m_explosionFrame.left == this->m_explosionFrame.width * (this->m_explosionFrameCount - 1))
			this->m_isExplosionFlashAnimating = false;
		else if (this->m_flashAnimationElapsedTime.asSeconds() >= this->m_explosionAnimationTimeInS / (this->m_explosionFrameCount - 1))
		{
			this->m_flashAnimationClock.restart();
			this->m_explosionFrame.left += this->m_explosionFrame.width;
		}

		if (this->m_explosionFrame.left == this->m_explosionFrame.width * (this->m_explosionFrameCount - 2)) // change this
		{
			this->m_explosionFrame.left = 0;
			this->m_explosionFrame.top += this->m_explosionFrame.height;
		}

		this->m_explosionSprite.setTextureRect(this->m_explosionFrame);
	}
}

void Rocket::renderExplosionFlash(sf::RenderWindow* target)
{
	if (this->m_isExplosionFlashShown)
	{
		target->draw(this->m_explosionSprite);

		if (!this->m_isExplosionFlashAnimating)
			this->m_isExplosionFlashShown = false;
	}
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
	this->m_smokeParticleColor = sf::Color(175, 175, 175);
	this->m_smokeParticleTexture.loadFromFile("textures/particles/smoke.png");
	this->m_smokeParticleInitialScale = { 0.20f, 0.16f };
	this->m_smokeParticleMaxScale = { 0.4f, 0.4f };
	this->m_particleSpawnRateInMs = 150u;
	this->m_smokeAngleError = 70u;
	this->m_particleLifeTimeError = 2u;
	this->m_smokeParticleRotationSpeed = 50;
	this->m_smokeParticleInitialAlpha = 128u;
	this->m_smokeParticleSpeed = 5u;
	this->m_smokeParticleAcceleration = 0.0f;
	this->m_smokeParticleUpwardForce = 5.0f;
	this->m_smokeParticleLifeTime = 1.5f;

	// Fire
	this->m_fireParticleColor = sf::Color::White;
	this->m_fireParticleTexture.loadFromFile("textures/particles/flameLowRes1.png");
	this->m_fireParticleInitialScale = { 0.4f, 0.4f };
	this->m_fireParticleMaxScale = { 0.5f, 0.5f };
	this->m_fireAngleError = 100u;
	this->m_fireParticleRotationSpeed = 50;
	this->m_fireParticleInitialAlpha = 255u;
	this->m_fireParticleSpeed = 5u;
	this->m_fireParticleAcceleration = 0.0f;
	this->m_fireParticleUpwardForce = 5.0f;
	this->m_fireParticleLifeTime = 0.1f;

	// Debris
	this->m_debrisTexture.loadFromFile("textures/particles/assault_shell.png");
	this->m_debrisAmount = 128u;
	this->m_debrisSpeed = 2000u;
	this->m_debrisSpeedError = this->m_debrisSpeed / 3;
	this->m_debrisRange = 350.0f;
	this->m_debrisRangeError = this->m_debrisRange / 2;

	// Explosion
	this->m_explosionParticleColor = sf::Color(175, 175, 175);
	this->m_explosionParticleTexture = this->m_smokeParticleTexture;
	this->m_explosionParticleInitialScale = { 0.5f, 0.5f };
	this->m_explosionParticleMaxScale = { 0.9f, 0.9f };
	this->m_explosionParticlesAmount = 20u;
	this->m_explosionParticleRotationSpeed = 50;
	this->m_explosionParticleInitialAlpha = 100u;
	this->m_explosionParticleSpeed = 0u;
	this->m_explosionParticleSpeedError = 700u;
	this->m_explosionParticleAcceleration = 3.0f;
	this->m_explosionParticleUpwardForce = 55.0f;
	this->m_explosionParticleLifeTime = this->m_smokeParticleLifeTime;
}

void Rocket::initExplosionFlash()
{
	this->m_isExplosionFlashAnimating = false;
	this->m_explosionFrame = sf::IntRect(0, 0, 192, 192);
	this->m_explosionFrameCount = 5u;
	this->m_explosionTexture.loadFromFile("textures/particles/explosion_sprite_sheet2.png");
	this->m_explosionTexture.setSmooth(true);
	this->m_explosionSprite.setTexture(this->m_explosionTexture);
	this->m_explosionSprite.setTextureRect(this->m_explosionFrame);
	this->m_explosionSprite.setRotation(rand() % 360);
	this->m_explosionSprite.setScale(2.0f, 2.0f);
	this->m_explosionSprite.setOrigin(sf::Vector2f(this->m_explosionFrame.width / 2.0f, this->m_explosionFrame.height / 2.0f));
	this->m_explosionAnimationTimeInS = 0.1f;
}

void Rocket::update(float deltaTime)
{
	if (this->m_isAlive)
	{
		this->m_elapsedTime = this->m_clock.getElapsedTime();

		if (this->m_elapsedTime.asMilliseconds() >= (100.0f / this->m_speed) * this->m_particleSpawnRateInMs)
		{
			this->m_clock.restart();

			this->spawnPathParticles();
		}

		this->move(deltaTime);
		this->killIfOutRange();
	}

	this->animateExplosion();
	this->updateDebris(deltaTime);
	this->updateParticles(deltaTime);
}

void Rocket::render(sf::RenderWindow* target)
{
	this->renderExplosionFlash(target);

	for (auto& debris : this->m_debris)
		debris.render(target);

	for (auto& particle : this->m_particles)
		particle.render(target);

	if (this->m_isAlive)
		target->draw(this->m_body);
}

const void Rocket::explode()
{
	float currentAngle = 0.0f;

	this->m_isExplosionFlashAnimating = true;

	// Smoke particles
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
			this->m_explosionParticleLifeTime + rand() % this->m_particleLifeTimeError
		));

		currentAngle += 360.0f / this->m_explosionParticlesAmount;
	}

	// Debris
	for (int i = 0; i < this->m_debrisAmount; i++)
	{
		this->m_debris.emplace_back(Bullet(&this->m_debrisTexture, this->m_body.getPosition(), this->m_debrisSpeed + rand() % this->m_debrisSpeedError,
			this->m_damage, static_cast<float>(rand() % 360), this->m_debrisRange + rand() % this->m_debrisRangeError));
	}

	this->showExplosionFlash();
}
