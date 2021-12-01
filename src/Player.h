#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "DisplayObject.h"
#include "PlayerAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>

class Player : public DisplayObject
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void setAnimation(const Animation& animation);
	void setMotion(int speed, const char dir);
	void setDamage(int damage);

	PlayerAnimationState getAnimState();

private:
	void m_buildAnimations();
	void jump();
	bool jumping = false;

	SpriteSheet* m_pSpriteSheet;

	int m_currentFrame, m_currentRow, speed, health = 100;
	float deltaTime = 1.0f / 60;
	float jumpTimer = 0.0f;

	double gravity = 7.0;

	glm::vec2 MaxVelocity = glm::vec2(20.0, 50.0);

	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
};

#endif /* defined (__PLAYER__) */