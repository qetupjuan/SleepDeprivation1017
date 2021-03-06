#include "Game.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include "glm/gtx/string_cast.hpp"
#include "IMGUI_SDL/imgui_sdl.h"


Game* Game::s_pInstance = nullptr;

// Game functions - DO NOT REMOVE ***********************************************

Game::Game() :
	m_pWindow(nullptr), m_pRenderer(nullptr), m_currentFrame(0), m_bRunning(true), m_frames(0), m_currentScene(nullptr), m_currentSceneState(NO_SCENE), m_volume(64)
{
	srand(unsigned(time(nullptr)));  // random seed
}

Game::~Game()
= default;


bool Game::init(const char* title, const int x, const int y, const int width, const int height, const bool fullscreen)
{

	auto flags = 0;

	TotalScores.clear();
	TotalScores.push_back(0.0);
	TotalScores.push_back(0.0);

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		//m_pWindow = SDL_CreateWindow(title, x, y, width, height, flags);
		m_pWindow = (Config::make_resource(SDL_CreateWindow(title, x, y, width, height, flags)));

		
		
		// if window creation successful create our renderer
		if (m_pWindow != nullptr)
		{
			std::cout << "window creation success" << std::endl;
			//m_pRenderer = SDL_CreateRenderer(m_pWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			m_pRenderer = (Config::make_resource(SDL_CreateRenderer(m_pWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)));

			if (m_pRenderer != nullptr) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer.get(), 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			// IMGUI 
			ImGui::CreateContext();
			ImGuiSDL::Initialize(m_pRenderer.get(), width, height);
			Mix_AllocateChannels(10);

			// Initialize Font Support
			if (TTF_Init() == -1)
			{
				printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				return false;
			}

			start();

		}
		else 
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}

	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::start()
{
	SoundManager::Instance()->load("../Assets/audio/permanentSleep.wav", "bg_music", SOUND_MUSIC);
	SoundManager::Instance()->playMusic("bg_music", -1);

	m_currentSceneState = SceneState::NO_SCENE;

	changeSceneState(SceneState::START_SCENE);
}

void Game::setScores()
{
}

SDL_Renderer * Game::getRenderer() const
{
	return m_pRenderer.get();
}

glm::vec2 Game::getMousePosition() const
{
	return m_mousePosition;
}

bool Game::getPause()
{
	return paused;
}

glm::vec2 Game::GetScores()
{
	return glm::vec2 (TotalScores[0], TotalScores[1]);
}


void Game::setVolume(int vol)
{
	if (((m_volume + vol) >= 0) && ((m_volume + vol) <= 128))
	{
		m_volume += vol;
	}
}

void Game::setFrames(const Uint32 frames)
{
	m_frames = frames;
}

Uint32 Game::getFrames() const
{
	return m_frames;
}

void Game::setPause(bool choice)
{
	paused = choice;
}

void Game::setHighestScore(double score)
{
	if (TotalScores[1] < score)
	{
		TotalScores[1] = score;
	}
}

void Game::changeSceneState(const SceneState new_state)
{
	if (new_state != m_currentSceneState) {

		// scene clean up
		if (m_currentSceneState != SceneState::NO_SCENE) 
		{
			m_currentScene->clean();
			std::cout << "cleaning previous scene" << std::endl;
			FontManager::Instance()->clean();
			std::cout << "cleaning FontManager" << std::endl;
			TextureManager::Instance()->clean();
			std::cout << "cleaning TextureManager" << std::endl;
		}
		// clean up more
		//delete m_currentScene;
		m_currentScene = nullptr;

		m_currentSceneState = new_state;
		
		switch (m_currentSceneState)
		{
		case SceneState::START_SCENE:
			TotalScores[0] = 0.0;
			m_currentScene = new StartScene();
			std::cout << "start scene activated" << std::endl;
			break;
		case SceneState::LEVEL1_SCENE:
			TotalScores[0] = 0.0;
			m_currentScene = new Level1Scene();
			std::cout << "Level 1 scene activated" << std::endl;
			break;
		case SceneState::LOSE_SCENE:
			m_currentScene = new EndScene('l');
			std::cout << "losing :(" << std::endl;
			break;
		case SceneState::WIN_SCENE:
			m_currentScene = new EndScene('w');
			std::cout << "willing :D" << std::endl;
			break;
		default:
			std::cout << "default case activated" << std::endl;
			break;
		}
	}
	
}

void Game::quit()
{
	m_bRunning = false;
}

void Game::render() const
{
	SDL_RenderClear(m_pRenderer.get()); // clear the renderer to the draw colour

	m_currentScene->draw();

	SDL_RenderPresent(m_pRenderer.get()); // draw to the screen


}

void Game::update()
{
	if (startCount)
	{
		TotalScores[0] += deltaTime;
	}
	Mix_Volume(-1, m_volume);
	setHighestScore(TotalScores[0]);
	if (m_currentSceneState == LEVEL1_SCENE)
	{
		startCount = true;
	}
	else
	{
		startCount = false;
		//ScoreBoardManager::Instance()->showHigh(true);
	}
	m_currentScene->update();
}

void Game::clean() const
{
	std::cout << "cleaning game" << std::endl;

	// Clean Up for ImGui
	ImGui::DestroyContext();

	TTF_Quit();

	SDL_Quit();
}

void Game::handleEvents()
{
	m_currentScene->handleEvents();

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) 
			{
				case SDLK_ESCAPE:
					m_bRunning = false;
					break;
				case SDLK_y:
					if (m_volume >= 4)
					{
						m_volume -= 4;
					}
					break;
				case SDLK_u:
					if (m_volume <= 124)
					{
						m_volume += 4;
					}
					break;
			}
			break;
		default:
			break;
		}
	}
}