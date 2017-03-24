#pragma once
#include"Obj.h"
#include"Model\Obj\Weapon\Weapon.h"
class CanSendBulletObj {
public:
	enum class BulletType {
		XMISSILE = 0x0001,
		MINES = 0x0002,
	};
	struct BulletNode {
		int ID;
		BulletNode*next;
		BulletNode*last;
		Weapon *node;
	};
	struct BulletListNode {
		int now_bullet_num;
		int bullet_num;
		BulletNode*add_(Weapon*weapon) {
			this->tail->ID = weapon->ID;
			this->tail->node = weapon;
			this->now_bullet_num++;
			auto tmp = static_add(this->head,this->tail);
			this->tail->ID = 0;
			return tmp;
		}
		void delete_(BulletNode*p) {
			this->now_bullet_num--;
			static_delete(p,this->head,this->tail);
		}
		void init_() {
			this->head = (BulletNode*)malloc(sizeof(BulletNode));
			this->head->ID = 0;
			this->head->next = NULL;
			this->head->last = NULL;
			this->tail = this->head;
		}
		BulletListNode() {
			this->init_();
		}
		BulletNode * head;
		BulletNode * tail;
	};
	
	bool canSendBullet;
	map<BulletType, BulletListNode *>bulletNodeList;
	//Weapon *bulletList[MAX_BULLET];
	virtual void sendBullet(Obj*);
	virtual BulletListNode* findBulletList(BulletType);
	virtual BulletListNode* hasOwnBulletList(BulletType);
	virtual void bulletNodeList_add(BulletType, BulletListNode*);
	virtual void afterAttack(Obj*);
	virtual void dearSendBullet(Obj*);
	virtual void doSendBullet(Obj*);
	virtual void dearBulletDeath(Obj*);
	virtual void setDirection(Direction fx);
	virtual void setStatus(Status);
	virtual BulletListNode* CreateBulletListNode(BulletType);
	template<class classT, class enumT,class objT>
	 static Weapon* bullet_add(objT*self, int x, int y, int type, int fx = -1, bool reback = false);
	template<class classT, class enumT,class objT>
	//�Ǹ��ڵ� ���� ���� �Ƿ��ʼ������ reback �Ƿ��б�ع����� ����һ��weapon ��Ϊ��ǰ�¼����weapon
	 static Weapon* bulletList_add(objT*self,BulletListNode*,int x,int y,int type,int fx = -1,bool reback = false);
	void test(Obj*obj);
	 virtual const int getBulletTopNum(BulletType);
	 virtual int getBulletNowNum(BulletType);
};