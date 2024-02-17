#include "Particle.h"

Particle::Particle(sf::Color _color, sf::Texture* _texture, sf::Vector2f _initialPosition, sf::Vector2f _initialScale, sf::Vector2f _maxScale, u8 _initialAlpha, i16 _rotationSpeed, u16 _initialSpeed, float _acceleration, float _initialAngle, float _upwardForce, float _lifeTime)
	: m_color(_color), m_texture(*_texture), m_initialPosition(_initialPosition), m_initialScale(_initialScale), m_maxScale(_maxScale), m_initialAlpha(_initialAlpha), m_rotationSpeed(_rotationSpeed), m_initialSpeed(_initialSpeed), m_speed(0.0f), m_acceleration(_acceleration), m_initialAngle(_initialAngle), m_upwardForce(_upwardForce), m_lifeTime(_lifeTime), m_isAlive(true)
{
	this->m_rotationSpeed = static_cast<float>(rand() % (this->m_rotationSpeed + 1) - static_cast<float>(this->m_rotationSpeed / 2));
	this->m_startTime = this->m_clock.getElapsedTime();

	_texture->setSmooth(true);
	this->m_body.setTexture(*_texture);
	this->m_body.setScale(this->m_initialScale);
	this->m_body.setColor(this->m_color);
	this->m_body.setOrigin({ this->m_texture.getSize().x / 2.0f, this->m_texture.getSize().y / 2.0f });
	this->m_body.setPosition(this->m_initialPosition);
	this->m_body.setRotation(rand() % 360); // Initial rotation
}

Particle::~Particle()
{}

void Particle::update(float deltaTime)
{
	if (this->m_isAlive)
	{
		this->m_elapsedTime = this->m_clock.getElapsedTime();

		this->killIfOutOfTime(this->m_lifeTime);
		this->move(deltaTime);
		this->decreaseAlpha();
		this->increaseScale();
	}
}
void Particle::render(sf::RenderWindow* target) const
{
	if (this->m_isAlive)
		target->draw(this->m_body);
}

void Particle::killIfOutOfTime(float lifeTime)
{
	if (this->m_elapsedTime.asSeconds() >= lifeTime)
		this->m_isAlive = false;
}

void Particle::move(float deltaTime)
{
	float radians = this->m_initialAngle * (3.14f / 180.0f);

	this->m_speed = sigmoidTransition(this->m_initialSpeed * 5.0f, 0.0f, this->m_elapsedTime.asSeconds(), this->m_startTime.asSeconds(), this->m_acceleration);
	this->m_velocity = sf::Vector2f(this->m_speed * std::cos(radians), this->m_speed * std::sin(radians));

	this->m_body.move(sf::Vector2f(this->m_velocity.x * deltaTime, (this->m_velocity.y - this->m_upwardForce) * deltaTime));
	this->m_body.rotate(this->m_rotationSpeed * deltaTime);

	this->increaseUpwardForce();
}

void Particle::decreaseAlpha()
{
	u8 alpha = this->m_initialAlpha * (1.0f - this->m_elapsedTime.asSeconds() / this->m_lifeTime);

	this->m_body.setColor(sf::Color(
		this->m_body.getColor().r,
		this->m_body.getColor().g,
		this->m_body.getColor().b,
		alpha
	));
}
void Particle::increaseScale()
{
	float progress = this->m_elapsedTime.asSeconds() / this->m_lifeTime;
	sf::Vector2f targetScale = this->m_maxScale * progress;
	this->m_body.setScale(this->m_initialScale + targetScale);
}
void Particle::increaseUpwardForce()
{
	float newUpwardForce = this->m_upwardForce * this->m_elapsedTime.asSeconds() / this->m_lifeTime;
	this->m_velocity.y -= newUpwardForce;
}
