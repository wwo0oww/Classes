#include"BeiginScene.h"
#include "../Core/AppMacros.h"
#include "../Model/Obj/Biological/Biological.h"
#include "cocos2d.h"
#include "ui\UIButton.h"
#include"Controller\EventController.h"

USING_NS_CC;
using namespace ui;
Scene* BeiginScene::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	BeiginScene *layer = BeiginScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
// on "init" you need to initialize your instance
bool BeiginScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	int num = 3;
	int height = 30;
	int width = 80;
	int offset = 20;
	int fontsize = 15;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	int all_height = height *  num + (num - 1) * offset;

	int init_height = (visibleSize.height - all_height) / 2;

	int init_width = visibleSize.width / 2;

	int index = 3;

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	
	CCConfiguration *conf = CCConfiguration::sharedConfiguration();
	auto singleplayerStr = conf->getValue("singleplayer");
	auto multiplayerStr = conf->getValue("multiplayer");
	auto settingStr = conf->getValue("setting");
	//创建button对象  
	auto singleplayer = Button::create("HelloWorld.png", "HelloWorld.png");
	auto multiplayer = Button::create("HelloWorld.png", "HelloWorld.png");
	auto setting = Button::create("HelloWorld.png", "HelloWorld.png");
	//打开scale9 可以拉伸图片  
	singleplayer->setScale9Enabled(true);
	multiplayer->setScale9Enabled(true);
	setting->setScale9Enabled(true);
	//设置button title  
	singleplayer->setTitleText(singleplayerStr.getDescription());
	multiplayer->setTitleText(multiplayerStr.getDescription());
	setting->setTitleText(settingStr.getDescription());
	//设置button title字体大小  
	singleplayer->setTitleFontSize(fontsize);
	multiplayer->setTitleFontSize(fontsize);
	setting->setTitleFontSize(fontsize);
	//设置btn的内容大小  
	singleplayer->setContentSize(Size(width, height));
	multiplayer->setContentSize(Size(width, height));
	setting->setContentSize(Size(width, height));

	
	//btn->setPosition(Vec2(width/2,height/2));
	//设置btn的位置  
	singleplayer->setPosition(Vec2(init_width, init_height + --index * (height + offset) + height / 2));
	multiplayer->setPosition(Vec2(init_width, init_height + --index * (height + offset) + height / 2));
	setting->setPosition(Vec2(init_width, init_height + --index * (height + offset) + height / 2));
	//为按钮添加触摸事件监听  
	singleplayer->addTouchEventListener(this,toucheventselector(BeiginScene::onSinglePlayer));
	multiplayer->addTouchEventListener(this, toucheventselector(BeiginScene::onMultiPlayer));
	setting->addTouchEventListener(this, toucheventselector(BeiginScene::onSetting));
	this->addChild(singleplayer, 4);
	this->addChild(multiplayer, 4);
	this->addChild(setting, 4);
	

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	//closeItem = MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	//closeItem->setPosition(Vec2(0, 0));

	//// create menu, it's an autorelease object
	//auto menu = Menu::create(closeItem, nullptr);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("Hello World", "fonts/arial.ttf", TITLE_FONT_SIZE);

	//// position the label on the center of the screen
	//label->setPosition(origin.x + visibleSize.width / 2,
	//	origin.y + visibleSize.height - label->getContentSize().height);

	//// add the label as a child to this layer
	//this->addChild(label, 1);

	//// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");

	//// position the sprite on the center of the screen
	//sprite->setPosition(Vec2(visibleSize / 2) + origin);

	//// add the sprite as a child to this layer
	//this->addChild(sprite);

	return true;
}

void BeiginScene::onSinglePlayer(Ref *pSender, TouchEventType type){
	EventController::EventListener(pSender, type,EventController::Key::SINGLEPLAYER);
}
void BeiginScene::onMultiPlayer(Ref *pSender, TouchEventType type) {
	EventController::EventListener(pSender, type, EventController::Key::SINGLEPLAYER);
}
void BeiginScene::onSetting(Ref *pSender, TouchEventType type) {
	EventController::EventListener(pSender, type, EventController::Key::SINGLEPLAYER);
}

void BeiginScene::menuCloseCallback(Ref* sender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}