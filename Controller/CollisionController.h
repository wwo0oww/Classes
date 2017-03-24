#pragma once
#include"Core\Controller.h"
#include"Model\Obj\Obj.h"
#include"Core\MyLock.h"

class CollisionController : public Controller {
public:
	//��ײ���� ��2�����
	// 1.�໥����
	// 2.����һ����ʧ
	struct CollisionNode {
		CollisionNode *last;//��һ���ڵ�
		CollisionNode * next;//��һ���ڵ�
		bool used;//�Ƿ���ʹ��
		Obj*Collisioner;//��ײ��
		Obj*Collisioneder;//����ײ��
		void * PointNode;//��Ӧ��map�ڵ㣬�������������ײ����
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