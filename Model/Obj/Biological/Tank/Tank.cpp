#include"Model\Obj\Biological\Tank\Tank.h"
#include"Controller\SpriteController.h"
#include"Model\data.h"
#include"malloc.h"
#include"Model\Obj\Weapon\Weapon.h"
#include"Model\Obj\Weapon\Missile.h"
#include"Controller\ObjController.h"
#include"Controller\MapBuildController.h"
#include"Controller\MainSceneController.h"
#include"Controller\TouchEventController.h"
#include"Core\UI\Message.h"
bool Tank::bInitSpriteFrame = false;
int Tank::num = 0;
Tank::Tank(Type type, int x, int y, bool bAI ):CanScanningObj(this), CanAttackObj(this) {
	CanScanningObj::initAttackObj(CanAttackObj::attackObj);
	this->X = x;
	this->Y = y;
	this->type = int(type);
	this->bOnce = false;
	//this->status = bAI?Status(Status::MOVE| Status::STAND): Status::STAND;
	this->status = Status::STAND;
	this->fx = Direction::DOWN;
	this->bAI = bAI;
	this->init();
	this->high = 5;
	this->start_high = 3;
	this->canSendBullet = true;

}
void Tank::sendBullet(Obj*obj) {
	CanSendBulletObj::sendBullet(obj);
}
void Tank::g_dearSonDeath(Obj*obj,Obj*param) {
	if(obj != NULL)
	obj->dearSonDeath(param);
}
Tank::Tank(int type, int x, int y, bool bAI) :CanScanningObj(this), CanAttackObj(this){
	Tank((Type)type, x, y, bAI);
}
void Tank::dearSonDeath(Obj*obj) {
	this->dearBulletDeath(obj);
	Biological::dearSonDeath(obj);
}
void Tank::afterAttack() {
	CanAttackObj::resetAttackTime();
	CanSendBulletObj::afterAttack(this);
}
bool Tank::canAttack() {
	return CanAttackObj::CanAttack();
}
void Tank::resetAttack() {
	CanAttackObj::resetAttackTime();
}
void Tank::doAttack(int x, int y) {
	this->sendBullet(this);
	this->bullet_aim_x = x;
	this->bullet_aim_y = y;
}
void Tank::doSendBullet(Obj*obj) {
	int X = this->X, Y = this->Y;
	Weapon* weapon;
	switch ((Type)this->type)
	{
	case Type::STRONG:
		Weapon *p;

		switch (this->fx)
		{
		case Direction::UP:
			Y += 1;
			break;
		case Direction::DOWN:
			Y -= 1;
			break;
		case Direction::RIGHT:
			X += 1;
			break;
		case Direction::LEFT:
			X -= 1;
			break;
		default:
			break;
		}
		//this->test(this);
		
			weapon = CanSendBulletObj::bullet_add<Missile, Missile::Type, Tank>(this, X, Y, int(Missile::Type::XMISSILE), this->getDirection());
			if (weapon != NULL) {
				if (this->bullet_aim_x != -1) {

					((Missile*)weapon)->setSideWayAim(this->bullet_aim_x, this->bullet_aim_y);
					this->bullet_aim_x = -1;
					this->bullet_aim_y = -1;
				}
				if (this->ID == ObjController::PlayerID)
					((Missile*)weapon)->setSideWayAim(TouchEventController::clickPosition_x, TouchEventController::clickPosition_y);
				weapon->parent = this;
				weapon->register_death_dear(this, g_dearSonDeath);
				this->afterAttack();
			}
		
		//CanSendBulletObj::bullet_add<Missile, Missile::Type>(this, X, Y, int(Missile::Type::XMISSILE), this->getDirection());
		/*BulletListNode * bulletListNode = NULL;
		BulletType bulletType = (BulletType)pow(2, int(Missile::Type::XMISSILE));
		if ((bulletListNode == this->hasOwnBulletList(bulletType)) == NULL) {
			bulletListNode = this->CreateBulletListNode(bulletType);
		}
		this->bulletList_add<Missile, Missile::Type>(bulletListNode,X,Y,int( Missile::Type::XMISSILE), this->getDirection());
		*/
		/*bulletListNode->bulletList[bulletListNode->now_bullet_num] = (Weapon*)ObjController::create<Missile, Missile::Type>(Missile::Type::XMISSILE, X, Y, true, this->getDirection());
		p = bulletListNode->bulletList[bulletListNode->now_bullet_num];
		p->harmType = this->harmType;
		p->parent = this;
		p->bullet_index = this->now_bullet_num;
		this->now_bullet_num++;*/
		break;
	default:
		break;
	}
}
void Tank::dearCollision(Obj*obj) {
}
void Tank::init() {
	this->harmType = 2;
	switch ((Type)this->type)
	{
	case Tank::Type::STRONG:
		this->canBeHarm = true;
		
		this->picChangeNum = 6;
		this->moveNum = 6;
		this->bMove = true;
		this->bMovePicChange = true;
		this->bAttack = true;
		this->bAttackPicChange = true;
		this->bStand = true;
		this->bStandPicChange = true;
		this->HP = 100;
		this->bShowName = true;
		this->offsetH = 4;
		Tank::num++;
		break;
	default:
		break;
	}

	Biological::init();
}

void Tank::dearShowObj() {
	Biological::dearShowObj();
}
void Tank::die() {

	Tank::num--;
	Biological::die();

}
void Tank::ShowObj() {
	Biological::ShowObj();
}
void Tank::setDirection(Direction fx) {
	if (this->fx != fx) {
		CanSendBulletObj::setDirection(fx);
		Biological::setDirection(fx);
	}
	
}

void Tank::setStatus(Status status) {
	if (this->status != status) {
		CanSendBulletObj::setStatus(status);
		Biological::setStatus(status);
	}
}

Direction Tank::getDirection() {
	return Biological::getDirection();
}
void Tank::run(int tid) {
	if (this->ID != ObjController::PlayerID) {
		//this->sendBullet(this);
	}
	CanSendBulletObj::dearSendBullet(this);
	CanAttackObj::run();
	CanScanningObj::run();
	Biological::run(tid);

}
int Tank::GetZOrderY() {
	switch (this->type)
	{
	case (int)Tank::Type::STRONG:
		return this->Y - 2;
		break;
	default:
		break;
	}
	
}
void Tank::initSpriteFrame(void* SpriteFrameInfo) {
	Biological::initSpriteFrame(SpriteFrameInfo);
}
//暴露的调用对象方法的接口
void* Tank::Method(std::string methName, void* param) {
	
	Biological::Method(methName, param);
	return NULL;
}