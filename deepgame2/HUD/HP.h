#ifndef HP_H
#define HP_H

#include <SFML/Graphics.hpp>
#include <string>



class HP
{
private:
    sf::Font m_HnAFont;
    std::string m_healthValue;
    std::string m_armorValue;
    sf::Text m_healthText;
    sf::Text m_armorText;

    sf::RectangleShape m_HnAScreenShape;
    sf::Texture m_HnAScreenTexture;
    sf::Vector2f m_HnAScreenSize;
    sf::Vector2f m_HnAScreenPosition;

	// Player stats
	uint8_t m_playerHp;
	uint8_t m_playerArmor;

public:
    HP();
    virtual ~HP();

public:
    void update(sf::RenderWindow* target, sf::Vector2f viewPosition);
    void render(sf::RenderWindow* target);

public:
	void setPlayerHp(uint8_t hp) { this->m_playerHp = hp; }
	void setPlayerArmor(uint8_t armor) { this->m_playerArmor = armor; }

public:
    void setPosition(sf::Vector2u windowSize, sf::Vector2f viewPosition);
};

#endif