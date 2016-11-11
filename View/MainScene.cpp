#include"MainScene.h"
#include "../Core/AppMacros.h"
#include "../Model/Obj/Biological/Biological.h"
#include "cocos2d.h"
#include "ui\UIButton.h"
#include"Controller\EventController.h"
#include"Controller\GameController.h"
#include"Model\Obj\Biological\Tank\Tank.h"
#include"Model\data.h"
USING_NS_CC;
using namespace ui;
Scene* MainScene::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	MainScene *layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
// on "init" you need to initialize your instance
bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	/*Texture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("image.png");
	CCSpriteBatchNode *spriteBatch;
	spriteBatch->initWithTexture(texture);
	addChild(spriteBatch);*/
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	//cache->addSpriteFramesWithFile("spear_soldiers.plist", "spear_soldiers.png");
	cache->addSpriteFramesWithFile("texture/tank_2.plist", "texture/tank_2.png");
	sprite = CCSprite::createWithSpriteFrameName("2 (1).png");
	if(sprite != NULL){
		sprite->setPosition(100,100);
		this->addChild(sprite);
	}
	Tank* tank = new Tank();
	tank->Method("setDirection",new ClassData::ObjData(Direction::DOWN));
	this->schedule(SEL_SCHEDULE(&MainScene::test), 0.1f);

	return true;
}
void MainScene::test(float dt) {
	count = count % 74 + 1;
	char name[20];
	sprintf_s(name,20,"2 (%d).png",count);
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
	sprite->setDisplayFrame(frame);
}


