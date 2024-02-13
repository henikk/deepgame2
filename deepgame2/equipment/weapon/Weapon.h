#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#include "../../types.h"
#include "../../FX/Particle.h"
#include "Bullet.h"

class Weapon
{
private:
	std::string m_pathToTexture;
	std::string m_pathToBulletTexture;
	std::string m_gunName;
	std::string m_description;

private:
	std::vector<Bullet> m_bullets;
	std::vector<Particle> m_shotSmokeArray;

private:
	bool m_hasShot;
	bool m_canShoot;
	bool m_shotAnimating;
	bool m_emptyAnimating;
	bool m_reloadAnimating;
	bool m_isFlashShown;

private:
	sf::Clock m_shootClock;
	sf::Clock m_reloadClock;
	sf::Clock m_reloadAnimationClock;
	sf::Time m_shootElapsedTime;
	sf::Time m_reloadElapsedTime;
	sf::Time m_reloadAnimationElapsedTime;

private:
	u8 m_flashFramesCount;
	sf::Texture m_flashTexture;
	sf::IntRect m_flashFrame;
	sf::Sprite m_flashSprite;

private:
	float accuracyControl() const;
	const void animateShot();
	const void animateEmpty();
	const void animateReload();
	const void showFlash(float angle);

protected:
	sf::Texture m_texture;
	sf::Texture m_bulletTexture;
	sf::RectangleShape m_body;
	sf::Vector2f m_gunOffset;
	sf::Vector2f m_barrelOffset;
	sf::Vector2f m_position;
	sf::Vector2f m_barrelPosition;
	float m_angle;

protected:
	u8 m_shotFrameCount;
	u8 m_emptyFrameCount;
	u8 m_reloadFrameCount;
	sf::IntRect m_frame;

protected:
	u8 m_damage;					// How much hp will gone when hit
	u8 m_accuracy;					// Chance to hit near target from 0% to 100%
	u8 m_bulletsPerShot;			// How many bullets will spawn when shot
	u16 m_bulletSpeed;				// Pixels per "some" time ¯\_(ツ)_/¯
	u16 m_fireRange;				// Max distance bullet can reach
	u16 m_capacity;					// Max capacity of 1 magazine
	u16 m_ammo;						// Avaible ammo in stock
	u16 m_magazine = m_capacity;	// Ammo in magazine is avaible to shoot
	float m_reloadTime;				// Reload speed in seconds. Minimum speed is animation speed
	float m_fireRate;				// Shots per second

protected:
	sf::Color m_particleColor;
	std::string m_pathToParticleTexture;
	sf::Texture m_particleSmokeTexture;	
	sf::Vector2f m_particleInitialScale;
	sf::Vector2f m_particleMaxScale;
	i8 m_particleRotationSpeed;
	u8 m_particleInitialAlpha;
	u16 m_particleSpeed;
	float m_particleAcceleration;
	float m_particleUpwardForce;
	float m_particleLifeTime;

protected:
	std::vector<std::string> m_pathsToSounds;
	//sf::SoundBuffer m_soundBuffer;
	//sf::Sound m_shotSound;

protected:
	bool m_isSelected;
	bool m_singleShot;
	bool m_showSmoke;
	bool m_showFlash;
	bool m_playerLookDirection;

public:
	Weapon(std::string _pathToTexture, std::string _pathToBulletTexture, std::string _pathToParticleTexture, std::vector<std::string> _pathsToSounds);
	virtual ~Weapon() = 0;
	
public:
	virtual void Shoot() = 0;
	virtual void Reload() = 0;

public: 
	virtual void AngleControl(const sf::RenderWindow* target) = 0; // public ?
	__forceinline virtual void Select() = 0 { this->m_isSelected = true; }
	__forceinline virtual void Hide() = 0 { this->m_isSelected = false; }

public:
	// Setters
	__forceinline virtual void setDamage(u8 damage) = 0;
	__forceinline virtual void setAccuracy(u8 accuracy) = 0;
	__forceinline virtual void setFireRate(float fireRate) = 0;
	__forceinline virtual void setCapacity(u16 capacity) = 0;
	__forceinline virtual void setAmmo(u16 ammo) = 0;
	__forceinline virtual void setMagazine(u16 magazine) = 0;
	__forceinline virtual void setPosition(sf::Vector2f position) = 0;

	// Getters
	__forceinline virtual const u8 getDamage() const = 0;
	__forceinline virtual const u8 getAccuracy() const = 0;
	__forceinline virtual const float getFireRate() const = 0;
	__forceinline virtual const u16 getCapacity() const = 0;
	__forceinline virtual const u16 getAmmo() const = 0;
	__forceinline virtual const u16 getMagazine() const = 0;
	__forceinline virtual const sf::Vector2f getPosition() const = 0;

public:
	virtual void update(const sf::RenderWindow* target, float deltaTime) = 0;
	virtual void updateInput(const sf::RenderWindow* target) = 0;
	virtual void updateTime() = 0;
	virtual void render(sf::RenderWindow* target) = 0;
};

#endif
