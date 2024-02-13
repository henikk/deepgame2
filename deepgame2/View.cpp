#include "View.h"

View::View(sf::Vector2f center, sf::Vector2u size)
{
	this->followDelay = 0.25f;
	this->zoom = 1.0f;
	
	this->view.setCenter(center);
	this->view.setSize(sf::Vector2f(size));
	this->view.zoom(zoom);
}

View::~View()
{
}

void View::update(sf::Vector2f center, float deltaTime)
{
	// DEBUG
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		this->view.zoom(0.9f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		this->view.zoom(1.1f);

    float t = deltaTime / this->followDelay;
    t = t > 1.0f ? 1.0f : t;

	this->view.setCenter(this->view.getCenter() + (center - this->view.getCenter()) * t);
}
