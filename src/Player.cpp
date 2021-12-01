#include "Player.h"
#include <algorithm>
#include "Game.h"

Player::Player(): m_currentAnimationState(NOTHING), m_currentFrame(0), m_currentRow(0)
{
	/*TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");
	*/

	TheTextureManager::Instance()->load("../Assets/sprites/player_run.png", "p_run", Game::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/sprites/player_roll.png", "p_roll", Game::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/sprites/player_jump.png", "p_jump", Game::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/sprites/player_dead.png", "p_dead", Game::Instance()->getRenderer());
	TheTextureManager::Instance()->load("../Assets/sprites/player_tomb.png", "p_tomb", Game::Instance()->getRenderer());

	// set frame width
	setWidth(64);

	// set frame height
	setHeight(128);

	setPosition(glm::vec2(400.0f, 436.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(PLAYER);

	//m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	switch(m_currentAnimationState)
	{
	case LEFTING:
		TheTextureManager::Instance()->drawFrame("p_run", getPosition().x, getPosition().y, 128, 128, m_currentRow, m_currentFrame, 8, 1, 0.5f, Game::Instance()->getRenderer(), 0.0, 255, true, SDL_FLIP_NONE);
		break;
	/*case RIGHTING:
		TheTextureManager::Instance()->drawFrame("p_run", getPosition().x, getPosition().y, getWidth(), getHeight(), m_currentRow, m_currentFrame, 8, 1, 0.5f, Game::Instance()->getRenderer(), 0.0, 255, true, SDL_FLIP_NONE);
		break;
	case JUMP_RIGHT:
		TheTextureManager::Instance()->draw("p_jump", getPosition().x, getPosition().y, Game::Instance()->getRenderer(), true, SDL_FLIP_NONE);
		break;*/
	case JUMP_LEFT:
		TheTextureManager::Instance()->draw("p_jump", getPosition().x -32, getPosition().y - 64, 64, 128, Game::Instance()->getRenderer(), 0.0, 255, SDL_FLIP_NONE);
		break;
	case ROLL:
		TheTextureManager::Instance()->drawFrame("p_roll", getPosition().x, getPosition().y + 32, 64, 64, m_currentRow, m_currentFrame, 4, 1, 0.5f, Game::Instance()->getRenderer(), 0.0, 255, true, SDL_FLIP_NONE);
		break;
	case DEAD:
		TheTextureManager::Instance()->drawFrame("p_dead", getPosition().x, getPosition().y, 128, 128, m_currentRow, m_currentFrame, 6, 1, 0.5f, Game::Instance()->getRenderer(), 0.0, 255, true, SDL_FLIP_NONE);
		if (m_currentFrame >= 5)
		{
			setAnimationState(TOMB);
		}
		break;
	case TOMB:
		TheTextureManager::Instance()->draw("p_tomb", getPosition().x, getPosition().y, Game::Instance()->getRenderer(), true, SDL_FLIP_NONE);
		break;
	}
	
	
	
}

void Player::update()
{
	if (m_currentAnimationState == ROLL)
	{
		setHeight(64);
		setWidth(64);
	}
	else
	{
		setHeight(128);
		setWidth(64);
	}

	if (jumpTimer > 0.0f)
	{
		jumpTimer -= deltaTime;
	}

	if (jumping)
	{
		jump();
	}

	float xVel = getVelocity().x;
	float yVel = getVelocity().y;

	xVel += getAcceleration().x;
	yVel += getAcceleration().y + gravity;

	//xVel *= (jumping ? 0.75 : 1);

	if ((getPosition().x > 0.0f) && (getPosition().x < 700.0f))
	{
		xVel = std::min(std::max(xVel, -(MaxVelocity.x)), (MaxVelocity.x));
		setPosition(glm::vec2(getPosition().x + xVel, getPosition().y));
	}

	if ((getPosition().y <= 436.0) && (getPosition().y > 32.0))
	{
		if (getAcceleration().y != 0.0)
		{
			yVel = std::min(std::max(yVel, -(MaxVelocity.y)), 20.0f);
			setPosition(glm::vec2(getPosition().x, getPosition().y + yVel));
			setAcceleration(glm::vec2(getAcceleration().x, getAcceleration().y + (gravity / 30.0)));
		}
		else
		{
			if (getPosition().y != 436.0)
			{
				yVel = std::min(std::max(yVel, -(MaxVelocity.y)), 20.0f);
				setPosition(glm::vec2(getPosition().x, getPosition().y + yVel));
			}
		}
	}
	else if (getPosition().y > 436.0)
	{
		setAcceleration(glm::vec2 (0.0, 0.0));
		setPosition(glm::vec2 (getPosition().x, 436.0));
	}

	setAcceleration(glm::vec2(0.0, getAcceleration().y));

	//setAcceleration(glm::vec2 (0.0, 0.0));

}

void Player::clean()
{
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;
}

void Player::setMotion(int speed, const char dir)
{
	switch (dir)
	{
	case ('x'):
		setPosition(glm::vec2(getPosition().x + speed * deltaTime, getPosition().y));
		break;
	case ('y'):
		if (speed == 1)
		{
			if (!jumping)
			{
				jumping = true;
				jumpTimer = 0.25f;
			}
		}

		break;
	}
}

void Player::setDamage(int damage)
{
	if (health > 0)
	{
		health -= damage;
	}
	else
	{
		setPosition(glm::vec2(1000.0f, 1000.0f));
		setVelocity(glm::vec2(0.0f, 0.0f));

	}
}

PlayerAnimationState Player::getAnimState()
{
	return m_currentAnimationState;
}


void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-3"));

	m_pAnimations["idle"] = idleAnimation;

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-3"));

	m_pAnimations["run"] = runAnimation;
}

void Player::jump()
{
	if (jumping)
	{
		if (jumpTimer > 0.0f)
		{
			setPosition(glm::vec2(getPosition().x, getPosition().y - 800.0f * deltaTime));
		}
		else
		{
			if (getPosition().y < 435)
			{
				setPosition(glm::vec2(getPosition().x, getPosition().y + 650.0f * deltaTime));
			}
			else
			{
				setPosition(getPosition().x, getPosition().y);
				jumping = false;
			}
		}
	}
}
