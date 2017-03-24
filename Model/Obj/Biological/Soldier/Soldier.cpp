#include"Soldier.h"
#include"Controller\ObjController.h"
#include"Model\Obj\Weapon\Weapon.h"
#include"Model\Obj\Weapon\Missile.h"
#include"Controller\TouchEventController.h"
Soldier::Soldier() {
}
int Soldier::GetZOrderY() {
	switch (this->type)
	{
	case (int)Type::LANCER:
		return this->Y;
		break;
	default:
		break;
	}
	return this->Y - 1;
}
void Soldier::init() {
	this->canBeHarm = true;
	switch ((Type)this->type)
	{
	case Soldier::Type::LANCER:
		
		this->bAttack = true;
		this->bAttackPicChange = true;
		this->bMove = true;
		this->bMovePicChange = true;
		this->bStand = true;
		this->bStandPicChange = true;
		this->high = 10;
		this->start_high = 0;
		this->bShowProgress = true;
		this->HP = 100;
		this->now_HP = 100;
		this->picChangeNum = 6;
		this->moveNum = 6;
		this->anchorPoint = Vec2(0.5,0);
		
		break;
	
	default:
		break;
	}
	this->bShowName = true;
	Biological::init();
}

void Soldier::sendBullet(Obj*obj) {
	CanSendBulletObj::sendBullet(obj);
}
Soldier::Soldier(Type type, int x, int y, bool bAI) {
	this->X = x;
	this->Y = y;
	this->type = (int)type;
	this->bAI = bAI;
	this->status = Status::STAND;//Status::STAND;//Status(Status::STAND|Status::MOVE);
	this->fx = Direction::DOWN;
	this->init();

}
void Soldier::picChange() {
	this->bsclae_change = true;

}
void Soldier::dearSonDeath(Obj*obj) {
	this->dearBulletDeath(obj);
	Biological::dearSonDeath(obj);
}
void Soldier::afterAttack() {
	CanSendBulletObj::afterAttack(this);
}
void Soldier::doSendBullet(Obj*obj) {
	
	int x = TouchEventController::clickPosition_x;
	int y = TouchEventController::clickPosition_y;
	Vec2 cover = CoverInfo::coverData->coverData[int(type)];
	Weapon *weapon = NULL;
	switch ((Type)this->type)
	{
	case Type::LANCER:
		weapon = CanSendBulletObj::bullet_add<Missile, Missile::Type,Soldier>(this,TouchEventController::clickPosition_x, TouchEventController::clickPosition_y, int(Missile::Type::MINES), -1,true);
		if (weapon != NULL) {
			weapon->parent = this;
		}
		break;
	default:
		break;
	}
}
void Soldier::setDirection(Direction fx) {
	if (fx != this->fx) {
		this->picChange();
		CanSendBulletObj::setDirection(fx);
		Biological::setDirection(fx);
	}
}

void Soldier::setStatus(Status status) {
	if (this->status != status) {
		this->picChange();
		CanSendBulletObj::setStatus(status);
		Biological::setStatus(status);
	}
}


//void Soldier::changeFX(Direction fx) {
//	Biological::changeFX(fx);
//}
Soldier::Soldier(int type, int x, int y) {
	Soldier((Type)type, x, y, true);
}
//Position* Soldier::SetCoverPosition() {
//	int index = 0;
//	switch (type)
//	{
//	case int(Soldier::Type::LANCER) :
//		coverList = (Position*)malloc
//		((this->W*this->H)*sizeof(Position));
//		coverList[0].x = 0;
//		coverList[0].y = -2;
//
//		coverList[1].x = 0;
//		coverList[1].y = -3;
//
//		coverList[2].x = 1;
//		coverList[2].y = -2;
//
//		coverList[3].x = 1;
//		coverList[3].y = -3;
//
//		return coverList;
//		break;
//	
//	default:
//		break;
//	}
//	return NULL;
//}
//角色死亡
void Soldier::die() {
	Biological::die();
}
//角色 活动
void Soldier::run(int tid) {
	this->dearSendBullet(this);
	Biological::run(tid);
}//对象运行
 //暴露的调用对象方法的接口
void* Soldier::Method(std::string methName, void* param) {
	return Soldier::Method(methName, param);

}