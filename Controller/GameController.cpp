#include"GameController.h"
#include"View\BeiginScene.h"
#include"View\HelloWorldScene.h"
#include"Model\Obj\Obj.h"
#include"ObjController.h"
int GameController::screenPixW;//屏幕宽度
int GameController::screenPixH;//屏幕高度
int GameController::screenSizeW;//屏幕宽度
int GameController::screenSizeH;//屏幕高度
int GameController::last_screenSizeW;//屏幕宽度
int GameController::last_screenSizeH;//屏幕高度
int GameController::zero_x;//显示原点
int GameController::zero_y;//显示原点
float GameController::position_x;
float GameController::position_y;
float GameController::timeInterval = 0.02;
Size GameController::anchorPoint = Size(0.5,0.5);
int GameController::mapX = MAP_NUM * POSITION_LIST_X;
int GameController::mapY = MAP_NUM * POSITION_LIST_Y;
 Size GameController::screenScale;
 float GameController::wUnit;
 float GameController::hUnit;
 bool GameController::bSreeenChange;
 Scene * GameController::scene;//当前scene
string GameController::gameName;// = "conquer";
int GameController::xoffset = 10;//允许player偏移显示中心位置
int GameController::yoffset = 10;//允许player偏移显示中心位置
bool GameController::bSreeenScale = false;
Vec2 GameController::screenSize[3];
 int GameController::now_screenSize = 0;
USING_NS_CC;
GameController* GameController::m_Instance = new GameController();
int GameController::timestamp = 0;
GameController::~GameController() {
	SpriteFrameCache::destroyInstance(); 
}
void GameController::setCenterPosition(int x,int y) {
	GameController::position_x = x;
	GameController::position_y = y;
	GameController::zero_x = GameController::position_x - GameController::screenSizeW / 2;
	GameController::zero_y = GameController::position_y - GameController::screenSizeH / 2;
}
void GameController::initScreen(int x, int y) {
	GameController::screenSizeH = y;
	GameController::screenSizeW = x;
	GameController::last_screenSizeW = GameController::screenSizeW;
	GameController::last_screenSizeH = GameController::screenSizeH;
	GameController::position_x = GameController::screenSizeW / 2;
	GameController::position_y = GameController::screenSizeH / 2;
	GameController::zero_x = GameController::position_x - GameController::screenSizeW / 2;
	GameController::zero_y = GameController::position_y - GameController::screenSizeH / 2;
	GameController::bSreeenChange = true;
	GameController::bSreeenScale = true;
}
GameController::GameController() {
	GameController::screenSize[0] = Vec2(150,90);
	GameController::screenSize[1] = Vec2(100, 60);
	GameController::screenSize[2] = Vec2(50, 30);
	GameController::bSreeenChange = false;
	initScreen(GameController::screenSize[1].x, GameController::screenSize[1].y);
	GameController::screenPixH = 800;
	GameController::screenPixW = 1000;
#ifdef WIN_32
	
#else
#ifdef ANDROID
	
#endif
#endif
}
//取得 单位size等于多少piont
Size GameController::getScreenUnitSize() {

	if (screenScale.width == 0) {
		auto screenPoint = Director::getInstance()->getVisibleSize();
		wUnit = screenPoint.width * 1.0 / screenSizeW;
		hUnit = screenPoint.height * 1.0 / screenSizeH;
		screenScale = Size(wUnit,hUnit);
	}
	return screenScale;
}
GameController* GameController::GetInstance(){
	
	return m_Instance;
}

void GameController::loadText()
{
	//按钮文字 
	CCConfiguration::sharedConfiguration()->loadConfigFile("config/strings.plist");
}
void GameController::loadTexture()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	
	cache->addSpriteFramesWithFile("texture/spear_soldiers.plist","texture/spear_soldiers.png");
	cache->addSpriteFramesWithFile("texture/tank_2.plist", "texture/tank_2.png");
	cache->addSpriteFramesWithFile("texture/tank.plist", "texture/tank.png");
	cache->addSpriteFramesWithFile("texture/plant.plist", "texture/plant.png");
	cache->addSpriteFramesWithFile("texture/weapon.plist", "texture/weapon.png");
	cache->addSpriteFramesWithFile("texture/soldier.plist", "texture/soldier.png");
	cache->addSpriteFramesWithFile("texture/building.plist", "texture/building.png");
}
void GameController::Init() {
	loadText();
	loadTexture();
	srand((unsigned)time(0));
	
}
void GameController::BeiginWin() {
	auto scene = BeiginScene::scene();
	//auto scene = HelloWorld::scene();
	auto director = Director::getInstance();
	// run
	director->runWithScene(scene);
}
void GameController::Start() {
	BeiginWin();

}
void GameController::changeScene(Scene*scene) {
	GameController::scene = scene;
	Director::getInstance()->replaceScene(scene);
}
void GameController::setScreenSizeInPix(float w,float h) {
	auto eglVeiw = Director::getInstance()->getOpenGLView();
	if(eglVeiw)
	eglVeiw->setFrameSize(w,h);
}
bool GameController::positionSreenCenter(Vec2 vec2, Vec2 offset,bool bEnd) {
#ifdef DEBUG
	CCLOG("positionSreenCenter start");
#endif
	xoffset = GameController::screenSizeW / 4;// GameController::screenSizeW / 4;
	yoffset = GameController::screenSizeH / 4;// GameController::screenSizeH / 4;
	/*static Vec2 position = Vec2(GameController::position_x, GameController::position_y);
	if (vec2 == Vec2(0,0)) {
		GameController::position_x = position.x;
		GameController::position_y = position.y;
		GameController::bSreeenChange = true;
	}*/
	static int last_x = vec2.x;
	static int last_y = vec2.y;
#ifdef MUTI_MOVE
	static int last_x = vec2.x;
	static int last_y = vec2.y;
#endif
	if (vec2.x > GameController::position_x + GameController::xoffset) {
		if (GameController::position_x < MAP_NUM * POSITION_LIST_X - GameController::screenSizeW / 2) {
#ifdef MUTI_MOVE
			GameController::position_x+=vec2.x - last_x;
#else
			//GameController::position_x++;
			//position.x++;
			if (bEnd) {
				GameController::position_x = ++last_x ;

			}else
			GameController::position_x += offset.x;
			GameController::bSreeenChange = true;
#endif
			
		}
		
	}
	else if(vec2.x  < GameController::position_x - GameController::xoffset){
		if (GameController::position_x - GameController::screenSizeW / 2 > 0){
#ifdef MUTI_MOVE
			GameController::position_x+= vec2.x - last_x;
#else
			//GameController::position_x--;
			//position.x--;
			if (bEnd) {
				GameController::position_x = --last_x;
			}
			else
			GameController::position_x -= offset.x;
			GameController::bSreeenChange = true;
#endif
			
		}
		
	}

	if (vec2.y > GameController::position_y + GameController::yoffset) {
		if (GameController::position_y < MAP_NUM * POSITION_LIST_Y - GameController::screenSizeH / 2){
#ifdef MUTI_MOVE
			GameController::position_y+= vec2.y - last_y;
#else
			//GameController::position_y++;
			//position.y++;
			if (bEnd) {
				GameController::position_y = ++last_y;
			}
			else
			GameController::position_y += offset.y;
			GameController::bSreeenChange = true;
#endif
			
		}
		
	}
	else if (vec2.y  < GameController::position_y - GameController::yoffset) {
		if (GameController::position_y - GameController::screenSizeH / 2 > 0){
#ifdef MUTI_MOVE
			GameController::position_y += vec2.y - last_y;
#else
			//GameController::position_y--;
			//position.y--;
			if (bEnd) {
				GameController::position_y = --last_y;
			}
			else
			GameController::position_y -= offset.y;
			GameController::bSreeenChange = true;
#endif
			
		}
		
	}
	if (GameController::bSreeenChange) {
		GameController::zero_x = GameController::position_x - GameController::screenSizeW / 2;
		GameController::zero_y = GameController::position_y - GameController::screenSizeH / 2;
		
		//CCLOG("%d %d", GameController::position_x, GameController::position_y);
		return true;
	}
	else {
		return false;
	}
	
#ifdef MUTI_MOVE
	last_x = vec2.x;
	last_y = vec2.y;
#endif
#ifdef DEBUG
	CCLOG("positionSreenCenter end");
#endif
}
void GameController::upScreen() {
	now_screenSize--;
	if (now_screenSize < 0)now_screenSize = 0;
	else
	initScreen(screenSize[now_screenSize].x, screenSize[now_screenSize].y);
}
void GameController::downScreen() {
	now_screenSize++;
	if (now_screenSize > 2)now_screenSize = 2;
	else
	initScreen(screenSize[now_screenSize].x, screenSize[now_screenSize].y);
}
