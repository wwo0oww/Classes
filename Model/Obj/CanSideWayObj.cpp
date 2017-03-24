#include"CanSideWayObj.h"
#include"Controller\GameController.h"
void CanSideWayObj::setSideWayAim(int x, int y) {
	this->canSideWay = true;
	this->aim_x = x;
	this->aim_y = y;
	this->now_start_index = 0;
}
bool CanSideWayObj::stepMove(Obj * self,Direction fx, Vec2 next_position_, int& now_move_num, bool& crossSearchMap_) {
	//后台坐标 变化
	//可移动now_move_num = mvoenum 重新赋值
	//在减为0前 表示此次移动一格还没结束，继续移动
	//变为 0 表示移动一格移动完，将now_move_num = -1，表示不可移动 后台坐标重新变化，
	if (!self->bMove)
		return false;

	if (now_move_num > 0) {

		now_move_num--;
		if (self->spritesNode != NULL) {
			//加判断是因为，当一格没移动完，移动状态变化了，则会变为-1，且此时不能移动
			Vec2 tmp = self->getScreenPosition();
			if (self->bAI || !GameController::positionSreenCenter(self->next_poisition, Vec2(1.0 / self->moveNum, 1.0 / self->moveNum), self->now_moveNum == 0/*this->now_moveNum == 0 true*//*注释内容是为了使屏幕镜头一个个移动 但是这样会导致物体移动时一卡一卡*/)) {
				if (this->sideWayFX_y == Direction::DOWN)
				{
					tmp.y -= (self->moveNum - now_move_num)* self->unitSpeedY;
				}
				else if (this->sideWayFX_y == Direction::UP) {
					tmp.y += (self->moveNum - now_move_num) * self->unitSpeedY;
				}
				if (this->sideWayFX_x == Direction::RIGHT) {
					tmp.x += (self->moveNum - now_move_num) * self->unitSpeedX;
				}else if (this->sideWayFX_x == Direction::LEFT)
				{
					tmp.x -= (self->moveNum - now_move_num) * self->unitSpeedX;
				}
				((CCSprite*)self->spritesNode->list[0])->setPosition(tmp);


			}
		}

	}
	//移动完了一格，将后台信息同步
	if (now_move_num == 0) {
		self->X = next_position_.x;
		self->Y = next_position_.y;
		if (self->spritesNode != NULL) {
			((CCSprite*)self->spritesNode->list[0])->setZOrder(-(self->GetZOrderY() - GameController::zero_y));
		}
		////this->Movelock = false;
		//if (crossSearchMap_) {
		//	crossSearchMap_ = false;
		//	MapController::ObjMap_add(this);
		//}
		now_move_num = -1;
		//GameController::positionSreenCenter(Vec2(0, 0));
	}
	//状态必须为移动
	if (!(self->status & Status::MOVE))
		return false;
	//移动完一格再继续新移动
	if (now_move_num > 0)
		return false;
	return true;
}
void CanSideWayObj::run() {
	
}
bool CanSideWayObj::isStatSideWay(bool add) {
	if (this->now_start_index >= this->start_index) {
		return true;
	}
	else {
		if(add)
			this->now_start_index++;
		return false;
	}
}
bool CanSideWayObj::doSideWay(Obj * self) {
	
	if (self->X == this->aim_x&&this->aim_y == self->Y) {
		self->unableMove((Obj*)-1);
	}
	this->sideWayFX_x = Direction(-1);
	this->sideWayFX_y = Direction(-1);
	Obj* result = NULL;
	Direction fx = self->fx;
	int x = self->X;
	int y = self->Y;
	self->next_poisition.x = self->X;
	self->next_poisition.y = self->Y;
	if (self->X > this->aim_x) {
		this->sideWayFX_x = Direction::LEFT;
		self->fx = Direction::LEFT;
		result = (Obj*)MapController::probelMap(self);
		self->fx = fx;
		if (result == NULL) {
			if (self->X % UNIT_OBJ_MAP == 0/*UNIT_OBJ_MAP - 1*/) {
				MapController::ObjMap_delete(self);
				self->X--;
				MapController::ObjMap_add(self);
				
			}
			else {
				self->X--;
			}
			self->next_poisition.x = self->X ;
		}
	}
	else if (self->X < this->aim_x) {
		this->sideWayFX_x = Direction::RIGHT;
		self->fx = Direction::RIGHT;
		result = (Obj*)MapController::probelMap(self);
		self->fx = fx;
		if (result == NULL) {
			
			if (self->X % UNIT_OBJ_MAP == UNIT_OBJ_MAP - 1) {
				MapController::ObjMap_delete(self);
				self->X++;
				MapController::ObjMap_add(self);
				
			}else
				self->X++;
			self->next_poisition.x = self->X;
		}
	}
	if (result != NULL) {
		self->unableMove(result);
		return false;
	}
	if (self->Y > this->aim_y) {
		this->sideWayFX_y = Direction::DOWN;

		self->fx = Direction::DOWN;
		result = (Obj*)MapController::probelMap(self);
		self->fx = fx;
		if (result == NULL) {
			
			if (self->Y % UNIT_OBJ_MAP == 0/*UNIT_OBJ_MAP - 1*/) {
				MapController::ObjMap_delete(self);
				self->Y--;
				MapController::ObjMap_add(self);
				
			}else
				self->Y--;
			self->next_poisition.y = self->Y ;
		}
	}
	else if (self->Y < this->aim_y) {
		this->sideWayFX_y = Direction::UP;

		self->fx = Direction::UP;
		result = (Obj*)MapController::probelMap(self);
		self->fx = fx;
		if (result == NULL) {
			
			if (self->Y % UNIT_OBJ_MAP == UNIT_OBJ_MAP - 1) {
				MapController::ObjMap_delete(self);
				self->Y++;
				MapController::ObjMap_add(self);
				
			}else
				self->Y++;
			self->next_poisition.y = self->Y;
		}
	}
	self->X = x;
	self->Y = y;
	if (result != NULL) {
		self->unableMove(result);
		return false;
	}
	else {
		self->now_moveNum = self->moveNum;
		self->afterMove();
	}
	return true;


}
//void CanSideWayObj::before_die(Obj * self) {
//	if (self->wayFindType == Obj::WayFindType::AIM && this->next_poisition.x != -10) {
//		this->clearData();
//	}
//}
//void CanSideWayObj::completeAIM(Obj *) {
//	this->clearData();
//}
//void CanSideWayObj::clearData() {
//	this->next_poisition.x = -10;
//}