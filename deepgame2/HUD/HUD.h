#ifndef HUD_H
#define HUD_H

//#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//#include "../equipment/weapon/Weapon.h"

#include "Information.h"
#include "Gadget.h"
#include "WeaponHUD.h"
#include "HP.h"

class HUD
{		
public:
	WeaponHUD m_weapons;
	Gadget m_gadgets;
	HP m_hp;
	Information m_info;

public:
	HUD();
	virtual ~HUD();

public:
	void update(sf::RenderWindow* target, sf::Vector2f viewPosition);
	void render(sf::RenderWindow* window);
};

#endif

