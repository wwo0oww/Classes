#pragma once
#include "cocos2d.h"
#include"Core\Controller.h"
class GameController : public Controller {
private:
	static GameController * m_Instance;
public:
	int width;
	int height;
private:
	void loadText();
	void loadTexture();
public:
	static GameController* getInstance();
	void init();
	void start();
	void beiginWin();
};