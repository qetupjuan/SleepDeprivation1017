#include "EBullet.h"
#include "TextureManager.h"
#include "Game.h"

EBullet::EBullet():m_isActive(true)
{
	TextureManager::Instance()->load("../Assets/sprites/ebullet.png", "ebullet", Game::Instance()->getRenderer());

	setWidth(32);
	setHeight(32);
	setIsColliding(false);
	setType(E_BULLET);
}

EBullet::~EBullet() = default;

void EBullet::draw()
{
	TextureManager::Instance()->draw("ebullet", getPosition().x, getPosition().y, Game::Instance()->getRenderer(), true);
}

void EBullet::update()
{
	auto x = getPosition().x;
	auto y = getPosition().y + 10;// 00 * deltaTime;
	setPosition(glm::vec2(x, y));
	checkBound();
}

void EBullet::clean()
{
}

void EBullet::reset()
{
	setPosition(-1000.0f, -1000.0f);
	m_isActive = false;
}

bool EBullet::isActive()
{
	return m_isActive;
}

void EBullet::setActive()
{
	m_isActive = true;
}

void EBullet::checkBound()
{
	if ((getPosition().y < 0) || (getPosition().y > 600))
	{
		reset();
	}
}
