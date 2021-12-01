#pragma once
#ifndef __ENEMY_BULLET__
#define __ENEMY_BULLET__

#include "DisplayObject.h"

class EBullet : public DisplayObject
{
public:
	EBullet();
	~EBullet();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void reset();

	// getters and setters
	bool isActive();
	void setActive();

	void checkBound();

private:
	float deltaTime = 1.0f / 60;
	bool m_isActive;
};


#endif // !__ENEMY_BULLET__