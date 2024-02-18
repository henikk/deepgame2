#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Texture* _texture, sf::Vector2f _initialPostition, u16 _speed, u8 _damage, float _angle, float _range)
	: m_texture(*_texture), m_initialPosition(_initialPostition), m_speed(_speed), m_damage(_damage), m_angle(_angle), m_range(_range), m_isAlive(true)
{
	_texture->setSmooth(true);
	this->m_body.setTexture(*_texture);
	this->m_body.setScale(sf::Vector2f(2.65f, 0.35f));
	this->m_body.setColor(sf::Color::Yellow);
	this->m_body.setOrigin(sf::Vector2f(0.0f, this->m_texture.getSize().y / 2));
	this->m_body.setPosition(this->m_initialPosition);
	this->m_body.setRotation(this->m_angle);
}

Bullet::~Bullet()
{}

void Bullet::update(float deltaTime)
{
	if (this->m_isAlive)
	{
		float radians = this->m_angle * (3.14f / 180.0f);

		this->m_velocity = sf::Vector2f(this->m_speed * std::cos(radians), this->m_speed * std::sin(radians));
		this->m_body.move(this->m_velocity * deltaTime);

		killIfOutRange();
	}
}

void Bullet::render(sf::RenderWindow* target) const
{
	if (this->m_isAlive)
		target->draw(this->m_body);
}

void Bullet::killIfOutRange() {
	if (this->m_body.getPosition().x >= this->m_initialPosition.x + this->m_range ||
		this->m_body.getPosition().y <= this->m_initialPosition.y - this->m_range ||
		this->m_body.getPosition().x <= this->m_initialPosition.x - this->m_range ||
		this->m_body.getPosition().y >= this->m_initialPosition.y + this->m_range)
	{
		this->kill();
	}
}