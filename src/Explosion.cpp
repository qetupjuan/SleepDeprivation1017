#include "Explosion.h"
#include "Game.h"
#include <utility>

Explosion::Explosion() : m_currentRow(0), m_currentFrame(0), m_bIsActive(false)
{
	/*TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");*/

	TextureManager::Instance()->load("../Assets/sprites/sickExplosion.png", "expl", Game::Instance()->getRenderer());


	// set frame width
	setWidth(96);

	// set frame height
	setHeight(96);

	setIsColliding(false);
	setType(EXPLOSION);

	//m_buildAnimations();

	//reset();
}

Explosion::~Explosion()
= default;

void Explosion::draw()
{
	//if(m_currentFrame == 0)
	//{
		/*TheTextureManager::Instance()->playAnimation(
			"spritesheet", m_pAnimations["explosion"],
			getPosition().x, getPosition().y, m_currentFrame, 0.5f,
			TheGame::Instance()->getRenderer(), 0, 255, true);*/
	//}
	//else
	//{
		//reset();
	//}

	if (m_currentFrame < 5)
	{
		TextureManager::Instance()->drawFrame("expl", getPosition().x, getPosition().y, getWidth(), getHeight(), m_currentRow, m_currentFrame, 6, 1, 0.75f, Game::Instance()->getRenderer(), 0.0, 255, true, SDL_FLIP_VERTICAL);
	}
	else
	{
		reset();
	}
	
}

void Explosion::update()
{
}

void Explosion::clean()
{
}

void Explosion::reset()
{
	setPosition(-1000.0f, -1000.0f);
	m_currentFrame = 0;
	m_bIsActive = false;
}

bool Explosion::isActive()
{
	return m_bIsActive;
}

void Explosion::setActive()
{
	m_currentFrame = 0;
	m_bIsActive = true;
}

void Explosion::m_buildAnimations()
{
	Animation explosionAnimation = Animation();

	explosionAnimation.name = "explosion";
	explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("explosion1"));
	explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("explosion2"));
	explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("explosion3"));
	explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("explosion4"));
	explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("explosion5"));
	explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("explosion6"));
	explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("explosion7"));

	m_pAnimations["explosion"] = explosionAnimation;
}
