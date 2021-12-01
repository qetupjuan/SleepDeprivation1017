#include "Bullet.h"
#include "TextureManager.h"
#include "Game.h"

Bullet::Bullet():m_isActive(true)
{
	TextureManager::Instance()->load("../Assets/sprites/pbullet.png", "pbullet", Game::Instance()->getRenderer());

	setWidth(32);
	setHeight(32);
	setIsColliding(false);
	setType(P_BULLET);
	//setVelocity(glm::vec2(0.0f, -100.0f));
}

Bullet::~Bullet() = default;

void Bullet::draw()
{
	//if (m_isActive)
		TextureManager::Instance()->draw("pbullet", getPosition().x, getPosition().y, Game::Instance()->getRenderer(), true);
}

void Bullet::update()
{
	auto x = getPosition().x;
	auto y = getPosition().y - 10;// 00 * deltaTime;
	setPosition(glm::vec2(x, y));
	checkBound();
}

void Bullet::clean()
{
}

void Bullet::reset()
{
	setPosition(-1000.0f, -1000.0f);
	m_isActive = false;
}

bool Bullet::isActive()
{
	return m_isActive;
}

void Bullet::setActive()
{
	m_isActive = true;
}

void Bullet::checkBound()
{
	if ((getPosition().y < 0) || (getPosition().y > 600))
	{
		reset();
	}
}
