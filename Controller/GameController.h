#pragma once

#include"Core\Controller.h"


using namespace ui;
class GameController : public Controller {
private:
	static GameController * m_Instance;
	static Size screenScale;
public:
	static int screenPixW ;//屏幕宽度
	static int screenPixH;//屏幕高度
	static int screenSizeW;//屏幕宽度
	static int screenSizeH;//屏幕高度
	static int last_screenSizeW;//屏幕宽度
	static int last_screenSizeH;//屏幕高度
	static float position_x;//显示中心
	static float position_y;//显示中心
	static int zero_x;//显示原点
	static int zero_y;//显示原点
	static int mapX ;
	static int mapY ;
	static float timeInterval;//时间间隔
	static Size anchorPoint;
	static int xoffset;//允许player偏移显示中心位置
	static int yoffset;//允许player偏移显示中心位置
	static float wUnit;
	static float hUnit;
	static bool bSreeenChange;//use for position
	static bool bSreeenScale;//use for scale
	static Scene * scene;//当前scene
	static std::string gameName;// = "conquer";
	static Vec2 screenSize[3];
	static int now_screenSize;
	static int timestamp;
private:
	static void loadText();
	static void loadTexture();
public:
	static GameController* GetInstance();
	GameController();
	~GameController();
	static void Init();
	static void Start();
	static void BeiginWin();
	static void changeScene(Scene*);
	static void setScreenSizeInPix(float,float);
	static Size getScreenUnitSize();
	static bool positionSreenCenter(Vec2 vec2, Vec2 offset, bool bEnd);
	static void setCenterPosition(int x,int y);
	static void initScreen(int x, int y);
	static void upScreen();
	static void downScreen();
};