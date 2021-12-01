#include "EndScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "ScoreBoardManager.h"

EndScene::EndScene()
{
	EndScene::start();
}

EndScene::EndScene(const char option)
{
	switch (option)
	{
	case 'l':
		outcome = "lose";
		break;
	case 'w':
		outcome = "win";
		break;
	default:
		outcome = "";
		break;
	}
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	TextureManager::Instance()->draw(outcome, 400, 300, Game::Instance()->getRenderer(), true, SDL_FLIP_NONE);
	drawDisplayList();
	//m_label->draw();
	ScoreBoardManager::Instance()->Draw();
}

void EndScene::update()
{
	updateDisplayList();
	glm::vec2 Scores = Game::Instance()->GetScores();
	ScoreBoardManager::Instance()->setScore(Scores.x);
	ScoreBoardManager::Instance()->setHS(Scores.y);
}

void EndScene::clean()
{
	//delete m_label;
	removeAllChildren();
}

void EndScene::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (m_MainMenu != nullptr)
		{
			m_MainMenu->handleMouseEvents(&event);
			m_Quit->handleMouseEvents(&event);
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

void EndScene::start()
{
	TextureManager::Instance()->load("../Assets/sprites/winState.png", "win", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("../Assets/sprites/loseState.png", "lose", Game::Instance()->getRenderer());

	m_MainMenu = new Button("../Assets/sprites/main.png", "mainMenu", MAIN_MENU_BOTTON);
	m_MainMenu->setPosition(400.0f, 400.0f);
	m_MainMenu->setAlpha(200);
	m_MainMenu->addEventListener(CLICK, [](Button* button)-> void
		{
			button->setActive(false);
			TheGame::Instance()->changeSceneState(START_SCENE);
		});

	m_MainMenu->addEventListener(MOUSE_OVER, [](Button* button)->void
		{
			button->setAlpha(255);
		});

	m_MainMenu->addEventListener(MOUSE_OUT, [](Button* button)->void
		{
			button->setAlpha(200);
		});
	addChild(m_MainMenu);

	m_Quit = new Button("../Assets/sprites/quit.png", "quitButton", QUIT_BOTTON);
	m_Quit->setPosition(400.0f, 500.0f);
	m_Quit->setAlpha(200);
	m_Quit->addEventListener(CLICK, [](Button* button)-> void
		{
			button->setActive(false);
			TheGame::Instance()->quit();
			//TheGame::Instance()->changeSceneState(LEVEL1_SCENE);
		});

	m_Quit->addEventListener(MOUSE_OVER, [](Button* button)->void
		{
			button->setAlpha(255);
		});

	m_Quit->addEventListener(MOUSE_OUT, [](Button* button)->void
		{
			button->setAlpha(200);
		});
	addChild(m_Quit);

	/*const SDL_Color blue = { 0, 0, 255, 255 };
	m_label = new Label("END SCENE", "Dock51", 80, blue, glm::vec2(400.0f, 40.0f));
	m_label->setParent(this);
	addChild(m_label);*/
}
