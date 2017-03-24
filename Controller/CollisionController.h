#pragma once
#include"Core\Controller.h"
#include"Model\Obj\Obj.h"
#include"Core\MyLock.h"

class CollisionController : public Controller {
public:
	//碰撞结束 有2中情况
	// 1.相互分离
	// 2.其中一方消失
	struct CollisionNode {
		CollisionNode *last;//上一个节点
		CollisionNode * next;//下一个节点
		bool used;//是否在使用
		Obj*Collisioner;//碰撞者
		Obj*Collisioneder;//被碰撞者
		void * PointNode;//对应的map节点，用来处理分离碰撞结束
	}*PCollisionNode;
private:
	static CollisionController * m_Instance;
	static void RemoveNode(Obj*, Obj*, void* mapNode);
	static MyLock* NodeLock;
	static CollisionNode*head;
public:
	
	CollisionController();

	static CollisionController* GetInstance();
	static void addNode(Obj*,Obj*,void*);
	static void RemoveNode(Obj*, Obj*);
	static void RemoveNode(void*mapNode, Obj*obj);
	static void RemoveNode(Obj*obj);
	static void dearCollision();
};