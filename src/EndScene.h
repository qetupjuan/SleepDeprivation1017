#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__

#include "Scene.h"
//#include "Label.h"
#include "Button.h"

class EndScene final : public Scene
{
public:
	EndScene();
	EndScene(const char option);
	~EndScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	//Label* m_label{};
	std::string outcome;

	Button* m_MainMenu;
	Button* m_Quit;
};

#endif /* defined (__END_SCENE__) */