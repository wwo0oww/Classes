#include"GameController.h"
#include"View\BeiginScene.h"
USING_NS_CC;
GameController* GameController::m_Instance = new GameController();
GameController* GameController::getInstance(){
	return m_Instance;
}
void GameController::loadText()
{
	//°´Å¥ÎÄ×Ö 
	CCConfiguration::sharedConfiguration()->loadConfigFile("config/strings.plist");
}
void GameController::loadTexture()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	
	cache->addSpriteFramesWithFile("texture/spear_soldiers.plist","texture/spear_soldiers.png");
	cache->addSpriteFramesWithFile("texture/tank_2.plist", "texture/tank_2.png");

}
void GameController::init() {
	this->loadText();
	this->loadTexture();
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->height = visibleSize.height;
	this->width = visibleSize.width;
	
}
void GameController::beiginWin() {
	auto scene = BeiginScene::scene();
	auto director = Director::getInstance();
	// run
	director->runWithScene(scene);
}
void GameController::start() {
	this->beiginWin();

}