#include "ScoreBoardManager.h"
#include "Game.h"

ScoreBoardManager* ScoreBoardManager::m_pInstance = nullptr;

void ScoreBoardManager::Start()
{
	const SDL_Color yellow = { 255, 255, 0, 255 };
	m_pHighScoreLabel = new Label("HighScore: ", "Consolas", 24, yellow,
		glm::vec2(10.0f, 40.0f), TTF_STYLE_NORMAL, false);

	m_pScoreLabel = new Label("Score: 0", "Consolas", 24, yellow,
		glm::vec2(10.0f, 10.0f), TTF_STYLE_NORMAL, false);

	m_score = 0.0;
	m_high_score = 0.0;
}

void ScoreBoardManager::Draw() const
{
	//m_pLivesLabel->draw();

	m_pScoreLabel->draw();

	//if (showHighScore)
	//{
		m_pHighScoreLabel->draw();
	//}
}

int ScoreBoardManager::getScore() const
{
	return m_score;
}

void ScoreBoardManager::setScore(const int new_score)
{
	m_score = new_score;
	m_pScoreLabel->setText("Score: " + std::to_string(m_score));
}

void ScoreBoardManager::setHS(int new_hs)
{
	m_high_score = new_hs;
	m_pHighScoreLabel->setText("HighScore: " + std::to_string(m_high_score));
}

int ScoreBoardManager::getLives() const
{
	return m_lives;
}

void ScoreBoardManager::setLives(const int new_lives)
{
	m_lives = new_lives;
	if(m_lives < 1)
	{
		Game::Instance()->changeSceneState(END_SCENE);
	}
	//m_pLivesLabel->setText("Lives: " + std::to_string(m_lives));
}

void ScoreBoardManager::showHigh(bool hs)
{
	showHighScore = hs;
}

ScoreBoardManager::ScoreBoardManager()
{
	Start();
	setScore(Config::SCORE);
	setLives(Config::LIVES);
}

ScoreBoardManager::~ScoreBoardManager()
= default;
