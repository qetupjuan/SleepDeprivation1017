#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "DisplayObject.h"

class BG : public DisplayObject
{
public:
	BG();
	~BG();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	glm::vec2 checkBoundary(glm::vec2 Pos);
	float time = 1.0 / 60;
	bool Gameplay_BG = true;

	glm::vec2 back_bgPOS, tree_bgPOS;
};

#endif // !__BACKGROUND__