#include"Missile.h"
#include"Controller\ObjController.h"
Missile::Missile(Type type, int x, int y, bool bAI,Direction fx ) {
	this->X = x;
	this->Y = y;
	this->type = (int)type;
	this->bAI = bAI;
	this->key[0] = 1;
	this->key[2] = 1;
	this->setDirection(fx);
	this->harm = 2;
	this->init();
	
}
void Missile::init() {

	switch ((Type)this->type)
	{
	case Missile::Type::XMISSILE:
		this->offsetH = 200;
		
		this->W = CoverInfo::coverData->coverData[this->type].x;
		this->H = CoverInfo::coverData->coverData[this->type].y;
		CanSideWayObj::start_index = 8;
		this->bAttack = true;
		this->bAttackPicChange = true;
		this->bMove = true;
		this->bMovePicChange = true;
		this->bStand = false;
		this->bStandPicChange = false;
		this->bOnce = false;
		this->high = 4;
		this->start_high = 2;
		this->bShowProgress = false;
		this->picChangeNum = 3;
		this->moveNum = 1;
		this->max_move_n = 50;
		this->now_move_n = 0;
		this->status = Status::MOVE;
		this->harm = 10;
		this->harm_x_range = 3;
		this->harm_y_range = 3;
		break;
	case Type::MINES:
		this->harm = 5;
		this->canBeenScanning = false;
		/*this->offsetH = 1;*/
		this->W = CoverInfo::coverData->coverData[this->type].x;
		this->H = CoverInfo::coverData->coverData[this->type].y;
		this->bDearCollision = true;
		this->bAttack = true;
		this->bAttackPicChange = true;
		this->bMove = false;
		this->bMovePicChange = true;
		this->bStand = true;
		this->bStandPicChange = true;
		this->bOnce = false;
		this->high = 1;
		this->start_high = 0;
		this->bShowProgress = false;
		this->picChangeNum = 3;
		this->anchorPoint = Vec2(0.5, 0);
		this->status = Status::STAND;
		this->harm_x_range = 3;
		this->harm_y_range = 3;
		this->bShowName = true;
		break;
	default:
		break;
	}

	Weapon::init();
}


void Missile::boom(Obj*obj) {
	this->status = Status::ATTACK;
	this->pic_index = 0;
	this->bMove = false;
	/*if(this->spritesNode->list[0] != NULL)
	((CCSprite*)this->spritesNode->list[0])->setRotation(0);*/
	this->bUI = false;
	switch ((Type)this->type)
	{
	case Type::XMISSILE:
		this->X = this->next_poisition.x;
		this->Y = this->next_poisition.y;
		CanSideWayObj::sideWayFX_x = (Direction)-1;
		CanSideWayObj::sideWayFX_y = (Direction)-1;
		MapController::ClearMap(this);
		if (int(obj)!= -1&&obj != NULL) {
			this->X = obj->X;
			this->Y = obj->Y;
		}
   		this->bsclae_change = true;
		
		break;
	case Type::MINES:
		MapController::ClearMap(this);

		this->bsclae_change = true;
		
		break;
	default:
		break;
	}
}
//void Missile::before_die() {
//	//CanSideWayObj::before_die(this);
//	Weapon::before_die();
//}
//void Missile::completeAIM() {
//	//CanSideWayObj::completeAIM(this);
//	Weapon::completeAIM();
//}

void Missile::dearHarm() {
	if (this->status == Status::ATTACK) {
		switch (this->type) {
		case (int)Type::XMISSILE:
				CanHarmObj::dearHarm(this,this->X, this->Y - 2);
			break;
		case (int)Type::MINES:
				CanHarmObj::dearHarm(this,this->X, this->Y);
			break;
		}

	}
}

bool Missile::stepMove(Direction fx, Vec2 next_position, int& now_move_num, bool& crossSearchMap) {
	if (CanSideWayObj::canSideWay&&CanSideWayObj::isStatSideWay(true)) {
		
		if (this->bShow) {
			int rotation = -1;
			switch ((Type)this->type) {

			case Type::XMISSILE:
				
				if (CanSideWayObj::sideWayFX_x == Direction::RIGHT&&CanSideWayObj::sideWayFX_y == Direction::DOWN) {
					rotation = 45;
				}
				else if (CanSideWayObj::sideWayFX_x == Direction::RIGHT&&CanSideWayObj::sideWayFX_y == Direction::UP) {
					rotation = 315;
				}
				else if (CanSideWayObj::sideWayFX_x == Direction::LEFT&&CanSideWayObj::sideWayFX_y == Direction::DOWN) {
					rotation = 135;
				}
				else if (CanSideWayObj::sideWayFX_x == Direction::LEFT&&CanSideWayObj::sideWayFX_y == Direction::UP) {
					rotation = 225;
				}
				else if (CanSideWayObj::sideWayFX_x == Direction::LEFT) {
					rotation = 180;
				}
				else if (CanSideWayObj::sideWayFX_x == Direction::RIGHT) {
					rotation = 0;
				}
				else if (CanSideWayObj::sideWayFX_y == Direction::UP) {
					rotation = 270;
				}
				else if (CanSideWayObj::sideWayFX_y == Direction::DOWN) {
					rotation = 90;
				}
				if(rotation != -1)
				((CCSprite*) this->spritesNode->list[0])->setRotation(rotation);
				break;
			}
		}
		return CanSideWayObj::stepMove(this, fx, next_position, now_move_num, crossSearchMap);
	}
	return Weapon::stepMove( fx, next_position, now_move_num, crossSearchMap);
}
//角色 活动
void Missile::run(int tid) {
	//CanSideWayObj::run();
	Weapon::run(tid);
}//对象运行
void Missile::objMove() {
	
	if (CanSideWayObj::canSideWay&&CanSideWayObj::isStatSideWay(false)) {
		CanSideWayObj::doSideWay(this);
		
	}else
	Weapon::objMove();
}
void Missile::setSideWayAim(int x, int y) {
	CanSideWayObj::setSideWayAim(x,y);
}
 //暴露的调用对象方法的接口
void* Missile::Method(std::string methName, void* param) {
	return Weapon::Method(methName, param);

}
void Missile::dearCollision(Obj*obj) {
	if (this->status&Status::ATTACK)return;
	if (this->harmType != obj->harmType) {
		this->boom(obj);
	}
}