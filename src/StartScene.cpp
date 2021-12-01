#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "ScoreBoardManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	TextureManager::Instance()->draw("title", 400, 300, Game::Instance()->getRenderer(), true, SDL_FLIP_NONE);
	drawDisplayList();
	ScoreBoardManager::Instance()->Draw();
}

void StartScene::update()
{
	updateDisplayList();
	glm::vec2 Scores = Game::Instance()->GetScores();
	ScoreBoardManager::Instance()->setScore(Scores.x);
	ScoreBoardManager::Instance()->setHS(Scores.y);
}

void StartScene::clean()
{
	std::cout << "Clean called on StartScene" << std::endl;
	
	/*delete m_pStartLabel;
	m_pStartLabel = nullptr;
	
	delete m_pInstructionsLabel;
	m_pInstructionsLabel = nullptr;

	delete m_pShip;
	m_pShip = nullptr;*/

	delete m_pStartButton;
	m_pStartButton = nullptr;

	removeAllChildren();
}

void StartScene::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if(m_pStartButton != nullptr)
		{
			m_pStartButton->handleMouseEvents(&event);
			m_pSecondStartButton->handleMouseEvents(&event);
		}
		
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				//TheGame::Instance()->changeSceneState(SceneState::WIN_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::LOSE_SCENE);
				break;
			}
			break;

		default:
			break;
		}
	}
}

void StartScene::start()
{
	TextureManager::Instance()->load("../Assets/sprites/titleState.png", "title", Game::Instance()->getRenderer());

	/*const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("START SCENE", "Consolas", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pShip = new Ship();
	m_pShip->setPosition(glm::vec2(400.0f, 300.0f));
	addChild(m_pShip);*/

	m_pStartButton = new Button("../Assets/sprites/start.png", "startButton", START_BUTTON);
	m_pStartButton->setPosition(400.0f, 400.0f);
	m_pStartButton->setAlpha(200);
	m_pStartButton->addEventListener(CLICK, [](Button* button)-> void
	{
		button->setActive(false);
		TheGame::Instance()->changeSceneState(LEVEL1_SCENE);
	});

	m_pStartButton->addEventListener(MOUSE_OVER, [](Button* button)->void
	{
		button->setAlpha(255);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [](Button* button)->void
	{
		button->setAlpha(200);
	});
	addChild(m_pStartButton);

	m_pSecondStartButton = new Button("../Assets/sprites/quit.png", "quitButton", QUIT_BOTTON);
	m_pSecondStartButton->setPosition(400.0f, 500.0f);
	m_pSecondStartButton->setAlpha(200);
	m_pSecondStartButton->addEventListener(CLICK, [](Button* button)-> void
	{
		button->setActive(false);
		TheGame::Instance()->quit();
		//TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pSecondStartButton->addEventListener(MOUSE_OVER, [](Button* button)->void
	{
		button->setAlpha(255);
	});

	m_pSecondStartButton->addEventListener(MOUSE_OUT, [](Button* button)->void
	{
		button->setAlpha(200);
	});
	
	addChild(m_pSecondStartButton);
}

