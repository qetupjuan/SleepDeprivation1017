#pragma once
#ifndef __LEVEL1_SCENE__
#define __LEVEL1_SCENE__

#include "Scene.h"

#include "Player.h"
//#include "ship.h"
#include "Button.h"
#include "Obstacle.h"


class Level1Scene : public Scene
{
public:
	Level1Scene(bool paused = false);
	~Level1Scene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	bool KeyHeld(const SDL_Scancode c);
	bool KeyPressed(const SDL_Scancode c);
	bool KeyReleased(const SDL_Scancode c);
	int LastKeyDown();
	int LastKeyUp();


private:
	glm::vec2 m_mousePosition, front_bgPOS;
	float bulletTimer, enemyBulletTimer, dyingTimer, deadTimer;
	
	float deltaTime = 1.0f / 60;
	bool rolling = false, dead = false;

	const Uint8* s_keysCurr;
	Uint8* s_keysLast;
	int s_numKeys;
	int s_lastKeyDown;
	int s_lastKeyUp;

	Player* m_pPlayer;
	//Ship* m_Enemy;

	///void enemyShoot();
	///void bulletCollisionCheck();
	///void bulletClean();

	Button* m_Resume;
	Button* m_Quit;

	Obstacle* Obs1;
	Obstacle* Obs2;
	Obstacle* Obs3;
	Obstacle* Obs4;
	Obstacle* Obs5;
	std::vector<Obstacle*> ObsList;

	void CollisionCheck();

	glm::vec2 checkBoundary(glm::vec2 Pos);
};

#endif /* defined (__LEVEL1_SCENE__) */