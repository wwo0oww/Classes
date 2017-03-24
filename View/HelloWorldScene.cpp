#include "HelloWorldScene.h"
#include "../Core/AppMacros.h"
#include "../Model/Obj/Biological/Biological.h"
#include"Core\UI\Progress.h"
USING_NS_CC;


Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
     closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
    closeItem->setPosition(Vec2(0,0));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/arial.ttf", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    label->setPosition(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height);

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
	
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize / 2) + origin);

    // add the sprite as a child to this layer
   // this->addChild(sprite);
    
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tank_str_m_d (1).png");
	CCSprite* p1 = CCSprite::createWithSpriteFrame(frame);
	p1->setPosition(Vec2(50,50) + origin);
	//p1->setp
	p1->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(p1);
	Progress* _progress =new Progress();
	_progress->initbg(CCSprite::create());
	_progress->initfill(CCSprite::create());
	
	_progress->progress->setPosition(Vec2(160, 160) + origin);
	_progress->setProgress(10);
	this->addChild(_progress->progress);
	_progress->progress->setRotation(90);

	CCSprite* p2 = CCSprite::createWithSpriteFrame(frame);
	p2->setPosition(Vec2(60, 60) + origin);
	p2->setScaleY(-1);
	//p1->setp
	p2->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(p2);

    return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
