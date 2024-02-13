#include "Information.h"

Information::Information()
{
	this->m_infoEvent = "TEXT";
	//this->m_infoEventPosition = sf::Vector2f(730, 50);
	this->m_infoEventFont.loadFromFile("src/font/orange kid.otf");
	this->m_infoEventText.setString(this->m_infoEvent);
	this->m_infoEventText.setFont(this->m_infoEventFont);
	this->m_infoEventText.setCharacterSize(20);
	this->m_infoEventText.setFillColor(sf::Color::White);
	//this->m_infoEventText.setPosition(this->m_infoEventPosition);
}

Information::~Information() {}


void Information::update(sf::RenderWindow* target, sf::Vector2f viewPosition)
{
	this->setPosition(target->getSize(), viewPosition);
}

void Information::render(sf::RenderWindow* target)
{
    target->draw(this->m_infoEventText);
}


void Information::setPosition(sf::Vector2u windowSize, sf::Vector2f viewPosition)
{
	this->m_infoEventPosition = viewPosition;
	this->m_infoEventText.setPosition(this->m_infoEventPosition + sf::Vector2f(200, -50));
}