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
	//����

public:
	
	enum class WayFindType {
		SIMPLE,//��Ѱ·
		AIM,//Ŀ��Ŀ��Ѱ·
		PATROL,//Ѳ��
		WANDERING,//�ε�
	};
	struct WayFindNode{
	private:
		int mainFX[MAX_STORAGE_FX];//��Ӧ�õ�fx
		int len;//��ǰ����ʹ�÷����±�
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
		//��ȡ��ǰ���õ���һ��
		int getLastFX() {
			if (this->len > 1)
				return this->mainFX[len - 2];
			else
				return -1;
		}
		//��ȡ��ǰ���õ���һ�� ��ɾ����ǰ
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
	//����б��mapnode���bullet��һ����tailָ����õĵ�һ�����������õ����һ��
	
	WayFindNode*wayFindNode;
	WayFindType wayFindType;
	//Ѫ��
	Progress* progress;
	//Ψһ��ʶ
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
	//sprite����
	std::string spriteType;
	//����scene
	Scene* scene;
	//Ѫ��
	int HP;
	int now_HP;
	//ħ��
	int MP;
	//����
	Position* postion;
	//״̬
	Status status;
	//x����
	int X;
	//y����
	int Y;
	////�Ƿ���searchmapԽ��
	//bool CrossSearchMap;
	//�ƶ�ʱ���ܸı䷽��
	bool Movelock;
	//
	int lastX;
	MapController::MapNode*objMapNode;
	MapController::SearchMapNode *searchMapNode;
	int lastY;
	//z���� �߶�
	int Z;
	//�߶� �����߾���
	int high;
	//�߶� �ײ���ظ߶�
	int start_high;
	//ռ�ظ߶�
	int H;
	//ռ�ؿ��
	int W;
	////ͼƬ��
	//int pw;
	////ͼƬ��
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
	
	
	//����ͼƬ
	char lastPicName[MAX_PREFIX + 10];
	//��ǰͼƬ
	char picName[MAX_PREFIX + 10];
	bool bUI;//�Ƿ�Ҫ��Ⱦ
	//�Ƿ� �������ʼ��objͼƬ
	bool bpic;
	////���߳� �� ���� �������  �ٽ���
	//CRITICAL_SECTION cs;
	//�Ƿ���AI
	bool bAI;
	//����任ʱռ���Ƿ���ű�
	bool bmove_cover_Rotation;
	//ͼƬ�ı���
	int picChangeNum;
	//��ǰͼƬ�ı�������
	int now_picChangeNum;
	//�ƶ����
	int moveNum;
	//��ǰ�ƶ����
	int now_moveNum;
	int tid;//�����߳�id;
	int type;
	float wScale;
	float hScale;
	float wPScale;
	float hPScale;
	//��λѭ��x�ƶ�����
	float unitSpeedX;
	//��λѭ��y�ƶ�����
	float unitSpeedY;

	int key[4];
	int now_key;

	//��һ������
	Direction last_fx;
	//status
	Status last_status;
	SpriteController::SpritesNode*spritesNode = NULL;

	
	bool moving;
	//��ǰ��ʾͼƬindex
	int pic_index;
	//scale 
	bool bsclae_change;
	bool bNew = true;
	bool bClearMap;
	//0 death 1 alive -1 death but can use
	int bAlive;
	//�Ƿ���ʾ;
	bool bShow = false;
	//�Ƿ���Ⱦһ��
	bool bOnce;
	//�Ƿ�����Ⱦһ��
	bool bhadOnce;
	bool bPlaChangePosion;
	//sprite len
	int sprites_len = 4;
	bool bShowProgress;
	bool bShowName;
	Vec2 anchorPoint;
	//player Ҫ�ƶ���Ŀ�ĵ�
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
	//����
	Direction fx;
public:
	Obj();
	void  doChangeFX();
	void resetMove();
	void callback1();
	/*Obj(int, int, int);
	Obj(int, int, int,bool);*/
	//����
	virtual void register_death_dear(Obj*obj,void(*fuc)(Obj*, Obj*));
	//�����г�ʼ�� ����
	virtual void init();
	template <class T>
	T lambda_CS(T param, std::function<T(Obj* context, T param)>func);
	//���Բ���
	virtual void sendBullet(Obj*);
	virtual void setEnemy(Obj*);
	virtual void beenAttackToDie(Obj*);
	void dataDear();
	//�õ�player�ķ����״̬
	virtual void dearCollision(Obj*);
	virtual void getAIMMove();
	virtual void AIMMoveFull();
	//���AIM�µķ���
	virtual void AIMMove_getNewFX(bool init = false);
	virtual void resetSizeScale();
	virtual void afterMove();
	virtual void afterAttack();
	virtual void removeStatus(Status);
	virtual void completeAIM();
	virtual void dearSonDeath(Obj*);
	virtual void resetData();
	virtual void resetUIData();
	//����player��Ŀ�ĵ�
	virtual void setAim(int x,int y);
	//��ȡpostion
	virtual Position* Getpostion();
	//virtual Position* SetCoverPosition();
	virtual void PATROL_getWay();
	virtual void PATROL_set(int x, int y,int range);
	//����postion
	virtual void Setpostion(Position);
	//��ȡID
	virtual long GetID();
	//����ID
	virtual void SetID(long);

	virtual void WANDERING();
	virtual void setWay(WayFindType);
	//��ȡѪ��
	virtual int GetHP();
	//����Ѫ��
	virtual int SetHP(int, Obj*);
	virtual void changeFX(Direction fx);
	//��ȡħ��
	virtual int GetMP();
	//����ħ��
	virtual void SetMP(int);

	//��ȡX����
	virtual int GetX();
	//����X����
	virtual void SetX(int);

	//��ȡY����
	virtual int GetY();
	//����Y����
	virtual void SetY(int);
	//��ȡX����
	virtual int GetZOrderY();
	//��ȡZ����
	virtual int GetZ();
	//����Z����
	virtual void SetZ(int);

	//��ȡ��ظ߶�
	virtual int GetHigh();
	//������ظ߶�
	virtual void SetHigh(int);

	//��ȡ��ظ߶�
	virtual int GetBottomHigh();
	//������ظ߶�
	virtual void SetBottomHigh(int);

	//�����ƶ��ٶ�
	virtual void setMoveSpeed(int);
	virtual float getUnitSpeedY();
	virtual float getUnitSpeedX();
	//��ȡ�߶�
	virtual int GetH();
	//���ø߶�
	virtual void SetH(int);

	//��ȡ���
	virtual int GetW();
	//���ÿ��
	virtual void SetW(int);
	//�Ƴ��ڵ� Ҫ�Ƴ���Դ�б� Ҫ��Դ�б��Ƴ���ID�б� 
	virtual void RemoveNode(std::vector<Obj*>*, std::vector<int>);
	//�Ƴ�ǰҪ������
	virtual void  BeforeRemoveChildren();
	//��ɫ����
	virtual void die();
	virtual void before_die();
	//��ɫ �
	virtual void run(int tid);//��������
	//���÷���
	virtual void setDirection(Direction fx);
	//��ȡ����
	virtual Direction getDirection();
	//��ȡ��ǰͼƬindex
	virtual int getPicIndex();
	//���õ�ǰͼƬindex
	virtual void setPicIndex(int index);
	//��ȡ��Ļ����
	virtual Vec2 getScreenPosition();
	virtual Vec2 getScreenPositionP();
	//��ȡ����
	virtual Vec2 getSizeScale();
	//��ȡѪ������
	virtual Vec2 getProgressSizeScale();
	//��¶�ĵ��ö��󷽷��Ľӿ�
	virtual void* Method(std::string ,void* = NULL );
	
	virtual bool canPutDown();

	virtual void dearShowObj();

	virtual string getName();

	virtual void buildName();

	virtual void buildNameColor();

	virtual void getPicName(bool bShow_ = true);

	virtual void ShowObj();

	virtual void deleteSprite();
	//����
	virtual void initSpriteFrame(void *p);
	
	virtual void setStatus(Status);

	virtual bool stepMove(Direction fx, Vec2 next_position,int& now_move_num,bool& crossSearchMap);

	//�����ƶ�
	virtual void objMove();
	//obj ������Ļ
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