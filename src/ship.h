#pragma once
#ifndef __SHIP__
#define __SHIP__

#include "PathFindingDisplayObject.h"
#include "TextureManager.h"

class Ship final : public PathFindingDisplayObject
{
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void turnRight();
	void turnLeft();
	void moveForward();
	void moveBack();
	
	void move();

	// getters
	glm::vec2 getTargetPosition();
	glm::vec2 getCurrentDirection();
	float getMaxSpeed();

	// setters
	void setTargetPosition(glm::vec2 newPosition);
	void setCurrentDirection(glm::vec2 newDirection);
	void setMaxSpeed(float newSpeed);
	void setDamage(int damage);

private:
	void m_checkBounds();
	void m_reset();
	//int m_AnimationState();

	// steering behaviours n stuff
	float m_maxSpeed;
	float m_turnRate;
	float deltaTime = 1.0f / 60;
	int health = 100;

	void m_changeDirection();
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;
};


#endif /* defined (__SHIP__) */

