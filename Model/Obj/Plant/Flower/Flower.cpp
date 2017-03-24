#include"Flower.h"
Flower::Flower() {
}
int Flower::GetZOrderY() {
	switch (this->type)
	{
	case (int)Type::FRANGIPANI:
		return this->Y ;
		break;
	case (int)Type::XFLOWER:
		return this->Y ;
	default:
		break;
	}
	return this->Y -1;
}
void Flower::setDirection(Direction fx) {
	if (fx != this->fx)
		this->bsclae_change = true;
	Plant::setDirection(fx);
}
void Flower::init() {

	switch ((Type)this->type)
	{
	case Flower::Type::FRANGIPANI:
		
		this->bAttack = false;
		this->bAttackPicChange = false;
		this->bMove = false;
		this->bMovePicChange = false;
		this->bStand = true;
		this->bStandPicChange = false;
		this->bOnce = true;
		this->high = 10;
		this->start_high = 0;
		this->bShowProgress = false;
		this->HP = 100;
		this->anchorPoint = Vec2(0.5, 0);
		break;
	case Flower::Type::XFLOWER:
		
		this->bAttack = true;
		this->bAttackPicChange = true;
		this->moveNum = 12;
		this->bMove = true;
		this->picChangeNum = 12;
		this->status = Status(Status::STAND|Status::ATTACK);
		this->bMovePicChange = true;
		this->bStand = true;
		this->bStandPicChange = true;
		this->bOnce = false;
		this->high = 6;
		this->start_high = 0;
		
		break;
	default:
		break;
	}

	Plant::init();
}
Flower::Flower(Type type, int x, int y,bool bAI) {
	this->X = x;
	this->Y = y;
	this->type = (int)type;
	this->bAI = bAI;
	this->status = Status::STAND;
	this->fx = Direction::DOWN;
	this->init();

}
Flower::Flower(int type,int x, int y) {
	Flower((Type)type, x, y, true);
}

void Flower::die() {
	Plant::die();
}
//角色 活动
void Flower::run(int tid) {
	
	Plant::run(tid);
}//对象运行
 //暴露的调用对象方法的接口
void* Flower::Method(std::string methName, void* param) {
	return Plant::Method(methName, param);

}