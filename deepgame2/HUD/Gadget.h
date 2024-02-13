#ifndef GADGET_H
#define GADGET_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>



class Gadget
{
private:
	std::vector<int> m_gadgetsScreen;
	sf::RectangleShape m_gadgetsScreenShape;
	sf::Texture m_gadgetsScreenTexture;
	sf::Vector2f m_gadgetsScreenSize;
	sf::Vector2f m_gadgetsScreenPosition;

public:
	Gadget();
	virtual ~Gadget();
public:
	void update(sf::RenderWindow* target, sf::Vector2f viewPosition);
	void render(sf::RenderWindow* target);

public:
	void setPosition(sf::Vector2u windowSize, sf::Vector2f viewPosition);
};

#endif

