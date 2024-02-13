#ifndef INFORMATION_H
#define INFORMATION_H

#include <SFML/Graphics.hpp>
#include <string>

class Information
{
private:
	sf::Font m_infoEventFont;
	std::string m_infoEvent;
	sf::Text m_infoEventText;
	sf::Vector2f m_infoEventPosition;

public:
	Information();
	virtual ~Information();
public:
	void update(sf::RenderWindow* target, sf::Vector2f viewPosition);
	void render(sf::RenderWindow* target);

public:
	void setPosition(sf::Vector2u windowSize, sf::Vector2f viewPosition);
};

#endif