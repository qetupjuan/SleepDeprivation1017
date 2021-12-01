#include "BG.h"
#include "TextureManager.h"
#include "Game.h"

BG::BG()
{
	TextureManager::Instance()->load("../Assets/sprites/sickSpace.png", "background", Game::Instance()->getRenderer());
	TextureManager::Instance()->load("../Assets/sprites/backgroundTree.png", "background_trees", Game::Instance()->getRenderer());

	//setPosition(glm::vec2(800, 300));

	back_bgPOS = glm::vec2(800, 300);
	tree_bgPOS = glm::vec2(800, 300);
}

BG::~BG() = default;

void BG::draw()
{
	TextureManager::Instance()->draw("background", back_bgPOS.x, back_bgPOS.y, Game::Instance()->getRenderer(), true, SDL_FLIP_NONE);
	TextureManager::Instance()->draw("background_trees", tree_bgPOS.x, tree_bgPOS.y, Game::Instance()->getRenderer(), true, SDL_FLIP_NONE);
}

void BG::update()
{
	back_bgPOS = checkBoundary(back_bgPOS);
	tree_bgPOS = checkBoundary(tree_bgPOS);

	back_bgPOS = glm::vec2(back_bgPOS.x - time * 30, back_bgPOS.y);
	tree_bgPOS = glm::vec2(tree_bgPOS.x - time * 50, tree_bgPOS.y);
}

void BG::clean()
{
}

glm::vec2 BG::checkBoundary(glm::vec2 Pos)
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

