﻿#ifndef GAME_H
#define GAME_H

#include <ctime>

#include "Window.h"
#include "Player.h"
#include "HUD/HUD.h"
#include "View.h"

#include "equipment/weapon/weaponsList.h"

class Game
{
private:
    Window m_window;

private:
    sf::Clock clock;
    float deltaTime;

protected:
    Player player{ {50.0f, 100.0f }, sf::Color(222, 125, 70) , {0.0f, 0.0f}, 100, 100 };
    HUD hud;
    View view{ player.getPosition(), m_window.GetWindow()->getSize()};

public:
    Game();
    ~Game();

public:
    Window* GetWindow();
    Player* GetPlayer();

public:
    void Update();
    void UpdateHUD();
    void UpdateView(float deltaTime);
    void Render();
};

#endif