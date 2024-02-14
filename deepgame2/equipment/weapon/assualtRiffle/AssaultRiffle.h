#ifndef ASSAULT_H
#define ASSAULT_H

#include "../Weapon.h"
#include "../Bullet.h"

class AssaultRiffle: public Weapon
{
public:
	AssaultRiffle(std::string _pathToTexture, std::string _pathToBulletTexture, std::string _pathToParticleTexture, std::vector<std::string> _pathsToSounds);
	virtual ~AssaultRiffle() override;

public:
	virtual void Shoot() override;
	virtual void Reload() override;

public:
	virtual void AngleControl(const sf::RenderWindow* target) override;
	__forceinline virtual void Select() override { this->m_isSelected = true; }
	__forceinline virtual void Hide() override { this->m_isSelected = false; }

public:
	// Setters
	__forceinline virtual void setDamage(u8 damage) override { this->m_damage = damage; }
	__forceinline virtual void setAccuracy(u8 accuracy) override { this->m_maxAccuracy = accuracy; }
	__forceinline virtual void setFireRate(float fireRate) override { this->m_fireRate = fireRate; }
	__forceinline virtual void setCapacity(u16 capacity) override { this->m_capacity = capacity; }
	__forceinline virtual void setAmmo(u16 ammo) override { this->m_ammo = ammo; }
	__forceinline virtual void setMagazine(u16 magazine) override { this->m_magazine = magazine; }
	__forceinline virtual void setPosition(sf::Vector2f position) override { this->m_position = position; }

	// Getters
	__forceinline virtual const u8 getDamage() const override { return this->m_damage; }
	__forceinline virtual const u8 getAccuracy() const override { return this->m_maxAccuracy; }
	__forceinline virtual const float getFireRate() const override { return this->m_fireRate; }
	__forceinline virtual const u16 getCapacity() const override { return this->m_capacity; }
	__forceinline virtual const u16 getAmmo() const override { return this->m_ammo; }
	__forceinline virtual const u16 getMagazine() const override { return this->m_magazine; }
	__forceinline virtual const sf::Vector2f getPosition() const override { return this->m_position; }

public:
	virtual void update(const sf::RenderWindow* target, float deltaTime) override;
	virtual void updateInput(const sf::RenderWindow* target) override;
	virtual void updateTime() override;
	virtual void render(sf::RenderWindow* target) override;
};

#endif