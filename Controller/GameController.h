#pragma once

#include"Core\Controller.h"


using namespace ui;
class GameController : public Controller {
private:
	static GameController * m_Instance;
	static Size screenScale;
public:
	static int screenPixW ;//��Ļ���
	static int screenPixH;//��Ļ�߶�
	static int screenSizeW;//��Ļ���
	static int screenSizeH;//��Ļ�߶�
	static int last_screenSizeW;//��Ļ���
	static int last_screenSizeH;//��Ļ�߶�
	static float position_x;//��ʾ����
	static float position_y;//��ʾ����
	static int zero_x;//��ʾԭ��
	static int zero_y;//��ʾԭ��
	static int mapX ;
	static int mapY ;
	static float timeInterval;//ʱ����
	static Size anchorPoint;
	static int xoffset;//����playerƫ����ʾ����λ��
	static int yoffset;//����playerƫ����ʾ����λ��
	static float wUnit;
	static float hUnit;
	static bool bSreeenChange;//use for position
	static bool bSreeenScale;//use for scale
	static Scene * scene;//��ǰscene
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