#include "Gadget.h"

Gadget::Gadget()
{
	this->m_gadgetsScreenSize = sf::Vector2f(170, 35);
	//this->m_gadgetsScreenPosition = sf::Vector2f(630, 0);
	this->m_gadgetsScreenShape.setSize(this->m_gadgetsScreenSize);
	//this->m_gadgetsScreenShape.setPosition(this->m_gadgetsScreenPosition);
	this->m_gadgetsScreenShape.setFillColor(sf::Color::White);
}

Gadget::~Gadget() {}

void Gadget::update(sf::RenderWindow* target, sf::Vector2f viewPosition)
{
    this->setPosition(target->getSize(), viewPosition);
}

void Gadget::render(sf::RenderWindow* target)
{
	target->draw(this->m_gadgetsScreenShape);
}

void Gadget::setPosition(sf::Vector2u windowSize, sf::Vector2f viewPosition)
{
	this->m_gadgetsScreenPosition = viewPosition;
	this->m_gadgetsScreenShape.setPosition(m_gadgetsScreenPosition + sf::Vector2f(100, -100));
}
