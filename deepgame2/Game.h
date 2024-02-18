#ifndef GAME_H
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
    float initialScopeFrom;
    float scopeFrom; // From which coords camera will follow cursor. Variable must be initialized as percent from window size - [0.8f (80%)]

private:
    sf::Clock clock;
    float deltaTime;

    // [TEMP]
    int map(double value, double fromLow, double fromHigh, double toLow, double toHigh)
    {
        return round((value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow);
    }

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
