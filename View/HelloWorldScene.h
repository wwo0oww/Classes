#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	cocos2d::MenuItemImage* closeItem;
	cocos2d::Sprite *sprites[600][400];
public:
    virtual bool init() override;
	void move(float dt);
    static cocos2d::Scene* scene();
	
    // a selector callback
    void menuCloseCallback(Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__