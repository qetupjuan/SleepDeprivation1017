#pragma once
#ifndef __BULLET__
#define __BULLET__

#include "DisplayObject.h"

class Bullet : public DisplayObject
{
public:
	Bullet();
	~Bullet();

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

#endif // !__BULLET__