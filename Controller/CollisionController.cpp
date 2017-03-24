#include"CollisionController.h"
MyLock* CollisionController::NodeLock = new MyLock();
CollisionController::CollisionNode* CollisionController::head = NULL;
CollisionController* CollisionController::m_Instance = new CollisionController();
CollisionController::CollisionController() {
	
}
CollisionController* CollisionController::GetInstance() {
	return m_Instance;
}
void CollisionController::dearCollision() {
	
	CollisionNode* p = head;
	if (head == NULL)return;
	while (p->used) {
		if(p->Collisioneder->bDearCollision)
		p->Collisioneder->dearCollision(p->Collisioner);
		if (p->Collisioner->bDearCollision)
		p->Collisioner->dearCollision(p->Collisioneder);
		auto tmp = p;
		RemoveNode(p->Collisioner, p->Collisioneder);
		
		if (p->next == NULL) {
			break;
		}
		p = tmp->next;
	}
}

void CollisionController::addNode(Obj*collisioner, Obj*collisioneder,void * pointNode) {
	
#ifdef DEBUG
	CCLOG("addNode start");
#endif
	NodeLock->Lock();
	if (head == NULL) {
		head = (CollisionNode*)malloc(sizeof(CollisionNode));
		head->next = NULL;
		head->used = false;
	}
	CollisionNode* p = head;
	while (p->used) {
		if ((collisioner == p->Collisioneder&&collisioneder==p->Collisioner)
			|| (collisioner == p->Collisioner&&collisioneder == p->Collisioneder)) {
			NodeLock->UnLock();
			return;
		}
		if (p->next == NULL) {
			break;
		}
		p = p->next;
	}
	//��ǰ ���� ��һ��������
	if (p->next == NULL&&p->used) {
		p->next = (CollisionNode*)malloc(sizeof(CollisionNode));
		p->next->next = NULL;
		p->next->used = false;
		p = p->next;
	}
	//��ǰ û�� ��һ������
	//��ǰ û�� ��һ��������
	p->used = true;
	p->Collisioner = collisioner;
	p->Collisioneder = collisioneder;
	p->PointNode = pointNode;
	NodeLock->UnLock();
#ifdef DEBUG
	CCLOG("addNode end");
#endif
}

void CollisionController::RemoveNode(Obj*collisioner, Obj*collisioneder) {
	RemoveNode(collisioner, collisioneder,NULL);
}

void CollisionController::RemoveNode(void*mapNode, Obj*obj) {
	RemoveNode(obj,NULL,mapNode);
}

void CollisionController::RemoveNode(Obj*obj) {
	RemoveNode(obj,NULL,NULL);
}

void CollisionController::RemoveNode(Obj*collisioner, Obj*collisioneder,void* pointNode) {
	
#ifdef DEBUG
	CCLOG("RemoveNode start");
#endif
	NodeLock->Lock();
	if (head == NULL) {
		NodeLock->UnLock();
		return;
	}
	CollisionNode* p = head;
	while (p != NULL) {
		if (!p->used) {
			p = p->next;
			continue;
		}
		//��һ�������� ����map�ڵ�
		if (pointNode != NULL) {
			if (p->PointNode == pointNode&&(p->Collisioneder == collisioner||p->Collisioner == collisioner)) {
				p->used = false;
				break;
			}
			//������ڶ����� ����
			p = p->next;
			continue;
		}
		//�ڶ���������������һ����ʧ
		if (collisioneder == NULL) {
			if (p->Collisioneder == collisioner || p->Collisioner == collisioner) {
				p->used = false;
			}
			//��һ����ʧ �Ͳ���������� ����
			p = p->next;
			continue;
		}
		//������������
		if ((p->Collisioner == collisioner&&p->Collisioneder == collisioneder)|| p->Collisioner == collisioneder&&p->Collisioneder == collisioner ) {
			p->used = false;
			break;
		}
		p = p->next;
	}
	NodeLock->UnLock();
#ifdef DEBUG
	CCLOG("RemoveNode end");
#endif
}
