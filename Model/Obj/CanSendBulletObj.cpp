#include"CanSendBulletObj.h"
#include"Controller\ObjController.h"

#include"Model\Obj\Weapon\Missile.h"
#include"Model\Obj\Biological\Tank\Tank.h"
#include"Model\Obj\Biological\Soldier\Soldier.h"
void CanSendBulletObj::afterAttack(Obj*obj) {
	this->canSendBullet = true;
	obj->removeStatus(Status::ATTACK);
}
void CanSendBulletObj::dearBulletDeath(Obj*obj_) {
	
	if (obj_->type >= 20 && obj_->type < 30)
	{
		Weapon* obj = (Weapon*)obj_;
		BulletNode * p = (BulletNode*)obj->bullet_index;
		if (p == NULL)return;
		BulletListNode* tmpList = this->findBulletList((BulletType)(int)pow(2,obj->type - 20));
		tmpList->delete_(p);
		
		
	}
}

CanSendBulletObj::BulletListNode* CanSendBulletObj::findBulletList(BulletType type) {
	return this->bulletNodeList.find(type)->second;
}

CanSendBulletObj::BulletListNode* CanSendBulletObj::hasOwnBulletList(BulletType type) {
	auto result =  this->bulletNodeList.find(type);
	return result != this->bulletNodeList.end()? result->second:NULL;
}

void CanSendBulletObj::bulletNodeList_add(BulletType type, BulletListNode*node) {
	this->bulletNodeList.insert(pair<BulletType,BulletListNode*>(type,node));
}



void CanSendBulletObj::dearSendBullet(Obj*obj) {
	if (obj->status&Status::ATTACK) {
		if (obj->now_picChangeNum != 1)return;
		bool bSend = false;
		switch (obj->fx)
		{
		case Direction::UP:
			if (obj->pic_index == PrefixInfo::prefixData->prefixList[obj->type]->index_up_attack) {
				bSend = true;
			}
			break;
		case Direction::DOWN:
			if (obj->pic_index == PrefixInfo::prefixData->prefixList[obj->type]->index_down_attack) {
				bSend = true;
			}
			break;
		case Direction::RIGHT:
			if (obj->pic_index == PrefixInfo::prefixData->prefixList[obj->type]->index_right_attack) {
				bSend = true;
			}
			break;
		case Direction::LEFT:
			if (obj->pic_index == PrefixInfo::prefixData->prefixList[obj->type]->index_left_attack) {
				bSend = true;
			}
			break;
		default:
			break;
		}
		if (bSend) {
			this->doSendBullet(obj);
		}
	}
}

void CanSendBulletObj::doSendBullet(Obj*obj) {
}

int CanSendBulletObj::getBulletNowNum(BulletType type) {
	switch (type) {
	case BulletType::MINES:
		return 5;
		break;
	case BulletType::XMISSILE:
		return MAX_BULLET;
		break;
	}
}

const int CanSendBulletObj::getBulletTopNum(BulletType type) {
	switch (type) {
	case BulletType::MINES:
		return MAX_MINES;
		break;
	case BulletType::XMISSILE:
		return MAX_XMISSILE;
		break;
	}
}
CanSendBulletObj::BulletListNode* CanSendBulletObj::CreateBulletListNode(BulletType bulletType) {
	BulletListNode* bulletListNode = (BulletListNode*)malloc(sizeof(BulletListNode));
	bulletListNode->init_();
	this->bulletNodeList_add(bulletType, bulletListNode);
	bulletListNode->bullet_num = this->getBulletNowNum(bulletType);
	bulletListNode->now_bullet_num = 0;
	return bulletListNode;
}
template<class classT, class enumT,class objT>
Weapon* CanSendBulletObj::bulletList_add(objT*self,BulletListNode* bulletListNode, int x, int y, int type, int fx, bool reback) {
	Weapon*node = NULL;
	BulletNode*bulletNode = NULL;
	if (bulletListNode->now_bullet_num < bulletListNode->bullet_num) {
		if (fx != -1) {
			node = (Weapon*)ObjController::create<classT, enumT>(enumT(type), x, y, true, (Direction)fx);
		}
		else {
			node = (Weapon*)ObjController::create<classT, enumT>(enumT(type), x, y, true);
		}
		node->harmType = self->harmType;
		node->parent = self;
		
	}
	else if (reback&&bulletListNode->now_bullet_num >= bulletListNode->bullet_num) {
		bulletListNode->head->node->bAlive = -1;
		bulletListNode->head->node->bullet_index = NULL;
		bulletListNode->delete_(bulletListNode->head);
		
		
		if (fx != -1) {
			node = (Weapon*)ObjController::create<classT, enumT>(enumT(type), x, y, true, (Direction)fx);
		}
		else {
			node = (Weapon*)ObjController::create<classT, enumT>(enumT(type), x, y, true);
		}
		node->harmType = self->harmType;
		node->parent = self;
		node->bullet_index = node;
	}
	if (node == NULL)return NULL;
	bulletNode = bulletListNode->add_(node);
	
	
	node->bullet_index = bulletNode;
	
	return node;
}

template<class classT, class enumT,class objT>
Weapon* CanSendBulletObj::bullet_add(objT* self,int x, int y, int type, int fx , bool reback ) {
	BulletListNode * bulletListNode = NULL;
	BulletType bulletType = (BulletType)(int)pow(2, int(type - 20));
	if ((bulletListNode = self->hasOwnBulletList(bulletType)) == NULL) {
		bulletListNode = self->CreateBulletListNode(bulletType);
	}
	return self->bulletList_add<classT, enumT, objT>(self,bulletListNode, x, y, type, fx,reback);

}

void CanSendBulletObj::sendBullet(Obj*obj) {
	if (!this->canSendBullet) return;
	obj->setStatus(Status::ATTACK);
	
	this->canSendBullet = false;
}
void CanSendBulletObj::setStatus(Status status) {
	this->canSendBullet = true;
}
void CanSendBulletObj::setDirection(Direction fx) {
	this->canSendBullet = true;
}
void  CanSendBulletObj::test(Obj*obj) {
	CanSendBulletObj::bullet_add<Missile, Missile::Type, Tank>((Tank*)obj, 1, 1, int(Missile::Type::XMISSILE), -1, true);
	CanSendBulletObj::bullet_add<Missile, Missile::Type, Soldier>((Soldier*)obj, 1, 1, int(Missile::Type::MINES), -1, true);
}