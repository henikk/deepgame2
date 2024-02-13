#include "Weapon.h"

Weapon::Weapon(std::string _pathToTexture, std::string _pathToBulletTexture, std::string _pathToParticleTexture, std::vector<std::string> _pathsToSounds)
	: m_pathToTexture(_pathToTexture), m_pathToBulletTexture(_pathToBulletTexture), m_pathToParticleTexture(_pathToParticleTexture), m_pathsToSounds(_pathsToSounds), m_canShoot(true), m_isSelected(false)
{
	this->m_isFlashShown = false;
	this->m_flashFramesCount = 5;
	this->m_flashFrame = {0, 0, 256, 128 };
	this->m_flashTexture.loadFromFile("textures/particles/flash_sheet.png");
	this->m_flashTexture.setSmooth(true);
	this->m_flashSprite.setTexture(this->m_flashTexture);
	this->m_flashSprite.setTextureRect(this->m_flashFrame);
	this->m_flashSprite.setOrigin({ 0.0f, this->m_flashTexture.getSize().y / 2.0f });
	this->m_flashSprite.setScale({ 0.25f, 0.35f });
}

Weapon::~Weapon(){}

void Weapon::Shoot()
{
	if (this->m_canShoot)
	{
		if (this->m_shootElapsedTime.asSeconds() >= 1.0f / this->m_fireRate) // Make shot per fire rate
		{
			if (this->m_magazine > 0)
			{
				u8 smokeAngle = (100 - this->m_accuracy) * 2;
				float accuracyAngle = 0.0f;

				this->m_hasShot = true;
				this->m_shotAnimating = true;
				this->m_frame.left = 0;

				for (int i = 0; i < this->m_bulletsPerShot; i++)
				{
					if (this->m_playerLookDirection)
						accuracyAngle = this->accuracyControl();
					else
						accuracyAngle = 180.0f - this->accuracyControl();

					this->m_bullets.emplace_back(Bullet(&this->m_bulletTexture, this->m_barrelPosition, this->m_bulletSpeed,
						this->m_damage, accuracyAngle, this->m_fireRange));

					if (this->m_showSmoke)
					{
						this->m_shotSmokeArray.emplace_back(Particle(
							this->m_particleColor,
							&this->m_particleSmokeTexture,
							this->m_barrelPosition,
							this->m_particleInitialScale,
							this->m_particleMaxScale,
							this->m_particleRotationSpeed,
							this->m_particleInitialAlpha,
							this->m_particleSpeed,
							this->m_particleAcceleration,
							accuracyAngle + rand() % (smokeAngle + 1) - static_cast<float>(smokeAngle / 2),
							this->m_particleUpwardForce,
							this->m_particleLifeTime
						));
					}

				}
				this->m_magazine--;

				if (this->m_showFlash)
					this->showFlash(accuracyAngle);
			}
			this->m_shootClock.restart();
		}
	}	
}

void Weapon::Reload()
{
	if (this->m_canShoot)
	{		
		if (this->m_magazine < this->m_capacity && this->m_ammo > 0)
		{
			this->m_canShoot = false;
			this->m_reloadAnimating = true;
			this->m_frame.left = 0;
			this->m_reloadClock.restart();

			if (this->m_ammo >= this->m_capacity - this->m_magazine) // Load missing ammo
			{
				this->m_magazine += this->m_capacity - this->m_magazine;
				this->m_ammo -= this->m_capacity - this->m_magazine;
			}
			else // Load all ammo
			{
				this->m_magazine += this->m_ammo;
				this->m_ammo = 0;
			}
		}
	}
}

void Weapon::AngleControl(const sf::RenderWindow* target)
{
	sf::Vector2f worldPos = target->mapPixelToCoords(sf::Mouse::getPosition(*target));
	
	this->m_angle = atan2(worldPos.y - this->m_position.y - this->m_gunOffset.y,
		worldPos.x - this->m_position.x - this->m_gunOffset.x);

	this->m_barrelPosition = sf::Vector2f(this->m_position.x - this->m_gunOffset.x + std::cos(this->m_angle) * this->m_barrelOffset.x,
		this->m_position.y + this->m_gunOffset.y + std::sin(this->m_angle) * this->m_barrelOffset.x);

	/* In case of emergency
			this->m_barrelAngle = sf::Vector2f(this->m_position.x - this->m_gunOffset.x + std::cos(this->m_angle) * this->m_barrelOffset.x,
		this->m_position.y + this->m_gunOffset.y - this->m_barrelOffset.y + std::sin(this->m_angle) * this->m_barrelOffset.x);
	*/

	this->m_angle = this->m_angle * 180.0f / 3.14f;

	if (worldPos.x >= this->m_position.x)// if player looking right
	{
		this->m_playerLookDirection = true;

		this->m_body.setScale({ 1.0f, 1.0f });
		this->m_body.setRotation(this->m_angle);
	}
	else
	{
		this->m_playerLookDirection = false;

		this->m_body.setScale({ -1.0f, 1.0f });
		this->m_angle = 180.0f - this->m_angle;
		this->m_body.setRotation(-this->m_angle);
	}
}

float Weapon::accuracyControl() const
{
	u8 temp = (100 - this->m_accuracy) / 4; // 4 here because accuracy range is too "small"

	if (this->m_accuracy < 100)
		return this->m_angle + rand() % (temp + 1) - static_cast<float>(temp / 2);
	else
		return this->m_angle;
}

const void Weapon::animateShot()
{
	if (this->m_shotAnimating)
	{
		this->m_frame.top = this->m_frame.height;

		if (this->m_frame.left == this->m_frame.width * this->m_shotFrameCount - this->m_frame.width)
		{
			this->m_frame.left = 0;
			this->m_frame.top = 0;
			this->m_shotAnimating = false;
		}
		else
		{
			this->m_frame.left += this->m_frame.width;
		}

		this->m_body.setTextureRect(this->m_frame);
	}	
}

const void Weapon::animateEmpty()
{
	if (this->m_emptyAnimating)
	{
		if (this->m_frame.left == this->m_frame.width * this->m_emptyFrameCount - this->m_frame.width)
			this->m_emptyAnimating = false;
		else
			this->m_frame.left += this->m_frame.width;
		this->m_body.setTextureRect(this->m_frame);
	}
}

const void Weapon::animateReload()
{
	if (this->m_reloadAnimating)
	{
		if (this->m_frame.left == this->m_frame.width * this->m_reloadFrameCount - this->m_frame.width || !this->m_isSelected)
		{
			this->m_frame.left = 0;
			this->m_reloadAnimating = false;
		}
		else if (this->m_reloadAnimationElapsedTime.asSeconds() >= this->m_reloadTime / this->m_reloadFrameCount)
		{
			this->m_reloadAnimationClock.restart();
			this->m_frame.left += this->m_frame.width;
		}
		this->m_body.setTextureRect(this->m_frame);
	}
}

const void Weapon::showFlash(float angle)
{
	if (!this->m_isFlashShown)
	{
		this->m_flashFrame.left = rand() % this->m_flashFramesCount * m_flashFrame.width;

		this->m_flashSprite.setTextureRect(this->m_flashFrame);
		this->m_flashSprite.setPosition(this->m_barrelPosition);
		this->m_flashSprite.setRotation(angle);
		this->m_flashSprite.setColor(sf::Color(255, 250, 230, rand() % 201 + 55));

		this->m_isFlashShown = true;
	}
}

void Weapon::update(const sf::RenderWindow* target, float deltaTime)
{
	
	this->m_body.setPosition(this->m_position + this->m_gunOffset);

	// Reload
	if (this->m_reloadElapsedTime.asSeconds() > this->m_reloadTime && this->m_reloadAnimating == false)
		this->m_canShoot = true;

	// Emptying
	if (this->m_magazine <= 0)
		this->m_emptyAnimating = true;

	// Clear or Update bullets array
	for (auto it = this->m_bullets.begin(); it != this->m_bullets.end();)
	{
		if (!it->isAlive())
		{
			it = this->m_bullets.erase(it);
		}
		else
		{
			it->update(deltaTime);
			++it;
		}
	}
	// Clear or Update smoke particles array
	if (this->m_showSmoke)
	{
		for (auto it = this->m_shotSmokeArray.begin(); it != this->m_shotSmokeArray.end();)
		{
			if (!it->isAlive())
			{
				it = this->m_shotSmokeArray.erase(it);
			}
			else
			{
				it->update(deltaTime);
				++it;
			}
		}
	}

	if (this->m_isSelected)
	{
		this->animateShot();
		this->animateEmpty();
		this->animateReload();
		this->updateInput(target);
	}
	this->updateTime();
	
}

void Weapon::updateInput(const sf::RenderWindow* target)
{
	AngleControl(target);

	// Keys binding
	if (this->m_singleShot)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->m_hasShot)
		{
			this->Shoot();
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->m_hasShot = false;
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->m_singleShot)
	{
		this->Shoot();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->Reload();
	}
}

void Weapon::updateTime()
{
	this->m_shootElapsedTime = this->m_shootClock.getElapsedTime();
	this->m_reloadElapsedTime = this->m_reloadClock.getElapsedTime();
	this->m_reloadAnimationElapsedTime = this->m_reloadAnimationClock.getElapsedTime();
}

void Weapon::render(sf::RenderWindow* target)
{
	if (this->m_isSelected)
	{
		target->setTitle("Magazine: " + std::to_string(this->m_magazine)); // [DEBUG]

		target->draw(this->m_body);
	}

	if (this->m_showSmoke)
		for (auto& particle : this->m_shotSmokeArray)
			particle.render(target);

	for (auto& bullet : this->m_bullets)
		bullet.render(target);
	
	if (this->m_isFlashShown && this->m_showFlash)
	{
		target->draw(this->m_flashSprite);
		this->m_isFlashShown = false;
	}

}
