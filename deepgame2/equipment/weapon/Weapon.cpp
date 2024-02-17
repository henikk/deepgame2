#include "Weapon.h"

Weapon::Weapon(std::string _pathToTexture, std::string _pathToBulletTexture, std::string _pathToShellTexture, std::vector<std::string> _pathsToSounds)
	: m_pathToTexture(_pathToTexture), m_pathToBulletTexture(_pathToBulletTexture), m_pathToShellTexture(_pathToShellTexture), m_pathsToSounds(_pathsToSounds), m_canShoot(true), m_isSelected(false)
{
	this->m_currentAccuracy = 100.0f; // Set maximum accuracy from the begining
	this->m_particleSmokeTexture.loadFromFile("textures/particles/smoke.png");

	this->initCursor();
	this->initFlash();
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
				this->m_accuracyAngle = 0.0f;

				this->m_hasShot = true;
				this->m_shotAnimating = true;
				this->m_frame.left = 0;

				for (int i = 0; i < this->m_bulletsPerShot; i++)
				{
					if (this->m_playerLookDirection)
						this->m_accuracyAngle = this->addRandToAngle();
					else
						this->m_accuracyAngle = 180.0f - this->addRandToAngle();

					this->spawnBullet();
					this->spawnSmoke();
					
				}
				this->m_magazine--;

				this->spawnShell();
				this->makeShotSound();
				this->showFlash();
				this->decreaseAccuracy();
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

			if (this->m_ammo >= this->m_capacity - this->m_magazine) // Завантажити відсутні патрони
			{
				u16 missingAmmo = this->m_capacity - this->m_magazine;
				this->m_magazine += missingAmmo;
				this->m_ammo -= missingAmmo;
			}
			else // Завантажити всі доступні патрони
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

	this->m_barrelPosition = sf::Vector2f(this->m_position.x - this->m_gunOffset.x + std::cosf(this->m_angle) * this->m_barrelOffset.x,
		this->m_position.y + this->m_gunOffset.y + std::sinf(this->m_angle) * this->m_barrelOffset.x);

	this->m_ejectionPortPosition = sf::Vector2f(this->m_position.x - this->m_gunOffset.x + std::cosf(this->m_angle) * this->m_ejectionPortOffset.x,
		this->m_position.y + this->m_gunOffset.y + std::sinf(this->m_angle) * this->m_ejectionPortOffset.x);

	/* In case of emergency
			this->m_barrelAngle = sf::Vector2f(this->m_position.x - this->m_gunOffset.x + std::cosf(this->m_angle) * this->m_barrelOffset.x,
		this->m_position.y + this->m_gunOffset.y - this->m_barrelOffset.y + std::sinf(this->m_angle) * this->m_barrelOffset.x);
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

float Weapon::addRandToAngle() const
{
	u8 newAccuracy = static_cast<u8>((100.0f - this->m_currentAccuracy) / 4.0f); // 4 here because accuracy range is too "small"

	if (this->m_currentAccuracy < 100)
		return this->m_angle + rand() % (newAccuracy + 1) - static_cast<float>(newAccuracy / 2);
	else
		return this->m_angle;
}

void Weapon::increaseAccuracy(float deltaTime)
{
	if (this->m_dynamicAccuracy)
	{
		if (this->m_currentAccuracy < this->m_maxAccuracy)
			this->m_currentAccuracy += this->m_accuracyRecoverySpeed * deltaTime;
		else
			this->m_currentAccuracy = this->m_maxAccuracy;
	}
	else
	{
		this->m_currentAccuracy = this->m_maxAccuracy;
	}
}

void Weapon::decreaseAccuracy()
{
	if (this->m_currentAccuracy - this->m_recoil < 0)
		this->m_currentAccuracy = 0;
	else
		this->m_currentAccuracy -= this->m_recoil;
}

void Weapon::changeCursorOpacity()
{
	u8 cursorAlpha = static_cast<u8>(this->m_currentAccuracy * 2.55f);

	this->m_topCursor.setColor(sf::Color(
		this->m_cursorColor.r,
		this->m_cursorColor.g,
		this->m_cursorColor.b,
		cursorAlpha
	));
	this->m_bottomCursor.setColor(sf::Color(
		this->m_cursorColor.r,
		this->m_cursorColor.g,
		this->m_cursorColor.b,
		cursorAlpha
	));
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

const void Weapon::showFlash()
{
	if (!this->m_isFlashShown && this->m_showFlash)
	{
		this->m_flashFrame.left = rand() % this->m_flashFramesCount * m_flashFrame.width;

		this->m_flashSprite.setTextureRect(this->m_flashFrame);
		this->m_flashSprite.setPosition(this->m_barrelPosition);
		this->m_flashSprite.setRotation(this->m_accuracyAngle);
		this->m_flashSprite.setColor(sf::Color(255, 230, 200, rand() % 201 + 55));

		this->m_isFlashShown = true;
	}
}

const void Weapon::spawnBullet()
{
	this->m_bullets.emplace_back(Bullet(&this->m_bulletTexture, this->m_barrelPosition, this->m_bulletSpeed,
		this->m_damage, this->m_accuracyAngle, this->m_fireRange));
}

const void Weapon::spawnShell()
{
	this->m_shells.emplace_back(Particle(
		this->m_shellColor,
		&this->m_shellTexture,
		this->m_ejectionPortPosition,
		this->m_shellInitialScale,
		this->m_shellMaxScale,
		this->m_shellInitialAlpha,
		this->m_shellRotationSpeed,
		this->m_shellSpeed,
		this->m_shellAcceleration,
		-90.0f + rand() % (10 + 1) - static_cast<float>(10 / 2),
		-this->m_shellDownwardForce,
		this->m_shellLifeTime
	));
}

const void Weapon::spawnSmoke()
{
	if (this->m_showSmoke)
	{
		u8 smokeAngle = (100 - this->m_maxAccuracy) * 2;

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
			this->m_accuracyAngle + rand() % (smokeAngle + 1) - static_cast<float>(smokeAngle / 2),
			this->m_particleUpwardForce,
			this->m_particleLifeTime
		));
	}
}

const void Weapon::makeShotSound()
{
	this->m_soundBuffer.loadFromFile(this->m_pathsToSounds[0]);
	this->m_shotSound.setBuffer(this->m_soundBuffer);
	this->m_shotSound.play();
}

void Weapon::initCursor()
{
	this->m_cursorColor = { 0, 250, 100 };
	this->m_cursorScale = { 0.40f, 0.40f };

	this->m_cursorTexture.loadFromFile("textures/cursor/arrow4.png");

	this->m_topCursor.setTexture(this->m_cursorTexture);
	this->m_topCursor.setScale(this->m_cursorScale);
	this->m_topCursor.setOrigin(this->m_cursorTexture.getSize().x / 2.0f, this->m_cursorTexture.getSize().y / 2.0f);
	this->m_topCursor.setColor(this->m_cursorColor);

	this->m_bottomCursor.setTexture(this->m_cursorTexture);
	this->m_bottomCursor.setScale({ this->m_cursorScale.x, -this->m_cursorScale.y });
	this->m_bottomCursor.setOrigin(this->m_cursorTexture.getSize().x / 2.0f, this->m_cursorTexture.getSize().y / 2.0f);
	this->m_bottomCursor.setColor(this->m_cursorColor);
}

void Weapon::initFlash()
{
	this->m_isFlashShown = false;
	this->m_flashFramesCount = 5;
	this->m_flashFrame = { 0, 0, 256, 128 };
	this->m_flashTexture.loadFromFile("textures/particles/flash_sheet.png");
	this->m_flashTexture.setSmooth(true);
	this->m_flashSprite.setTexture(this->m_flashTexture);
	this->m_flashSprite.setTextureRect(this->m_flashFrame);
	this->m_flashSprite.setOrigin({ 0.0f, this->m_flashTexture.getSize().y / 2.0f });
	this->m_flashSprite.setScale({ 0.25f, 0.35f });
}

void Weapon::updateBullets(float deltaTime)
{
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
}

void Weapon::updateShells(float deltaTime)
{
	for (auto it = this->m_shells.begin(); it != this->m_shells.end();)
	{
		if (!it->isAlive())
		{
			it = this->m_shells.erase(it);
		}
		else
		{
			it->update(deltaTime);
			++it;
		}
	}
}

void Weapon::updateSmokeParticles(float deltaTime)
{
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
}

void Weapon::renderBullets(sf::RenderWindow* target)
{
	for (auto& bullet : this->m_bullets)
		bullet.render(target);
}

void Weapon::renderShells(sf::RenderWindow* target)
{
	for (auto& shell : this->m_shells)
		shell.render(target);
}

void Weapon::renderSmokeParticles(sf::RenderWindow* target)
{
	if (this->m_showSmoke)
		for (auto& particle : this->m_shotSmokeArray)
			particle.render(target);
}

void Weapon::renderFlashes(sf::RenderWindow* target)
{
	if (this->m_showFlash && this->m_isFlashShown)
	{
		target->draw(this->m_flashSprite);

		if (this->m_flashClock.getElapsedTime().asSeconds() >= 0.03f)
		{
			this->m_isFlashShown = false;
			this->m_flashClock.restart();
		}
	}
}

void Weapon::renderCursor(sf::RenderWindow* target)
{
	target->draw(this->m_topCursor);
	target->draw(this->m_bottomCursor);
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


	if (this->m_isSelected)
	{
		this->animateShot();
		this->animateEmpty();
		this->animateReload();
		this->updateInput(target);
	}
	this->updateTime();
	this->updateBullets(deltaTime);
	this->updateShells(deltaTime);
	this->updateSmokeParticles(deltaTime);

	this->increaseAccuracy(deltaTime);
	this->changeCursorOpacity();
}

void Weapon::updateInput(const sf::RenderWindow* target)
{
	sf::Vector2f mouseWorldPosition = target->mapPixelToCoords(sf::Mouse::getPosition(*target));

	this->m_distanceBetweenCursors = (100.0f - this->m_currentAccuracy) / 2.0f;
	this->m_topCursor.setPosition(mouseWorldPosition.x, (mouseWorldPosition.y - this->m_distanceBetweenCursors + 1));
	this->m_bottomCursor.setPosition(mouseWorldPosition.x, (mouseWorldPosition.y + this->m_distanceBetweenCursors));

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

	AngleControl(target);
}

void Weapon::updateTime()
{
	this->m_shootElapsedTime = this->m_shootClock.getElapsedTime();
	this->m_reloadElapsedTime = this->m_reloadClock.getElapsedTime();
	this->m_reloadAnimationElapsedTime = this->m_reloadAnimationClock.getElapsedTime();
}

void Weapon::render(sf::RenderWindow* target)
{
	this->renderBullets(target);
	this->renderSmokeParticles(target);
	this->renderFlashes(target);

	if (this->m_isSelected)
	{
		target->setTitle("Magazine: " + std::to_string(this->m_magazine) + " | Accuracy: " + std::to_string((int)this->m_currentAccuracy));

		target->draw(this->m_body);

		this->renderCursor(target);
	}	
	this->renderShells(target); // [TEMP]
}
