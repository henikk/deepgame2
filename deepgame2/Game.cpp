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
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	u16 viewRange = this->player.getWeaponViewRange();

	mousePos.x = map(mousePos.x, 0, 1600, -(viewRange) / 2.0f, viewRange / 2.0f) - this->m_window.GetWindow()->getPosition().x;
	mousePos.y = map(mousePos.y, 0, 800, -(viewRange * (16 / 9)) / 2.0f, (viewRange * (16 / 9))) / 2.0f - this->m_window.GetWindow()->getPosition().y;

	this->view.update(sf::Vector2f(mousePos.x + this->player.getPosition().x / 2 + player.getSize().x / 2,
		mousePos.y + this->player.getPosition().y / 2 + player.getSize().y / 2), deltaTime);
	this->m_window.GetWindow()->setView(this->view.getView());
}

