#pragma once

#include"Core\Controller.h"


USING_NS_CC;
using namespace ui;

class SpriteController {
//����
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

	static vector<SpritesNode*> spriteList;//�洢���þ���
	static map<long, void*>spriteUsedList;//�洢���þ���
	

	static MyLock* spirte_lc;//������
	static MyLock* frame_lc;//frame��
	
	static Vec2 spriteScale[MAX_TYPE][4][4];
	

	//����洢spriteframe��Ϣ��������߳��޷���ȡframe����
	 //std::map<char*, CCSpriteFrame*>spriteFrame;
	//���չؼ��ִ洢spriteframe��Ϣ��������߳��޷���ȡframe���� 
	//>>>>>>>>>>>>>>>>>>>>>>>����
	static map<std::string, std::map<std::string, CCSpriteFrame*>*>spriteFrameRoute;
//����
private:
	SpriteController();
	~SpriteController();
public:
	static SpriteController * GetInstance();

	static void freeSprites(void *obj);
	//��ȡһ��tag
	static void getOneTag(void*);
	//����һ������

	static void createSprites(void *);
	
	//�ı侫��ͼƬ
	static void changeSpritesPic(void * obj);
	static void resetSprite(void*obj_,bool bscale = false);
	//��ȡ frame
	static CCSpriteFrame* getSpriteFrame(std::string, std::string);

	//��ʼ��frame
	static void initSpriteFrame(SpriteFrameInfo*);
};