#include "ship.h"
#include "Game.h"
#include "Util.h"
#include "glm/gtx/string_cast.hpp"


Ship::Ship() : m_maxSpeed(10.0f)
{
	TheTextureManager::Instance()->load("../Assets/sprites/enemy.png", "enemy", Game::Instance()->getRenderer());

	setWidth(64);
	setHeight(64);
	setPosition(glm::vec2(400.0f, 50.0f));
	setVelocity(glm::vec2(4, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	//m_reset();
	setIsColliding(false);
	setType(GameObjectType::ENEMY);
	setState(IDLE);
	
	m_currentHeading = 0.0f; // current facing angle
	m_currentDirection = glm::vec2(1.0f, 0.0f); // facing right
	m_turnRate = 5.0f; // 5 degrees per frame
}


Ship::~Ship()
{}

void Ship::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("enemy", xComponent, yComponent,
		Game::Instance()->getRenderer(), true);
}


void Ship::update()
{
	if (health > 0)
	{
		move();
		m_checkBounds();
	}
	
}

void Ship::clean()
{
}

void Ship::turnRight()
{
	m_currentHeading += m_turnRate;
	if (m_currentHeading >= 360) 
	{
		m_currentHeading -= 360.0f;
	}
	m_changeDirection();
}

void Ship::turnLeft()
{
	m_currentHeading -= m_turnRate;
	if (m_currentHeading < 0)
	{
		m_currentHeading += 360.0f;
	}

	m_changeDirection();
}

void Ship::moveForward()
{
	setVelocity(m_currentDirection * m_maxSpeed);
}

void Ship::moveBack()
{
	setVelocity(m_currentDirection * -m_maxSpeed);
}

void Ship::move()
{
	glm::vec2 newPosition = getPosition() + getVelocity();
	setPosition(newPosition);
}

glm::vec2 Ship::getTargetPosition()
{
	return m_targetPosition;
}

glm::vec2 Ship::getCurrentDirection()
{
	return m_currentDirection;
}

float Ship::getMaxSpeed()
{
	return m_maxSpeed;
}

void Ship::setTargetPosition(glm::vec2 newPosition)
{
	m_targetPosition = newPosition;

}

void Ship::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

void Ship::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}

void Ship::setDamage(int damage)
{
	if (health > 0)
	{
		health -= damage;
	}
	else
	{
		setPosition(glm::vec2(1000.0f, 1000.0f));
		setVelocity(glm::vec2(0.0f, 0.0f));
	}
}


void Ship::m_checkBounds()
{

	if (getPosition().x > 768) {
		setVelocity(glm::vec2(-4, 0));
	}
	if (getPosition().x < getWidth() / 2) {
		setVelocity(glm::vec2(4, 0));
	}
}

void Ship::m_reset()
{
	setIsColliding(false);
	int halfWidth = getWidth() * 0.5f;
	int xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	int yComponent = -getHeight();
	setPosition(glm::vec2(xComponent, yComponent));
}

void Ship::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("enemy");
}

