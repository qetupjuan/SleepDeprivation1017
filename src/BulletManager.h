#pragma once
#ifndef __BULLET_MANAGER__
#define __BULLET_MANAGER__

#include <list>
#include "Bullet.h"
#include "EBullet.h"

class BulletManager
{
public:
	static BulletManager* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new BulletManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	//Getters baby
	Bullet* getBullet();
	EBullet* getEBullet();
	std::list<Bullet*> getPlayerBullets();
	std::list<EBullet*> getEnemyBullets();

	void update();
	void draw();

	void m_buildBullets();

private:
	BulletManager();
	~BulletManager();



	//Player Bullet craps

	int m_bulletNum;
	std::list<Bullet*> m_bulletPool;
	static BulletManager* s_pInstance;

	//Enemy Bullet craps
	int m_bulletNum_e;
	std::list<EBullet*> m_bulletPool_e;
	static BulletManager* s_pInstance_e;
};


#endif // !__BULLET_MANAGER__