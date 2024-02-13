#ifndef WEAPONHUD_H
#define WEAPONHUD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "../equipment/weapon/Weapon.h"

class WeaponHUD
{
private:
	std::vector<Weapon*> m_weaponScreen;

	sf::RectangleShape m_weaponScreenShape;
	sf::Vector2f m_weaponScreenSize;
	sf::Vector2f m_weaponScreenPosition;

	sf::RectangleShape m_weaponIcon;
	sf::Vector2f m_weaponIconSize;
	sf::Vector2f m_weaponIconPosition;
	std::vector<sf::RectangleShape> m_weaponScreenArr;

	sf::Texture m_weaponScreenTexture;

    bool isPressed;

	
	bool isPressed1;
    bool isPressed2;
    bool isPressed3;
    bool isPressed4;
    bool isPressed5;
	

public:
	WeaponHUD();
	virtual ~WeaponHUD();
public:
	void update(sf::RenderWindow* target, sf::Vector2f viewPosition);
	void render(sf::RenderWindow* target);

public:
	void setPosition(sf::Vector2u windowSize, sf::Vector2f viewPosition);
};

#endif