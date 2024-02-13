#include "Game.h"

Game::Game()
{
	this->m_window.GetWindow()->setView(view.getView());
}

Game::~Game()
{
 
}

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
	this->view.update(sf::Vector2f(player.getPosition().x + player.getSize().x / 2,
		player.getPosition().y + player.getSize().y / 2), deltaTime);
	this->m_window.GetWindow()->setView(view.getView());
}

