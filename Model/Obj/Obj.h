#pragma once

#include"Model\data.h"
#include"Core\MyLock.h"
#include"Core\UI\Progress.h"
#ifdef MODE_MAP
#include"Controller\MapController.h"
#endif
#include"Controller\SpriteController.h"
using namespace ui;

class Obj  {
	//属性

public:
	
	enum class WayFindType {
		SIMPLE,//简单寻路
		AIM,//目的目的寻路
		PATROL,//巡逻
		WANDERING,//游荡
	};
	struct WayFindNode{
	private:
		int mainFX[MAX_STORAGE_FX];//本应该的fx
		int len;//当前正在使用方向下标
		bool bAIMing;
		WayFindNode() {
			bFxFinish = false;
		}
	public:
		Obj*obj;
		bool bxMove;
		bool bFxFinish;
		void setAIMing(bool AIMing) {
			if (!AIMing) {
				this->init();
			}
			this->bAIMing = AIMing;
		}
		bool getAIMing() {
			return this->bAIMing;
		}
		bool isNULL() {
			return this->len == 0;
		}
		void init() {
			this->len = 0;
		}
		
		void addFX(int fx) {
			if (this->len < MAX_STORAGE_FX)
				this->mainFX[this->len++] = fx;
			else
				this->obj->AIMMoveFull();
		}
		//获取当前在用的上一个
		int getLastFX() {
			if (this->len > 1)
				return this->mainFX[len - 2];
			else
				return -1;
		}
		//获取当前在用的上一个 并删除当前
		int useLastFX() {
			if (this->len > 1) {
				this->len--;
				return this->mainFX[this->len - 1];
			}
			else {
				this->len = 0;
				return -1;
			}
		}
		int getNowFX() {
			if (this->len > 0)
				return this->mainFX[len - 1];
			else
				return -1;
		}
		void setNowFX(int fx) {
			if (this->len > 1) {
				
				this->mainFX[this->len - 1] = fx;
			}
		}
		int getLen() {
			return this->len;
		}
		int getFXInIndex(int i) {
			if (i > 0 && i < MAX_STORAGE_FX)
				return this->mainFX[i];
			else
				return -1;
		}
	};
	
	struct DeathDearNode {
		struct DeathNode {
			int ID;
			Obj*obj;
			Obj*param;
			void(*dear_func)(Obj*,Obj*);
			DeathNode*next;
			DeathNode*last;
			
		};
		DeathDearNode() {
			this->init_();
		}
		DeathNode* add_(void(*func)(Obj*,Obj*), Obj*obj,Obj*param) {
			
			this->tail->ID = obj->ID;
			this->tail->obj = obj;
			this->tail->param = param;
			this->tail->dear_func = func;
			auto tmp = static_add<DeathNode>(this->head, this->tail);
			this->tail->ID = 0;
			return tmp;
			/*this->tail->ID = obj->ID;
			this->tail->obj = obj;
			this->tail->param = param;
			this->tail->dear_func = func;
			if (this->tail->next == NULL) {
				this->tail->next = (DeathNode*)malloc(sizeof(DeathNode));
				this->tail->next->next = NULL;
				this->tail->next->last = this->tail;

				this->tail->next->ID = 0;

			}
			auto tmp = this->tail;
			this->tail = this->tail->next;
			return tmp;*/
		}
		void delete_(DeathNode*p) {
			p->ID = 0;
			static_delete<DeathNode>(p,this->head,this->tail);
			/*if (p->last == NULL) {
				auto tmp = this->tail->next;
				this->tail->next = p;
				p->last = this->tail;
				if (tmp != NULL)
					tmp->last = p;
				this->head = p->next;
				p->next = tmp;

				this->head->last = NULL;
			}
			else {
				p->last->next = p->next;
				p->next->last = p->last;

				auto tmp = this->tail->next;
				this->tail->next = p;
				p->last = this->tail;
				p->next = tmp;
				if (tmp != NULL)
					tmp->last = p;
			}*/
		}
		void free_() {
			auto p= this->head;
			while (p != NULL) {
				auto tmp = p;
				p = p->next;
				free(tmp);
			}
			this->head = this->tail = NULL;
		}
		void init_() {
			this->head = (DeathDearNode::DeathNode*)malloc(sizeof(DeathDearNode::DeathNode));
			this->head->ID = 0;
			this->head->last = NULL;
			this->head->next = NULL;
			this->tail = this->head;
		}
		void traverse() {
			auto p = this->head;
			while (p != this->tail) {
				p->dear_func(p->obj,p->param);
				p->ID = 0;
				p = p->next;
			}
			this->tail = this->head;
		}
		void clear() {
			auto p = this->head;
			while (p != this->tail) {
				p->ID = 0;
				p = p->next;
			}
			this->tail = this->head;
		}
	private:
		DeathNode*head;
		DeathNode*tail;
	};
	DeathDearNode*deathDearNode;
	struct AttackNode {
		int ID;
		Obj*obj;
		AttackNode*next;
		AttackNode*last;
	};
	struct AttackObj {
		AttackNode*attackNode;
	};
	struct  AttackList {
		void delete_by_id(int ID) {
			auto p = this->attack_head;
			while (p != this->attack_tail) {
				if (p->ID == ID) {
					this->delete_(p);
					break;
				}
			}
		}
		void free_() {
			auto p = this->attack_head;
			while (p != NULL) {
				auto tmp = p;
				p = p->next;
				free(tmp);
			}
			this->attack_head = this->attack_tail = NULL;
		}
		
		
		void clear() {
			auto p = this->attack_head;
			while (p != this->attack_tail) {
				p->ID = 0;
				p = p->next;
			}
			this->attack_tail = this->attack_head;
		}
		void delete_(AttackNode*p) {
			p->ID = 0;
			static_delete<AttackNode>(p,this->attack_head,this->attack_tail);
			/*if (p->last == NULL) {
				auto tmp = this->attack_tail->next;
				this->attack_tail->next = p;
				p->last = this->attack_tail;
				if (tmp != NULL)
					tmp->last = p;
				this->attack_head = p->next;
				p->next = tmp;

				this->attack_head->last = NULL;
			}
			else {
				p->last->next = p->next;
				p->next->last = p->last;

				auto tmp = this->attack_tail->next;
				this->attack_tail->next = p;
				p->last = this->attack_tail;
				p->next = tmp;
				if (tmp != NULL)
					tmp->last = p;
			}*/
		}
		AttackNode*add_(Obj*obj) {
			this->attack_tail->ID = obj->ID;
			this->attack_tail->obj = obj;
			auto tmp = static_add<AttackNode>(this->attack_head,this->attack_tail);
			this->attack_tail->ID = 0;
			return tmp;
		}
		AttackList() {
			this->init_();
		}
		void init_() {
			this->attack_head = (AttackNode*)malloc(sizeof(AttackNode));
			this->attack_head->next = NULL;
			this->attack_head->ID = 0;
			this->attack_head->last = NULL;
			this->attack_tail = this->attack_head;
		}
		AttackNode*attack_head = NULL;
		AttackNode*attack_tail = NULL;
	};
	AttackList*attackList;
	//这个列表和mapnode表和bullet表不一样，tail指向可用的第一个，不是已用的最后一个
	
	WayFindNode*wayFindNode;
	WayFindType wayFindType;
	//血条
	Progress* progress;
	//唯一标识
	long ID;
	bool bPicChanage = false;
	Direction next_fx;
	
	//progress bg ID
	long progressBID;
	//progress fill ID
	long progressfID;
	bool canBeenScanning;
	bool canScanningAll;
	Vec2 next_poisition;
	Position*coverList;
	//sprite类型
	std::string spriteType;
	//所属scene
	Scene* scene;
	//血量
	int HP;
	int now_HP;
	//魔量
	int MP;
	//坐标
	Position* postion;
	//状态
	Status status;
	//x坐标
	int X;
	//y坐标
	int Y;
	////是否发生searchmap越界
	//bool CrossSearchMap;
	//移动时不能改变方向
	bool Movelock;
	//
	int lastX;
	MapController::MapNode*objMapNode;
	MapController::SearchMapNode *searchMapNode;
	int lastY;
	//z坐标 高度
	int Z;
	//高度 离地最高距离
	int high;
	//高度 底部距地高度
	int start_high;
	//占地高度
	int H;
	//占地宽度
	int W;
	////图片宽
	//int pw;
	////图片高
	//int ph;
	
	int offsetH;
	int harmType;
	bool bCover;
	bool canBeHarm;
	bool bMove;
	bool bMovePicChange;
	bool bAttack;
	bool bAttackPicChange;
	bool bStand;
	bool bStandPicChange;
	bool bDearCollision;
	
	
	//上张图片
	char lastPicName[MAX_PREFIX + 10];
	//当前图片
	char picName[MAX_PREFIX + 10];
	bool bUI;//是否要渲染
	//是否 被子类初始化obj图片
	bool bpic;
	////多线程 见 数据 互斥访问  临界区
	//CRITICAL_SECTION cs;
	//是否是AI
	bool bAI;
	//方向变换时占地是否跟着变
	bool bmove_cover_Rotation;
	//图片改变间隔
	int picChangeNum;
	//当前图片改变间隔计数
	int now_picChangeNum;
	//移动间隔
	int moveNum;
	//当前移动间隔
	int now_moveNum;
	int tid;//所属线程id;
	int type;
	float wScale;
	float hScale;
	float wPScale;
	float hPScale;
	//单位循环x移动距离
	float unitSpeedX;
	//单位循环y移动距离
	float unitSpeedY;

	int key[4];
	int now_key;

	//上一个方向
	Direction last_fx;
	//status
	Status last_status;
	SpriteController::SpritesNode*spritesNode = NULL;

	
	bool moving;
	//当前显示图片index
	int pic_index;
	//scale 
	bool bsclae_change;
	bool bNew = true;
	bool bClearMap;
	//0 death 1 alive -1 death but can use
	int bAlive;
	//是否显示;
	bool bShow = false;
	//是否渲染一次
	bool bOnce;
	//是否已渲染一次
	bool bhadOnce;
	bool bPlaChangePosion;
	//sprite len
	int sprites_len = 4;
	bool bShowProgress;
	bool bShowName;
	Vec2 anchorPoint;
	//player 要移动的目的地
	int aim_x;
	int aim_y;
	//PATROL
	int PATROL_x;
	int PATROL_y;
	int PATROL_range;
	int WANDERING_num_top;
	int WANDERING_num;
	int WANDERING_now_num;
	int totalpic;
	int fx_change_time;
	int fx_change_now_time;
	//方向
	Direction fx;
public:
	Obj();
	void  doChangeFX();
	void resetMove();
	void callback1();
	/*Obj(int, int, int);
	Obj(int, int, int,bool);*/
	//方法
	virtual void register_death_dear(Obj*obj,void(*fuc)(Obj*, Obj*));
	//对象公有初始化 部分
	virtual void init();
	template <class T>
	T lambda_CS(T param, std::function<T(Obj* context, T param)>func);
	//属性操作
	virtual void sendBullet(Obj*);
	virtual void setEnemy(Obj*);
	virtual void beenAttackToDie(Obj*);
	void dataDear();
	//得到player的方向和状态
	virtual void dearCollision(Obj*);
	virtual void getAIMMove();
	virtual void AIMMoveFull();
	//获得AIM新的方向
	virtual void AIMMove_getNewFX(bool init = false);
	virtual void resetSizeScale();
	virtual void afterMove();
	virtual void afterAttack();
	virtual void removeStatus(Status);
	virtual void completeAIM();
	virtual void dearSonDeath(Obj*);
	virtual void resetData();
	virtual void resetUIData();
	//设置player的目的地
	virtual void setAim(int x,int y);
	//获取postion
	virtual Position* Getpostion();
	//virtual Position* SetCoverPosition();
	virtual void PATROL_getWay();
	virtual void PATROL_set(int x, int y,int range);
	//设置postion
	virtual void Setpostion(Position);
	//获取ID
	virtual long GetID();
	//设置ID
	virtual void SetID(long);

	virtual void WANDERING();
	virtual void setWay(WayFindType);
	//获取血量
	virtual int GetHP();
	//设置血量
	virtual int SetHP(int, Obj*);
	virtual void changeFX(Direction fx);
	//获取魔量
	virtual int GetMP();
	//设置魔量
	virtual void SetMP(int);

	//获取X坐标
	virtual int GetX();
	//设置X坐标
	virtual void SetX(int);

	//获取Y坐标
	virtual int GetY();
	//设置Y坐标
	virtual void SetY(int);
	//获取X坐标
	virtual int GetZOrderY();
	//获取Z坐标
	virtual int GetZ();
	//设置Z坐标
	virtual void SetZ(int);

	//获取离地高度
	virtual int GetHigh();
	//设置离地高度
	virtual void SetHigh(int);

	//获取离地高度
	virtual int GetBottomHigh();
	//设置离地高度
	virtual void SetBottomHigh(int);

	//设置移动速度
	virtual void setMoveSpeed(int);
	virtual float getUnitSpeedY();
	virtual float getUnitSpeedX();
	//获取高度
	virtual int GetH();
	//设置高度
	virtual void SetH(int);

	//获取宽度
	virtual int GetW();
	//设置宽度
	virtual void SetW(int);
	//移除节点 要移除的源列表 要从源列表移除的ID列表 
	virtual void RemoveNode(std::vector<Obj*>*, std::vector<int>);
	//移除前要做的事
	virtual void  BeforeRemoveChildren();
	//角色死亡
	virtual void die();
	virtual void before_die();
	//角色 活动
	virtual void run(int tid);//对象运行
	//设置方向
	virtual void setDirection(Direction fx);
	//获取方向
	virtual Direction getDirection();
	//获取当前图片index
	virtual int getPicIndex();
	//设置当前图片index
	virtual void setPicIndex(int index);
	//获取屏幕坐标
	virtual Vec2 getScreenPosition();
	virtual Vec2 getScreenPositionP();
	//获取比例
	virtual Vec2 getSizeScale();
	//获取血条比例
	virtual Vec2 getProgressSizeScale();
	//暴露的调用对象方法的接口
	virtual void* Method(std::string ,void* = NULL );
	
	virtual bool canPutDown();

	virtual void dearShowObj();

	virtual string getName();

	virtual void buildName();

	virtual void buildNameColor();

	virtual void getPicName(bool bShow_ = true);

	virtual void ShowObj();

	virtual void deleteSprite();
	//废弃
	virtual void initSpriteFrame(void *p);
	
	virtual void setStatus(Status);

	virtual bool stepMove(Direction fx, Vec2 next_position,int& now_move_num,bool& crossSearchMap);

	//处理移动
	virtual void objMove();
	//obj 超出屏幕
	virtual void objOutSreen();
	virtual void dearNotShowObj();
	virtual bool unableMove(Obj*);
	virtual void InitBShowProgress();
	virtual bool InitBShowName();
	virtual void SetBShowProgress(bool bShowProgress);
	virtual void SetBShowName(bool bShowName);
	virtual bool GetBShowProgress();
	
	
	private:
		void setProbeList(int index, Vec2 vec2, vector<MapController::SynInfo*>&list, int& len, void* obj);
		void setxProbeList(int index, Vec2 vec2, void* obj = NULL);
		void setyProbeList(int index, Vec2 vec2, void* obj = NULL);

};