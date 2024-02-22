#include "Game.h"

Game::Game() : deltaTime(0.0f), scopeFrom(0.90f)
{
	this->m_window.GetWindow()->setView(view.getView());
	this->initialScopeFrom = this->scopeFrom;

	// Set default mouse position
	sf::Mouse::setPosition(sf::Vector2i(this->m_window.GetWindow()->getSize().x / 2,
		this->m_window.GetWindow()->getSize().y / 2), *this->m_window.GetWindow());
}

Game::~Game() {}

Window* Game::GetWindow()
{
	return &this->m_window;
}

Player* Game::GetPlayer()
{
	return &this->player;
}

void Game::Update()
{
	this->deltaTime = this->clock.restart().asSeconds();

	this->m_window.update();

	if (this->player.isAlive())
		this->player.update(this->m_window.GetWindow(), this->deltaTime);

	this->UpdateHUD();
	this->UpdateView(this->deltaTime);
}

void Game::UpdateHUD()
{
	this->hud.m_hp.setPlayerHp(this->player.getHp());
	this->hud.m_hp.setPlayerArmor(this->player.getArmor());
	this->hud.update(this->m_window.GetWindow(), view.getView().getCenter());
}

void Game::Render()
{
	this->m_window.BeginDraw();
	this->m_window.drawBackground();

	if (player.isAlive())
		this->player.render(this->m_window.GetWindow());

	//this->hud.render(this->m_window.GetWindow());

	this->m_window.EndDraw();
}

void Game::UpdateView(float deltaTime)
{
	u16 viewRange = this->player.getWeaponViewRange();
	sf::Vector2i mousePos = sf::Mouse::getPosition() - this->m_window.GetWindow()->getPosition();
	sf::Vector2u windowSize = this->m_window.GetWindow()->getSize();

	// If mouse out of the window border
	if (mousePos.x >= 0 && mousePos.x <= windowSize.x && mousePos.y >= 0 && mousePos.y <= windowSize.y)
	{
		// If mouse out of the viewRange
		if (mousePos.x >= windowSize.x * this->scopeFrom ||
			mousePos.x <= windowSize.x * (1.0f - this->scopeFrom) ||
			mousePos.y >= windowSize.y * this->scopeFrom ||
			mousePos.y <= windowSize.y * (1.0f - this->scopeFrom) ||
			sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			this->scopeFrom = 0.55f;

			mousePos.x = map(mousePos.x, 0, this->m_window.GetWindow()->getSize().x, -(viewRange) / 2.0f, viewRange / 2.0f);
			mousePos.y = map(mousePos.y, 0, this->m_window.GetWindow()->getSize().y, -(viewRange * (16 / 9)) / 2.0f, (viewRange * (16 / 9)) / 2.0f);
			
			this->view.update(sf::Vector2f(mousePos.x + this->player.getPosition().x + this->player.getSize().x / 2.0f,
				mousePos.y + this->player.getPosition().y + this->player.getSize().y / 2.0f), deltaTime);
		}
		else
		{
			this->scopeFrom = this->initialScopeFrom;

			this->view.update(sf::Vector2f(this->player.getPosition().x + this->player.getSize().x / 2.0f,
				this->player.getPosition().y + this->player.getSize().y / 2.0f), deltaTime);
		}
	}
	else
	{
		this->view.update(sf::Vector2f(this->player.getPosition().x + this->player.getSize().x / 2.0f,
			this->player.getPosition().y + this->player.getSize().y / 2.0f), deltaTime);
	}
	
	this->m_window.GetWindow()->setView(this->view.getView());
}