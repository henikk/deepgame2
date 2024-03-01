#include "Grenade.h"

void Grenade::initBody()
{
	this->m_rotationSpeed = 55.0f;
}

void Grenade::initParticles()
{
	// Smoke
	this->m_smokeParticleColor = sf::Color(175, 175, 175);
	this->m_smokeParticleTexture.loadFromFile("textures/particles/smoke.png");
	this->m_smokeParticleInitialScale = { 0.20f, 0.16f };
	this->m_smokeParticleMaxScale = { 0.4f, 0.4f };
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

void Grenade::initExplosionFlash()
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

Grenade::Grenade(sf::Texture* _texture, sf::Vector2f _initialPosition, u8 _damage, u16 _initialSpeed, float _initialAngle, float _lifeTime)
	: m_texture(*_texture), m_initialPosition(_initialPosition), m_damage(_damage), m_initialSpeed(_initialSpeed),  m_initialAngle(_initialAngle), m_lifeTime(_lifeTime), m_isAlive(true)
{
	this->m_elapsedTime = this->m_clock.getElapsedTime();

	_texture->setSmooth(true);
	this->m_body.setTexture(*_texture);

	this->initBody();
	this->initParticles();
	this->initExplosionFlash();
}

void Grenade::killIfOutOfTime()
{
	if (this->m_elapsedTime.asSeconds() >= this->m_lifeTime)
	{
		this->explode();
		this->kill();
	}
}

void Grenade::showExplosionFlash()
{
	if (!this->m_isExplosionFlashShown)
	{
		//this->m_flashAnimationlock.restart();
		this->m_explosionSprite.setTexture(this->m_explosionTexture);
		this->m_explosionSprite.setPosition(this->m_body.getPosition());
		this->m_isExplosionFlashShown = true;
	}
}

void Grenade::move(float deltaTime)
{
	this->m_body.setPosition(this->m_initialPosition); // [TEMP]
}

void Grenade::animateExplosion()
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

void Grenade::updateParticles(float deltaTime)
{
	this->m_particles.erase(std::remove_if(this->m_particles.begin(), this->m_particles.end(), [](const auto& particles) {
		return !particles.isAlive();
		}), this->m_particles.end());

	for (auto& particle : this->m_particles)
		particle.update(deltaTime);
}

void Grenade::updateDebris(float deltaTime)
{
	this->m_debris.erase(std::remove_if(this->m_debris.begin(), this->m_debris.end(), [](const auto& debris) {
		return !debris.isAlive();
		}), this->m_debris.end());

	for (auto& debris : this->m_debris)
		debris.update(deltaTime);
}

void Grenade::renderExplosionFlash(sf::RenderWindow* target)
{
	if (this->m_isExplosionFlashShown)
	{
		target->draw(this->m_explosionSprite);

		if (!this->m_isExplosionFlashAnimating)
			this->m_isExplosionFlashShown = false;
	}
}

void Grenade::update(float deltaTime)
{
	if (this->m_isAlive)
	{
		this->m_elapsedTime = this->m_clock.getElapsedTime();

		this->move(deltaTime);
		this->killIfOutOfTime();
	}

	this->animateExplosion();
	this->updateDebris(deltaTime);
	this->updateParticles(deltaTime);
}

void Grenade::render(sf::RenderWindow* target)
{
	this->renderExplosionFlash(target);

	for (auto& debris : this->m_debris)
		debris.render(target);

	for (auto& particle : this->m_particles)
		particle.render(target);

	if (this->m_isAlive)
		target->draw(this->m_body);
}

const void Grenade::explode()
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
