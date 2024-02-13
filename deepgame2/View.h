#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

#include "../../external/transition/SigmoidTrasition.hpp"

class View
{
private:
	sf::View view;

private:
	float followDelay;
	float zoom;

public:
	View(sf::Vector2f center, sf::Vector2u size);
	~View();

public:
	void update(sf::Vector2f center, float deltaTime);

public:
	__forceinline const sf::View getView() const { return this->view; }

};

#endif

