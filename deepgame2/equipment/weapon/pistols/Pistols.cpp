#include "Pistols.h"

Pistols::Pistols(std::string _pathToTexture, std::string _pathToBulletTexture, std::string _pathToParticleTexture, std::vector<std::string> _pathsToSounds)
	: Weapon(_pathToTexture, _pathToBulletTexture, _pathToParticleTexture, _pathsToSounds)
{
	this->m_damage = 12;
	this->m_accuracy = 90;
	this->m_bulletsPerShot = 1;
	this->m_bulletSpeed = 4500;
	this->m_fireRange = 2000;
	this->m_capacity = 9;
	this->m_ammo = 30;	
	this->m_magazine = this->m_capacity;
	this->m_reloadTime = 3.5f;
	this->m_fireRate = 5.5f;

	this->m_singleShot = true;
	this->m_showFlash = true;
	this->m_showSmoke = true;

	this->m_shotFrameCount = 8;
	this->m_emptyFrameCount = 4;
	this->m_reloadFrameCount = 35;
	this->m_frame = sf::IntRect(0, 0, 80, 48);

	this->m_gunOffset = { 0.0f, 35.0f };
	this->m_barrelOffset = { 47.0f, 11.0f };

	this->m_particleColor = sf::Color::White;
	this->m_particleSmokeTexture.loadFromFile(this->m_pathToParticleTexture);
	this->m_particleInitialScale = { 0.03f, 0.03f };
	this->m_particleMaxScale = { 0.085f, 0.085f };
	this->m_particleRotationSpeed = 55;
	this->m_particleInitialAlpha = 100;
	this->m_particleSpeed = 70;
	this->m_particleAcceleration = 1.0f;
	this->m_particleUpwardForce = 1.0f;
	this->m_particleLifeTime = 0.2f;

	//this->m_soundBuffer.loadFromFile(this->m_pathsToSounds[0]);
	//this->m_shotSound.setBuffer(this->m_soundBuffer);
	
	// Move this to Weapon.cpp
	this->m_texture.loadFromFile(_pathToTexture);
	this->m_bulletTexture.loadFromFile(_pathToBulletTexture);
	this->m_body.setTexture(&this->m_texture);
	this->m_body.setTextureRect(this->m_frame);
	this->m_body.setFillColor(sf::Color::White);
	this->m_body.setSize(sf::Vector2f(this->m_frame.width, this->m_frame.height));
	this->m_body.setOrigin(0.0f, (this->m_body.getSize().y / 2.0f - this->m_barrelOffset.y));
}

Pistols::~Pistols()
{}

void Pistols::Shoot()
{
	Weapon::Shoot();
}

void Pistols::Reload()
{
	Weapon::Reload();
}

void Pistols::AngleControl(const sf::RenderWindow* target)
{
	Weapon::AngleControl(target);
}

void Pistols::update(const sf::RenderWindow* target, float deltaTime)
{
	Weapon::update(target, deltaTime);
}

void Pistols::updateInput(const sf::RenderWindow* target)
{
	Weapon::updateInput(target);
}

void Pistols::updateTime()
{
	Weapon::updateTime();
}

void Pistols::render(sf::RenderWindow* target)
{
	Weapon::render(target);
}
