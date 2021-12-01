#pragma once
#ifndef __OBSTACLES__
#define __OBSTACLES__

#include "DisplayObject.h"


class Obstacle : public DisplayObject
{
public:
	Obstacle();
	Obstacle(char type);
	~Obstacle();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	double rotation, speed;
	float time = 1.0 / 60;
	int m_currentFrame, m_currentRow, frameNumber;
	bool isRotating = false;
	std::string ObsName;

	void checkBoundary();
};



#endif // !__OBSTACLES__