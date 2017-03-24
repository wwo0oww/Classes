#include"Brike.h"
Brike::Brike() {
	
}
void Brike::init() {
	
	switch ((Type)this->type)
	{
	case Brike::Type::STEEL:
		
		this->bAttack = false;
		this->bAttackPicChange = false;
		this->bMove = false;
		this->bMovePicChange = false;
		this->bStand = true;
		this->bStandPicChange = false;
		this->bOnce = true;
		this->high = 100;
		this->start_high = 0;
		this->bShowProgress = false;
		break;
	default:
		break;
	}

	Building::init();
}
Brike::Brike(int type, int x, int y, bool bAI) {
	Brike((Type)type,x,y, bAI);
}
Brike::Brike(Type type,int x,int y, bool bAI) {
	this->X = x;
	this->Y = y;
	this->type = (int)type;
	this->bAI = true;
	this->status = Status::STAND;
	this->fx = Direction::DOWN;
	this->init();
	
}
//角色死亡
void Brike::die() {
	Building::die();
}

int Brike::GetZOrderY() {
	switch (this->type)
	{
	case (int)Brike::Type::STEEL:
		return this->Y - 1;
		break;
	default:
		break;
	}
}
//角色 活动
void Brike::run(int tid) {
	Building::run(tid);
}//对象运行
					   //暴露的调用对象方法的接口
void* Brike::Method(std::string methName, void* param) {
	
	return Building::Method(methName, param);
}