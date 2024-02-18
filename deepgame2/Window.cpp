#include "Window.h"

Window::Window() { this->initWindow(); }
Window::~Window() { this->destroyWindow(); }

void Window::initWindow()
{
	this->m_title = "project deep";

    this->m_videoMode.width = 1600;
    this->m_videoMode.height = 900;
    this->m_fpsLimit = 60;

    this->m_window = new sf::RenderWindow(this->m_videoMode, this->m_title, sf::Style::Close);
	
    this->m_window->setFramerateLimit(this->m_fpsLimit);	
	this->m_window->setMouseCursorVisible(false);
	this->m_window->setVerticalSyncEnabled(true);

	this->m_backgroundTexture.loadFromFile("textures/backgrounds/background2.png");
	this->m_backgroundSprite.setTexture(this->m_backgroundTexture);
	this->m_backgroundSprite.setOrigin( this->m_backgroundTexture.getSize().x / 2.0f, this->m_backgroundTexture.getSize().y / 2.0f );
	this->m_backgroundSprite.setPosition({ this->m_window->getSize().x / 2.0f, this->m_window->getSize().y / 2.0f + 450.0f });
}

void Window::destroyWindow() { this->m_window->close(); }

void Window::pollEvents()
{
	while (this->m_window->pollEvent(this->m_event))
	{
		switch (this->m_event.type)
		{
		case sf::Event::Closed:
			this->destroyWindow();
			break;
		}
	}
}

void Window::update() { pollEvents(); }

void Window::BeginDraw() { this->m_window->clear(sf::Color(30, 30, 30)); }
void Window::EndDraw() { this->m_window->display(); }
void Window::drawBackground() { this->m_window->draw(this->m_backgroundSprite); }
