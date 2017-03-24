#pragma once

#include"Core\Controller.h"


USING_NS_CC;
using namespace ui;

class SpriteController {
//属性
public:
	struct SpritesNode {
		void* list[OBJ_MAX_SPRITE];
		int len = 0;
		bool used = false;
	};
private:
	static void dearBaseSprites(void*);
	static void changeBaseSprites( void*);
public:

	

	struct SpriteFrameInfo {
		SpriteFrameInfo*next;
		char type[15];
		char prefix[MAX_PREFIX];
		int total;
	}*pSpriteFrameInfo;
	static SpriteController * m_Instance;
	static bool bNewSprite;

	static vector<SpritesNode*> spriteList;//存储可用精灵
	static map<long, void*>spriteUsedList;//存储在用精灵
	

	static MyLock* spirte_lc;//精灵锁
	static MyLock* frame_lc;//frame锁
	
	static Vec2 spriteScale[MAX_TYPE][4][4];
	

	//具体存储spriteframe信息，解决多线程无法获取frame问题
	 //std::map<char*, CCSpriteFrame*>spriteFrame;
	//按照关键字存储spriteframe信息，解决多线程无法获取frame问题 
	//>>>>>>>>>>>>>>>>>>>>>>>弃用
	static map<std::string, std::map<std::string, CCSpriteFrame*>*>spriteFrameRoute;
//方法
private:
	SpriteController();
	~SpriteController();
public:
	static SpriteController * GetInstance();

	static void freeSprites(void *obj);
	//获取一个tag
	static void getOneTag(void*);
	//创建一个精灵

	static void createSprites(void *);
	
	//改变精灵图片
	static void changeSpritesPic(void * obj);
	static void resetSprite(void*obj_,bool bscale = false);
	//获取 frame
	static CCSpriteFrame* getSpriteFrame(std::string, std::string);

	//初始化frame
	static void initSpriteFrame(SpriteFrameInfo*);
};