#include "Level1Scene.h"
#include "Game.h"
#include "ExplosionManager.h"
#include "BulletManager.h"
#include "BG.h"
#include "ScoreBoardManager.h"


Level1Scene::Level1Scene(bool paused) :bulletTimer(0.25), enemyBulletTimer(0.4), dyingTimer(1/10.0), deadTimer(1.0f)
{
	Level1Scene::start();
}


Level1Scene::~Level1Scene()
= default;

void Level1Scene::draw()
{
	drawDisplayList();
	ExplosionManager::Instance()->draw();
	//BulletManager::Instance()->draw();
	if (Game::Instance()->getPause())
	{
		TextureManager::Instance()->draw("pause", -53.5, 0, 907, 600, Game::Instance()->getRenderer(), 0.0, 100);
	}
	else
	{
		TextureManager::Instance()->draw("pause", 4000, 3000, 907, 600, Game::Instance()->getRenderer(), 0.0, 100);
	}
	TextureManager::Instance()->draw("background_front", front_bgPOS.x, front_bgPOS.y, Game::Instance()->getRenderer(), true, SDL_FLIP_NONE);
	ScoreBoardManager::Instance()->Draw();
}

void Level1Scene::update()
{
	if (!(m_pPlayer->getIsColliding()))
	{

		if (!Game::Instance()->getPause())
		{
			if (KeyHeld(SDL_SCANCODE_A))
			{
				m_pPlayer->setAcceleration(glm::vec2(-7.5, m_pPlayer->getAcceleration().y));

				/*if (m_pPlayer->getPosition().x >= 5)
				{
					m_pPlayer->setMotion(-500, 'x');
				}*/
			}
			else if (KeyHeld(SDL_SCANCODE_D))
			{
				m_pPlayer->setAcceleration(glm::vec2(7.5, m_pPlayer->getAcceleration().y));
				
				/*if (m_pPlayer->getPosition().x <= 795)
				{
					m_pPlayer->setMotion(500, 'x');
				}*/
			}

			if (KeyHeld(SDL_SCANCODE_W))
			{
				if (m_pPlayer->getPosition().y == 436.0)
				{
					m_pPlayer->setAcceleration(glm::vec2(m_pPlayer->getAcceleration().x, -15.0));
					TheSoundManager::Instance()->playSound("jump", 0);
				}


				/*if (m_pPlayer->getPosition().y >= 5)
				{
					m_pPlayer->setMotion(1, 'y');
				}*/
			}
			else if (KeyHeld(SDL_SCANCODE_S))
			{
				//m_pPlayer->setAcceleration(glm::vec2(0, -1.0));

				if (m_pPlayer->getPosition().y == 436.0)
				{
					TheSoundManager::Instance()->playSound("roll", 0);
					rolling = true;
				}
			}

			m_Resume->setPosition(glm::vec2(4000.0f, 4000.0f));
			m_Quit->setPosition(glm::vec2(4000.0f, 4000.0f));
			if (bulletTimer >= 0)
			{
				bulletTimer -= deltaTime;
			}
			else
			{
				bulletTimer = 0;
			}
			if (enemyBulletTimer >= 0)
			{
				enemyBulletTimer -= deltaTime;
			}
			else
			{
				enemyBulletTimer = 0;

			}
			//enemyShoot();
			//bulletCollisionCheck();
			CollisionCheck();
			updateDisplayList();
			front_bgPOS = checkBoundary(front_bgPOS);
			front_bgPOS = glm::vec2(front_bgPOS.x - deltaTime * 100, front_bgPOS.y);


			ExplosionManager::Instance()->update();
			BulletManager::Instance()->update();
			if (m_pPlayer->getPosition().y >= 435)
			{
				if (rolling)
				{
					m_pPlayer->setAnimationState(ROLL);
				}
				else
				{
					if (m_pPlayer->getAnimState() != LEFTING)
					{
						m_pPlayer->setAnimationState(LEFTING);
					}
				}
			}
			else if (m_pPlayer->getPosition().y < 435)
			{
				m_pPlayer->setAnimationState(JUMP_LEFT);
			}
		}
		else
		{
			m_Resume->setPosition(glm::vec2(400.0f, 400.0f));
			m_Quit->setPosition(glm::vec2(400.0f, 500.0f));
		}
	}
	else
	{
		if (!dead)
		{
			m_pPlayer->setAnimationState(DEAD);
			TheSoundManager::Instance()->playSound("death", 0);

			if (dyingTimer > 0.0)
			{
				dyingTimer -= deltaTime;
			}
			else
				dead = true;
		}
		else
		{
			if (deadTimer > 0.0)
			{
				m_pPlayer->setAnimationState(TOMB);
				deadTimer -= deltaTime;
			}
			else
			{
				Game::Instance()->changeSceneState(LOSE_SCENE);
			}
		}
		
	}
	glm::vec2 Scores = Game::Instance()->GetScores();
	ScoreBoardManager::Instance()->setScore(Scores.x);
	ScoreBoardManager::Instance()->setHS(Scores.y);
}

void Level1Scene::clean()
{

	//bulletClean();

	//delete m_pPlayer;
	//m_pPlayer = nullptr;

	//delete m_Enemy;
	//m_Enemy = nullptr;

	removeAllChildren();
}

void Level1Scene::handleEvents()
{
	auto wheel = 0;

	SDL_Keycode keyPressed;
	SDL_Keycode keyReleased;
	
	SDL_Event event;

	std::memcpy(s_keysLast, s_keysCurr, s_numKeys);
	s_lastKeyDown = s_lastKeyUp = -1;

	while (SDL_PollEvent(&event))
	{
		if (m_Resume != nullptr)
		{
			m_Resume->handleMouseEvents(&event);
			m_Quit->handleMouseEvents(&event);
		}

		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
			//auto explosion = ExplosionManager::Instance()->getExplosion();
			//explosion->setPosition(m_mousePosition);
			}
			break;
		case SDL_KEYDOWN:
			keyPressed = event.key.keysym.sym;
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				//TheGame::Instance()->changeSceneState(SceneState::PLAY_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			}
			// movement keys
			{
				//if(keyPressed == SDLK_w)
				//{
				//	//std::cout << "move forward" << std::endl;
				//	TheSoundManager::Instance()->playSound("jump", 0);
				//	if (m_pPlayer->getPosition().y >= 5)
				//	{
				//		m_pPlayer->setMotion(1, 'y');
				//	}
				//}

				//if (keyPressed == SDLK_a)
				//{
				//	//std::cout << "move left" << std::endl;
				//	if (m_pPlayer->getPosition().x >= 5)
				//	{
				//		m_pPlayer->setMotion(-500, 'x');
				//	}
				//}

				//if (keyPressed == SDLK_s)
				//{
				//	//std::cout << "move back" << std::endl;
				//	TheSoundManager::Instance()->playSound("roll", 0);
				//	rolling = true;
				//}

				//if (keyPressed == SDLK_d)
				//{
				//	//std::cout << "move right" << std::endl;
				//	if (m_pPlayer->getPosition().x <= 795)
				//	{
				//		m_pPlayer->setMotion(500, 'x');
				//	}
				//}

				if (keyPressed == SDLK_SPACE)
				{

					/*if (bulletTimer == 0)
					{
						SoundManager::Instance()->playSound("shoot", 0);
						auto bullet = BulletManager::Instance()->getBullet();
						auto thing = m_pPlayer->getPosition();
						bullet->setActive();
						bullet->setPosition(glm::vec2(thing.x, thing.y - 10));
						bulletTimer = 0.25;
					}*/
				}

				if (keyPressed == SDLK_p)
				{
					Game::Instance()->setPause(true);
				}
				if (keyPressed == SDLK_r)
				{
					Game::Instance()->setPause(false);
				}

				if (keyPressed == SDLK_y)
				{
					//Game::Instance()->setVolume(-4);
				}

				if (keyPressed == SDLK_u)
				{
					//Game::Instance()->setVolume(4);
				}
			}
			
			break;
		case SDL_KEYUP:
			keyReleased = event.key.keysym.sym;

			/*if (!keyReleased == SDLK_SPACE)
			{
				m_pPlayer->setAnimationState(LEFTING);
			}*/

			if (keyReleased == SDLK_s)
			{
				rolling = false;
			}
			


			break;
			
		}
	}
	s_keysCurr = SDL_GetKeyboardState(&s_numKeys);

}

void Level1Scene::start()
{
	BG* m_Background;

	m_Background = new BG();
	addChild(m_Background);

	m_pPlayer = new Player();
	addChild(m_pPlayer);

	BulletManager::Instance()->m_buildBullets();

	TextureManager::Instance()->load("../Assets/sprites/pauseState.png", "pause", Game::Instance()->getRenderer());

	m_Resume = new Button("../Assets/sprites/resume.png", "resume", RESUME_BOTTON);
	m_Resume->setPosition(glm::vec2(4000.0f, 4000.0f));
	m_Resume->setAlpha(200);
	m_Resume->addEventListener(CLICK, [](Button* button)-> void
		{
			button->setActive(false);
			Game::Instance()->setPause(false);
		});

	m_Resume->addEventListener(MOUSE_OVER, [](Button* button)->void
		{
			button->setAlpha(255);
		});

	m_Resume->addEventListener(MOUSE_OUT, [](Button* button)->void
		{
			button->setAlpha(200);
		});
	addChild(m_Resume);

	m_Quit = new Button("../Assets/sprites/quit.png", "quit", QUIT_BOTTON);
	m_Quit->setPosition(glm::vec2(4000.0f, 4000.0f));
	m_Quit->setAlpha(200);
	m_Quit->addEventListener(CLICK, [](Button* button)-> void
		{
			button->setActive(false);
			Game::Instance()->quit();
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

	SoundManager::Instance()->load("../Assets/audio/roll.wav", "roll", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/jump.wav", "jump", SOUND_SFX);
	SoundManager::Instance()->load("../Assets/audio/death.wav", "death", SOUND_SFX);

	Obs1 = new Obstacle('d');
	addChild(Obs1);
	Obs2 = new Obstacle('t');
	addChild(Obs2);
	Obs3 = new Obstacle('p');
	addChild(Obs3);
	Obs4 = new Obstacle('b');
	addChild(Obs4);
	Obs5 = new Obstacle('h');
	addChild(Obs5);

	ObsList.push_back(Obs1);
	ObsList.push_back(Obs2);
	ObsList.push_back(Obs3);
	ObsList.push_back(Obs4);
	ObsList.push_back(Obs5);

	TextureManager::Instance()->load("../Assets/sprites/backgroundFront.png", "background_front", Game::Instance()->getRenderer());
	front_bgPOS = glm::vec2(800, 550);

	s_keysCurr = SDL_GetKeyboardState(&s_numKeys);
	s_keysLast = new Uint8[s_numKeys];
	std::memcpy(s_keysLast, s_keysCurr, s_numKeys);


}

bool Level1Scene::KeyHeld(const SDL_Scancode c)
{
	if (s_keysCurr != nullptr)
	{
		if (s_keysCurr[c] == 1)
			return true;
		else
			return false;
	}
	return false;
}

bool Level1Scene::KeyPressed(const SDL_Scancode c)
{
	return (s_keysCurr[c] > s_keysLast[c]);
}

bool Level1Scene::KeyReleased(const SDL_Scancode c)
{
	return (s_keysCurr[c] < s_keysLast[c]);
}

int Level1Scene::LastKeyDown()
{
	return s_lastKeyDown;
}

int Level1Scene::LastKeyUp()
{
	return s_lastKeyUp;
}

void Level1Scene::CollisionCheck()
{
	for (auto element : ObsList)
	{
		Collision::circleAABBCheck(m_pPlayer, element);
	}
}

glm::vec2 Level1Scene::checkBoundary(glm::vec2 Pos)
{
	if (Pos.x < 10)
	{
		return (glm::vec2(800, Pos.y));
	}
	else
	{
		return Pos;
	}
}

//void Level1Scene::enemyShoot()
//{
//	if (enemyBulletTimer <= 0)
//	{
//		SoundManager::Instance()->playSound("shoot", 0);
//		auto bullet = BulletManager::Instance()->getEBullet();
//		auto thing = m_Enemy->getPosition();
//		bullet->setActive();
//		bullet->setPosition(glm::vec2(thing.x, thing.y + 10));
//		enemyBulletTimer = 0.4;
//	}
//}

//void Level1Scene::bulletCollisionCheck()
//{
//	auto player_stuff = BulletManager::Instance()->getPlayerBullets();
//	auto enemy_stuff = BulletManager::Instance()->getEnemyBullets();
//
//	//Checking enemy and player bullet
//
//	for (auto p_bullets : player_stuff)
//	{
//		Collision::squaredRadiusCheck(m_Enemy, p_bullets);
//	}
//
//	//Checking Player and Enemy Bullets
//
//	for (auto e_bullets : enemy_stuff)
//	{
//		Collision::squaredRadiusCheck(m_pPlayer, e_bullets);
//	}
//}

//void Level1Scene::bulletClean()
//{
//	auto player_stuff = BulletManager::Instance()->getPlayerBullets();
//	auto enemy_stuff = BulletManager::Instance()->getEnemyBullets();
//
//
//	for (auto p_bullets : player_stuff)
//	{
//		delete p_bullets;
//		p_bullets = nullptr;
//	}
//
//	for (auto e_bullets : enemy_stuff)
//	{
//		delete e_bullets;
//		e_bullets = nullptr;
//	}
//}
