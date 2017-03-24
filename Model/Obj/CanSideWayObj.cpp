#include"CanSideWayObj.h"
#include"Controller\GameController.h"
void CanSideWayObj::setSideWayAim(int x, int y) {
	this->canSideWay = true;
	this->aim_x = x;
	this->aim_y = y;
	this->now_start_index = 0;
}
bool CanSideWayObj::stepMove(Obj * self,Direction fx, Vec2 next_position_, int& now_move_num, bool& crossSearchMap_) {
	//��̨���� �仯
	//���ƶ�now_move_num = mvoenum ���¸�ֵ
	//�ڼ�Ϊ0ǰ ��ʾ�˴��ƶ�һ��û�����������ƶ�
	//��Ϊ 0 ��ʾ�ƶ�һ���ƶ��꣬��now_move_num = -1����ʾ�����ƶ� ��̨�������±仯��
	if (!self->bMove)
		return false;

	if (now_move_num > 0) {

		now_move_num--;
		if (self->spritesNode != NULL) {
			//���ж�����Ϊ����һ��û�ƶ��꣬�ƶ�״̬�仯�ˣ�����Ϊ-1���Ҵ�ʱ�����ƶ�
			Vec2 tmp = self->getScreenPosition();
			if (self->bAI || !GameController::positionSreenCenter(self->next_poisition, Vec2(1.0 / self->moveNum, 1.0 / self->moveNum), self->now_moveNum == 0/*this->now_moveNum == 0 true*//*ע��������Ϊ��ʹ��Ļ��ͷһ�����ƶ� ���������ᵼ�������ƶ�ʱһ��һ��*/)) {
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
	//�ƶ�����һ�񣬽���̨��Ϣͬ��
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
	//״̬����Ϊ�ƶ�
	if (!(self->status & Status::MOVE))
		return false;
	//�ƶ���һ���ټ������ƶ�
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