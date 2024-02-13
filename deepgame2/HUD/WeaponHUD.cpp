#include "WeaponHUD.h"

WeaponHUD::WeaponHUD() : isPressed(true)
{
    this->m_weaponScreenSize = sf::Vector2f(170, 20);
    //this->m_weaponScreenPosition = sf::Vector2f(0, 780);
    this->m_weaponScreenShape.setSize(this->m_weaponScreenSize);
    //this->m_weaponScreenShape.setPosition(this->m_weaponScreenPosition);
    this->m_weaponScreenShape.setFillColor(sf::Color::Red);
    
    this->m_weaponIconSize = sf::Vector2f(32, 10);
    //this->m_weaponIconPosition = sf::Vector2f(1, 787.5);
    this->m_weaponIcon.setSize(this->m_weaponIconSize);
    //this->m_weaponIcon.setPosition(this->m_weaponIconPosition);
    this->m_weaponIcon.setFillColor(sf::Color::White);
    this->m_weaponIcon.setOutlineColor(sf::Color::Black);
    this->m_weaponIcon.setOutlineThickness(1.0f);
    
    this->m_weaponScreenArr = std::vector<sf::RectangleShape>(5, this->m_weaponIcon);
	
    /*for(int i = 1; i <= this->m_weaponScreenArr.size(); i++)
    {
    	this->m_weaponScreenArr[i].setPosition(this->m_weaponIconSize.x * i + i, this->m_weaponIconPosition.y);
    }*/

    
    this->isPressed1 = true;
    this->isPressed2 = true;
    this->isPressed3 = true;
    this->isPressed4 = true;
    this->isPressed5 = true;
    
}

WeaponHUD::~WeaponHUD() {}


void WeaponHUD::update(sf::RenderWindow* target, sf::Vector2f viewPosition)
{    
    if (isPressed1)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            this->m_weaponScreenArr[0].setFillColor(sf::Color::Cyan);
            this->isPressed1 = false;
        }
    }
    else if (isPressed2)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            this->m_weaponScreenArr[1].setFillColor(sf::Color::Cyan);
            this->isPressed2 = false;
        }
    }
    else if(isPressed3)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        {
            this->m_weaponScreenArr[2].setFillColor(sf::Color::Cyan);
			this->isPressed3 = false;
        }
    }
    else if(isPressed4)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {
            this->m_weaponScreenArr[3].setFillColor(sf::Color::Cyan);
			this->isPressed4 = false;
        }
    }
    else if (isPressed5)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        {
            this->m_weaponScreenArr[4].setFillColor(sf::Color::Cyan);
            this->isPressed5 = false;
        }
    }

    //----------------------------------------------------------------------------Пізда нахуй ---\\
    
	if (!isPressed1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			this->m_weaponScreenArr[0].setFillColor(sf::Color::White);
			this->isPressed1 = true;
		}
	}
	else if (!isPressed2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			this->m_weaponScreenArr[1].setFillColor(sf::Color::White);
			this->isPressed2 = true;
		}
	}
	else if (!isPressed3)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			this->m_weaponScreenArr[2].setFillColor(sf::Color::White);
			this->isPressed3 = true;
		}
	}
	else if (!isPressed4)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			this->m_weaponScreenArr[3].setFillColor(sf::Color::White);
			this->isPressed4 = true;
		}
	}
	else if (!isPressed5)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			this->m_weaponScreenArr[4].setFillColor(sf::Color::White);
			this->isPressed5 = true;
		}
	}

	this->setPosition(target->getSize(), viewPosition);
}

void WeaponHUD::render(sf::RenderWindow* target)
{
    target->draw(this->m_weaponScreenShape);
    target->draw(this->m_weaponIcon);
    for (auto& item : this->m_weaponScreenArr)
    {
    	target->draw(item);
    }
}

void WeaponHUD::setPosition(sf::Vector2u windowSize, sf::Vector2f viewPosition)
{
    this->m_weaponScreenPosition = viewPosition;
    this->m_weaponIconPosition = viewPosition;

    this->m_weaponScreenShape.setPosition(this->m_weaponIconPosition);

   /* for (int i = 1; i <= this->m_weaponScreenArr.size(); i++)
	{
		this->m_weaponScreenArr[i].setPosition((this->m_weaponIconSize.x * i + i) + this->m_weaponIconPosition.x, this->m_weaponIconPosition.y);
	}*/
}