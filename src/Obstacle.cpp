#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle()
{
}

Obstacle::Obstacle(char type) : rotation(0.0)
{

	//Notations:
	/*
	d = disk
	t = stick
	p = spike
	b = big spike
	h = hands
	*/


	switch (type)
	{
	case 'd':
		TheTextureManager::Instance()->load("../Assets/sprites/disk.png", "d", Game::Instance()->getRenderer());
		setHeight(128);
		setWidth(128);
		setPosition(rand() % 600 + 800, 500);
		setIsColliding(false);
		setType(OBSTACLE);
		isRotating = true;
		frameNumber = 1;
		ObsName = "d";
		break;
	case 't':
		TheTextureManager::Instance()->load("../Assets/sprites/stick.png", "t", Game::Instance()->getRenderer());
		setHeight(448);
		setWidth(128);
		setPosition(rand() % 1600 + 800, 150);
		setIsColliding(false);
		setType(OBSTACLE);
		frameNumber = 1;
		ObsName = "t";
		break;
	case 'p':
		TheTextureManager::Instance()->load("../Assets/sprites/spikes.png", "p", Game::Instance()->getRenderer());
		setHeight(64);
		setWidth(128);
		setPosition(rand() % 400 + 1600, 468);
		setIsColliding(false);
		setType(OBSTACLE);
		frameNumber = 1;
		ObsName = "p";
		break;
	case 'b':
		TheTextureManager::Instance()->load("../Assets/sprites/sickSpike.png", "b", Game::Instance()->getRenderer());
		setHeight(128);
		setWidth(64);
		setPosition(rand() % 800 + 1600, 64);
		setIsColliding(false);
		setType(OBSTACLE);
		frameNumber = 1;
		ObsName = "b";
		break;
	case 'h':
		TheTextureManager::Instance()->load("../Assets/sprites/sickHands.png", "h", Game::Instance()->getRenderer());
		setHeight(64);
		setWidth(64);
		setPosition(rand() % 600 + 800, 468);
		setIsColliding(false);
		setType(OBSTACLE);
		frameNumber = 6;
		ObsName = "h";
		break;
	}

	setType(OBSTACLE);
}

Obstacle::~Obstacle() = default;

void Obstacle::draw()
{
	TheTextureManager::Instance()->drawFrame(ObsName, getPosition().x, getPosition().y, getWidth(), getHeight(), m_currentRow, m_currentFrame, frameNumber, 1, 0.5f, Game::Instance()->getRenderer(), rotation, 255, true, SDL_FLIP_NONE);

}

void Obstacle::update()
{
	checkBoundary();

	if (isRotating)
	{
		if (rotation > 720)
		{
			rotation = 0.0;
		}

		rotation += 200.0 * (1.0 / 60.0);
	}

	setPosition(glm::vec2(getPosition().x - time * 100, getPosition().y));
}

void Obstacle::clean()
{
}

void Obstacle::checkBoundary()
{
	if (getPosition().x < (0 - (getWidth() / 2)))
	{
		int randomNumber = rand() % 600 + 800;
		std::cout << "Randon Number is: " << randomNumber << std::endl;

		setPosition(randomNumber, getPosition().y);
	}
}
