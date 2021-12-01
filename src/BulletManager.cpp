#include "BulletManager.h"

BulletManager* BulletManager::s_pInstance = nullptr;

Bullet* BulletManager::getBullet()
{
	const auto bullet = m_bulletPool.front();
	bullet->setActive();
	m_bulletPool.pop_front();
	m_bulletPool.push_back(bullet);
	return bullet;
}

EBullet* BulletManager::getEBullet()
{
	const auto bullet_e = m_bulletPool_e.front();
	bullet_e->setActive();
	m_bulletPool_e.pop_front();
	m_bulletPool_e.push_back(bullet_e);
	return bullet_e;
}

std::list<Bullet*> BulletManager::getPlayerBullets()
{
	return m_bulletPool;
}

std::list<EBullet*> BulletManager::getEnemyBullets()
{
	return m_bulletPool_e;
}

void BulletManager::update()
{
	for (auto bullet : m_bulletPool)
	{
		if (bullet->isActive())
		{
			bullet->update();
		}
	}
	for (auto ebullet : m_bulletPool_e)
	{
		if (ebullet->isActive())
		{
			ebullet->update();
		}
	}
}

void BulletManager::draw()
{
	for (auto bullet : m_bulletPool)
	{
		if (bullet->isActive())
		{
			bullet->draw();
		}
	}
	for (auto bullet_e : m_bulletPool_e)
	{
		if (bullet_e->isActive())
		{
			bullet_e->draw();
		}
	}
}

BulletManager::BulletManager():m_bulletNum(50), m_bulletNum_e(60)
{
	m_buildBullets();
}

BulletManager::~BulletManager() = default;

void BulletManager::m_buildBullets()
{
	m_bulletPool = std::list<Bullet*>();
	m_bulletPool_e = std::list<EBullet*>();

	for (int n = 0; n < m_bulletNum; ++n)
	{
		m_bulletPool.push_back(new Bullet());
	}

	for (int n = 0; n < m_bulletNum_e; ++n)
	{
		m_bulletPool_e.push_back(new EBullet());
	}
	//Build enemy bullet _e
}
