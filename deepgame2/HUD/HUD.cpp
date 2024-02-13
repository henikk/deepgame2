#include "HUD.h"

HUD::HUD()
{	
}

HUD::~HUD()
{}

void HUD::update(sf::RenderWindow* target, sf::Vector2f viewPosition)
{
	this->m_weapons.update(target, viewPosition);
	this->m_gadgets.update(target, viewPosition);
	this->m_hp.update(target, viewPosition);
	this->m_info.update(target, viewPosition);
}

void HUD::render(sf::RenderWindow* target)
{
	this->m_weapons.render(target);
	this->m_gadgets.render(target);
	this->m_hp.render(target);	
	this->m_info.render(target);
}
