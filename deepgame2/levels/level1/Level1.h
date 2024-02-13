#ifndef LEVEL1_H
#define LEVEL1_H

#include <SFML/Graphics.hpp>

class Level1
{
private:
	sf::ConvexShape ground;
	sf::ConvexShape celi;
	sf::ConvexShape wall;
	sf::ConvexShape stairs;
	
	//Box box;
	//Door door;
	//Ladder ladder;
	//Elevator elevator;
	//Cord cord;
	//Lamp lamp;

	sf::Sprite sprite;
	sf::Texture texture;

public:
	Level1();
	~Level1();

};

#endif