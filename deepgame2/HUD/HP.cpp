#include "HP.h"
#include <iostream>
HP::HP()
{
	this->m_HnAScreenSize = sf::Vector2f(170, 5);
	//this->m_HnAScreenPosition = sf::Vector2f(3, 3);
	this->m_HnAScreenShape.setSize(this->m_HnAScreenSize);
	//this->m_HnAScreenShape.setPosition(this->m_HnAScreenPosition);
	this->m_HnAScreenShape.setFillColor(sf::Color::Red);
	this->m_HnAScreenShape.setOutlineColor(sf::Color(59, 59, 59)); // grey
	this->m_HnAScreenShape.setOutlineThickness(3);
	
	this->m_HnAFont.loadFromFile("src/font/orange kid.otf");
	
	// Health
	this->m_healthValue = std::to_string(this->m_playerHp);
	this->m_healthText.setFont(this->m_HnAFont);
	this->m_healthText.setFillColor(sf::Color::Red);
	this->m_healthText.setString(this->m_healthValue);
	this->m_healthText.setCharacterSize(20);
	//this->m_healthText.setPosition(this->m_HnAScreenPosition);
	
	// Armor
	this->m_armorValue = std::to_string(this->m_playerArmor);
	this->m_armorText.setFont(this->m_HnAFont);
	this->m_armorText.setFillColor(sf::Color::Blue);
	this->m_armorText.setString(this->m_armorValue);
	this->m_armorText.setCharacterSize(20);
	//this->m_armorText.setPosition(this->m_HnAScreenPosition.x + 30.0f,this->m_HnAScreenPosition.y);
}

HP::~HP() {}


void HP::update(sf::RenderWindow* target, sf::Vector2f viewPosition)
{
	this->m_healthValue = std::to_string(this->m_playerHp);
	this->m_healthText.setString(this->m_healthValue);
	
	this->m_armorValue = std::to_string(this->m_playerArmor);
	this->m_armorText.setString(this->m_armorValue);

	this->setPosition(target->getSize(), viewPosition);
}

void HP::render(sf::RenderWindow* target)
{
	target->draw(this->m_HnAScreenShape);
	target->draw(this->m_healthText);
	target->draw(this->m_armorText);
}


void HP::setPosition(sf::Vector2u windowSize, sf::Vector2f viewPosition)
{
	this->m_HnAScreenPosition = viewPosition;

	this->m_HnAScreenShape.setPosition(this->m_HnAScreenPosition + sf::Vector2f(-100.0f, -100.0f));
	this->m_healthText.setPosition(viewPosition);
	this->m_armorText.setPosition(viewPosition);
}
