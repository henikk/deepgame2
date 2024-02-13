#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

#include "types.h"

class Window
{
private:
	sf::VideoMode m_videoMode;
	sf::Event m_event;
	sf::RenderWindow* m_window;
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	
private:
	u8 m_fpsLimit;
	std::string m_title;
	//sf::Cursor m_cursor;

public:
	Window();
	~Window();

public:
	void initWindow();
	void destroyWindow();

public:
	inline const bool isRunning() const { return m_window->isOpen(); }
	void pollEvents();

	void update();

public:
	void BeginDraw();
	void EndDraw();
	void drawBackground();

public:
	inline sf::RenderWindow* GetWindow() const { return this->m_window; }
};

#endif