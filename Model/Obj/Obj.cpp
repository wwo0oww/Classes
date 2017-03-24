#include "Obj.h"
#include"Model\data.h"
#include"Controller\ObjController.h"
#include"Controller\SpriteController.h"
#include"Controller\GameController.h"
#include"Core\UI\Progress.h"
#include"Model\Obj\Biological\Tank\Tank.h"




  void Obj::initSpriteFrame(void *p) {
	  SpriteController::SpriteFrameInfo*spriteFrameInfo = (SpriteController::SpriteFrameInfo*)p;
	  SpriteController::initSpriteFrame(spriteFrameInfo);
  }

//template <typename T>
//T Obj::lambda_CS(T param, std::function<T(Obj* context, T param)>func) {
//#ifdef WIN_32
//	EnterCriticalSection(&this->cs);
//#endif
//	if (this == NULL) {
//		
//	}
//	return func(this, param);
//
//#ifdef WIN_32
//	LeaveCriticalSection(&this->cs);
//#endif
//}
//对象公有初始化 部分
  Obj::Obj() {
	  this->canBeHarm = true;
	  this->offsetH = 0;
	  this->canBeenScanning = true;
	  this->canScanningAll = false;
	  this->status = Status::STAND;
	  this->bNew = true;
	  this->bAI = true;
	  picChangeNum = 0;
	  this->bOnce = false;
	  this->bhadOnce = false;
	  this->harmType = 1;
	  this->now_moveNum = -1;
	  this->progress = NULL;
	  this->bShowProgress = true;
	  this->bShowName = false;
	  this->wayFindNode = (WayFindNode*)malloc(sizeof(WayFindNode));
	  this->wayFindNode->obj = this;
	  this->wayFindNode->bFxFinish = false;
	  this->unitSpeedY = 0;
	  this->unitSpeedX = 0;
	  this->wayFindNode->init();
	  for (int i = 0; i < 4; i++)
		  this->key[i] = 0;
	  this->now_key = 0;
	  this->bClearMap = true;
	  this->bCover = true;
	  this->anchorPoint  = Vec2(-1,-1);
	  this->bDearCollision = false;
	  this->PATROL_range = 20;
	  this->objMapNode = NULL;
	  this->searchMapNode = NULL;
	  this->HP = this->now_HP = 100;
	  this->WANDERING_num_top = 50;
	  this->fx_change_time = 5;
	  this->fx_change_now_time = 0;
	  this->fx = Direction::DOWN;
	  this->deathDearNode = (DeathDearNode*)malloc(sizeof(DeathDearNode));
	  this->deathDearNode->init_();
	  this->attackList = (AttackList*)malloc(sizeof(AttackList));
	  this->attackList->init_();
  }
  void Obj::register_death_dear(Obj*obj,void(*fuc)(Obj*,Obj*)) {
	  this->deathDearNode->add_(fuc, obj,this);
  }
   void Obj::setWay(WayFindType type) {
	   switch (type)
	   {
	   case Obj::WayFindType::SIMPLE:
		   break;
	   case Obj::WayFindType::AIM:
		   break;
	   case Obj::WayFindType::PATROL:
		   break;
	   case Obj::WayFindType::WANDERING:
		   this->WANDERING_now_num = -1;
		   this->setStatus(Status(Status::MOVE|Status::STAND));
		   this->wayFindType = WayFindType::WANDERING;
		   this->setDirection(Direction(rand()%4));
		   this->WANDERING_num = rand() % this->WANDERING_num_top;
		   break;
	   default:
		   break;
	   }
  }
  void Obj::dearCollision(Obj*) {
  }
  void Obj::PATROL_set(int x, int y,int range) {
	  this->wayFindType = WayFindType::PATROL;
	  this->PATROL_x = x;
	  this->PATROL_y = y;
	  this->PATROL_range = range;
	  this->setStatus(Status(Status::STAND|Status::MOVE));
}
  void Obj::PATROL_getWay() {
	  bool bTurn = false;
	  if (this->X - this->PATROL_x > this->PATROL_range&&this->getDirection() == Direction::RIGHT) {
		  bTurn = true;
	  }else
	  if (this->X - this->PATROL_x < -this->PATROL_range&&this->getDirection() == Direction::LEFT) {
		  bTurn = true;
	  }else
	  if (this->Y - this->PATROL_y > this->PATROL_range&&this->getDirection() == Direction::UP) {
		  bTurn = true;
	  }else
	  if (this->Y - this->PATROL_y < -this->PATROL_range&&this->getDirection() == Direction::DOWN) {
		  bTurn = true;

	  }
	  if (bTurn) {
		  this->setDirection(Direction((this->fx + 1) % 4));
	  }
  }
void Obj::init() {
	this->W = CoverInfo::coverData->coverData[this->type].x;
	this->H = CoverInfo::coverData->coverData[this->type].y;
	/*Vec2 vec = CoverInfo::coverData->getPicList(this->type, this->status, this->fx);
	this->pw = vec.x;
	this->ph = vec.y;*/

	this->wayFindType = WayFindType::SIMPLE;
	
	this->bmove_cover_Rotation = false;
	this->bsclae_change = false;
	this->bAlive = 1;
	this->pic_index = 0;
	
	//this->CrossSearchMap = false;
	if (this->bNew)
		ObjController::AddObj(this);
	else {
		this->bAlive = 1;
		this->spritesNode = NULL;
		this->bUI = false;
		this->bShow = false;
		SetHP(this->HP,NULL);
		this->last_fx = Direction(-1);
		ObjController::reloadObj(this);
	}
	if (!this->bAI) {
	//	setWay(Obj::WayFindType::WANDERING);
		this->HP = 10000;
		this->moveNum = 6;
		this->harmType = 0;
		ObjController::PlayerID = this->ID;
		ObjController::PlayerObj = this;
		this->wayFindType = WayFindType::AIM;
		GameController::setCenterPosition(this->X,this->Y);
		//this->status = Status::STAND;
	}
	this->bpic = false;
	this->moving = false;
	this->pic_index = 0;
	this->hScale = 0;
	this->wScale = 0;
	this->wPScale = 0;
	this->hPScale = 0;
	this->now_moveNum = -1;
	this->now_picChangeNum = 0;
	//this->xProbeList_len = 0;
	//this->yProbeList_len = 0;
	auto vec2 = this->getScreenPosition();
	this->lastX = vec2.x;
	this->lastY = vec2.y;
	
	this->bhadOnce = false;
	
	//InitializeCriticalSection(&this->cs);
	sprintf(this->lastPicName,"");
	this->scene = GameController::scene;
	if (bMove) {
		this->unitSpeedY = this->getUnitSpeedY();
		this->unitSpeedX = this->getUnitSpeedX();
	}
	this->last_fx = Direction(-1);
	this->last_status = Status(-1);
	this->next_fx = Direction(-1);
	this->now_HP = this->HP;
}
void Obj::buildNameColor() {
	switch (this->harmType) {
	case 0:
		((Label*)spritesNode->list[3])->setColor(Color3B::GREEN);
		break;
	case 1:
		((Label*)spritesNode->list[3])->setColor(Color3B::WHITE);
		break;
	case 2:
		((Label*)spritesNode->list[3])->setColor(Color3B::RED);
		break;
	}
}
string Obj::getName() {
	char ch[6];
	sprintf(ch, "%d", this->ID);
	return string(ch);
}
void Obj::buildName() {
	
	((Label*)spritesNode->list[3])->setString(this->getName());
	this->buildNameColor();
}
void Obj::resetMove() {
	this->moving = false;
}
//获取ID
long Obj::GetID() {
	return this->ID;
}
//设置ID
void Obj::SetID(long ID) {
	this->ID = ID;
}

//Position* Obj::SetCoverPosition() {
//	coverList = (Position*)malloc
//		((this->W*this->H)*sizeof(Position));
//	int index = 0;
//	for (int i = - this->W / 2; i <= ceil(this->W / 2.0) - 1; i++) {
//		for (int j = -this->H / 2; j <= ceil(this->H / 2.0) - 1; j++) {
//			coverList[index].x = i;
//			coverList[index].y = j;
//			index++;
//		}
//	}
//
//	return coverList;
//}
//获取血量
int Obj::GetHP() {
	return this->HP;
}
void Obj::beenAttackToDie(Obj*enemy) {

}
void  Obj::setEnemy(Obj*) {}
//设置血量
int Obj::SetHP(int HP,Obj*enemy) {
	if (!this->canBeHarm) return 10000;
	if (this->now_HP <= 0)return 0;
	this->now_HP = HP;
	if (this->now_HP <= 0) {
		this->bAlive = -1;
		this->beenAttackToDie(enemy);
		this->setEnemy(enemy);
	}
	if (this->bShow) {
		if(this->bShowProgress)
		this->progress->setProgress(this->now_HP*1.0 / this->HP * 100);
	}
	return this->now_HP;
}


//获取魔量
int Obj::GetMP() {
	return this->MP;
}
int Obj::GetZOrderY() {
	return this->Y - this->offsetH;
}

//设置魔量
void Obj::SetMP(int MP) {
	this->MP = MP;
}
//获取postion
Position* Obj::Getpostion() {
	 return this->postion;
}
//设置postion
 void Obj::Setpostion(Position position) {
	 this->postion->x = position.x;
	 this->postion->y = position.y;
 }

//获取X坐标
 int Obj::GetX() {
	return this->X;
}
//设置X坐标
void Obj::SetX(int X) {
	 this->X = X;
}

//获取Y坐标
int Obj::GetY() {
	return this->Y;
}
//设置Y坐标
void Obj::SetY(int Y) {
	this->Y = Y;
}
float Obj::getUnitSpeedY() {
	if (this->unitSpeedY == 0) {
		this->unitSpeedY = GameController::getScreenUnitSize().height / this->moveNum;
	}
	return this->unitSpeedY;
}
float Obj::getUnitSpeedX() {
	if (this->unitSpeedX == 0) {
		this->unitSpeedX = GameController::getScreenUnitSize().width / this->moveNum;
	}
	return this->unitSpeedX;
}
void Obj::setMoveSpeed(int speed) {
	this->unitSpeedY = GameController::getScreenUnitSize().height / this->moveNum;
	this->unitSpeedX = GameController::getScreenUnitSize().width / this->moveNum;
	this->moveNum = speed;
}

//获取Z坐标
int Obj::GetZ() {
	return this->Z;
}
//设置Z坐标
void Obj::SetZ(int Z) {
	this->Z = Z;
}

//获取离地高度
int Obj::GetHigh() {
	return this->high;
}
//设置离地高度
void Obj::SetHigh(int high) {
	this->high = high;
}

//获取离地高度
int Obj::GetBottomHigh() {
	return this->start_high;
}
//设置离地高度
void Obj::SetBottomHigh(int bottomHigh) {
	this->start_high = bottomHigh;
}

//获取高度
int Obj::GetH() {
	return this->H;
}
//设置高度
void Obj::SetH(int H){
	this->H = H;
}

//获取宽度
int Obj::GetW() {
	return this->W;
}
//设置宽度
void Obj::SetW(int W) {
	this->W = W;
}
//从某个列表，以ID为识别，删除子项
void Obj::RemoveNode(std::vector<Obj*>* src, std::vector<int> node) {
	int deleteLength = node.size();
	bool bHas = false;//当前孩子节点是否需要删除
	int srcLength = (*src).size();

	for (int i = 0; i < srcLength; ) {
		bHas = false;
		for (int j = 0; j < deleteLength; j++) {
			if (node[j] == (*src)[i]->GetID()) {//从要删列表中清除孩子节点
				bHas = true;
				node.erase(node.begin() + j);
				deleteLength--;
				break;
			}
		}
		if (bHas) {
			this->BeforeRemoveChildren();
			(*src).erase((*src).begin() + i);
			srcLength--;
		}
		else {
			i++;
		}
	}
}

void Obj::BeforeRemoveChildren() {
	printf("Obj:BeforeRemoveChildren");
}
void Obj::resetUIData() {
	this->deleteSprite();
	if (this->bOnce)
		this->bhadOnce = false;
	this->bUI = false;
	this->resetSizeScale();
	this->spritesNode = NULL;
}
void Obj::resetData() {
	//resetUIData();
}
void Obj::removeStatus(Status status_) {
	this->status = Status(this->status^status_);
}
void Obj::sendBullet(Obj*) {}
void Obj::setStatus(Status status_) {
	if (status_ != this->status) {
		if (status_ == Status::STAND) {
			this->status = status_;
		}
		else
			this->status = (Status)(this->status | status_);
		
		this->now_picChangeNum = this->picChangeNum;
		this->pic_index = 0;
	}
	
}

void Obj::dearSonDeath(Obj*) {
}
void Obj::before_die() {
	if (this->bMove && (this->status&Status::MOVE)) {
		this->X = this->next_poisition.x;
		this->Y = this->next_poisition.y;
	}
}
void Obj::die() {
	this->deathDearNode->traverse();
	if(this->bClearMap||this->now_HP <= 0)
	MapController::ClearMap(this);
	
	if (this->bShow&&this->spritesNode != NULL) {
		this->resetUIData();
	}
	
	
}
void Obj::doChangeFX() {
	if (this->next_fx != -1) {
		this->wayFindNode->setAIMing(false);
		this->now_picChangeNum = 0;
		this->bPicChanage = true;
		this->now_moveNum = -1;
		this->pic_index = 0;
		//this->next_fx = fx;
		this->last_fx = this->fx;
		this->fx = this->next_fx;
		this->next_fx = (Direction)-1;
	}
}
void Obj::WANDERING() {
	this->WANDERING_now_num++;
	if (this->WANDERING_now_num >= this->WANDERING_num) {
		this->setDirection(Direction(rand() % 4 ));
		this->WANDERING_now_num = 0;
		this->WANDERING_num = rand() % this->WANDERING_num_top + 5;
	}
}
void Obj::changeFX(Direction fx_) {
	this->wayFindNode->setAIMing(false);
	this->setDirection(fx_);

	//if (!this->status&Status::ATTACK) {
	//	this->now_picChangeNum = 0;
	//	this->pic_index = 0;
	//}
	//this->now_moveNum = -1;
	//this->bPicChanage = true;
	//
	////this->next_fx = fx;
	//this->last_fx = this->fx;
	//this->fx = fx_;
	////this->next_fx = fx_;
	
}
void Obj::setDirection(Direction fx) {
	if (this->fx != fx&&this->fx_change_now_time == 0) {
		if (fx < 0 || fx > 3)return;
		this->now_key = key[int(fx)];
		this->pic_index = 0;
		this->fx_change_now_time = this->fx_change_time;
		this->now_moveNum = -1;
		this->bPicChanage = true;
		this->last_fx = this->fx;
		this->fx = fx;
		this->now_picChangeNum = this->picChangeNum;
	}

	//this->next_fx = fx;
	
}

Direction Obj::getDirection() {
	return this->fx;
}

//获取当前图片index
int  Obj::getPicIndex() {
	return this->pic_index;
}
//设置当前图片index
void  Obj::setPicIndex(int index) {
	this->pic_index = index;
	//this->
}

void Obj::afterAttack() {
	
}

void Obj::getPicName(bool bShow_) {
	totalpic = 1;
	
switch (this->fx) {
	case Direction::DOWN:
		if (this->status&Status::ATTACK) {
			if (bAttackPicChange) {
				if(bShow_)
				sprintf(this->picName, "%s (%d).png",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_a_down, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_down_attack_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_a_down);
			}
		}
		else if (this->status& Status::MOVE) {
			if (bAttackPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png", PrefixInfo::prefixData->prefixList[this->type]->prefix_m_down, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_down_move_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_m_down);
			}
		}
		else if (this->status& Status::STAND) {
			if (bStandPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_s_down, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_down_stand_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_s_down);
			}
		}

		break;
	case Direction::UP:
		if (this->status& Status::ATTACK) {
			if (bAttackPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png", PrefixInfo::prefixData->prefixList[this->type]->prefix_a_up, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_up_attack_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_a_up);
			}
		}
		else if (this->status&Status::MOVE) {
			if (bAttackPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png", PrefixInfo::prefixData->prefixList[this->type]->prefix_m_up, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_up_move_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_m_up);
			}
		}
		else if (this->status& Status::STAND) {
			if (bStandPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_s_up, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_up_stand_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_s_up);
			}
		}


		break;
	case Direction::RIGHT:
		if (this->status& Status::ATTACK) {
			if (bAttackPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png", PrefixInfo::prefixData->prefixList[this->type]->prefix_a_right, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_right_attack_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_a_right);
			}
		}
		else if (this->status& Status::MOVE) {
			if (bAttackPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png", PrefixInfo::prefixData->prefixList[this->type]->prefix_m_right, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_right_move_num;
				
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_m_right);
			}
		}
		else if (this->status&Status::STAND) {
			if (bStandPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_s_right, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_right_stand_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_s_right);
			}
		}
		break;
	case Direction::LEFT:
		if (this->status& Status::ATTACK) {
			if (bAttackPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png", PrefixInfo::prefixData->prefixList[this->type]->prefix_a_left, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_left_attack_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_a_left);
			}
		}
		else if (this->status& Status::MOVE) {
			if (bAttackPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png", PrefixInfo::prefixData->prefixList[this->type]->prefix_m_left, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_left_move_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_m_left);
			}
		}
		else if (this->status& Status::STAND) {
			if (bStandPicChange) {
				if (bShow_)
				sprintf(this->picName, "%s (%d).png",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_s_left, this->pic_index + 1);
				totalpic = PrefixInfo::prefixData->prefixList[this->type]->index_left_stand_num;
			}
			else {
				if (bShow_)
				sprintf(this->picName, "%s",
					PrefixInfo::prefixData->prefixList[this->type]->prefix_s_left);
			}
		}
		break;
	default:
		break;
	}
	this->pic_index++;
	this->pic_index %= totalpic;
	if (strlen(this->picName) < 4)
	{
		int i = 0;
	}
}

void Obj::dearShowObj() {
	if (this->bOnce && this->bhadOnce&&!GameController::bSreeenChange) {
		this->bUI = false;
		return;
	}
	if (this->bOnce&&!this->bhadOnce) {
		this->bhadOnce = true;
	}
	
	if (this->now_picChangeNum++ < this->picChangeNum&&!GameController::bSreeenChange) {
		this->bUI = false;
		return;
	}
	if (this->now_picChangeNum >= this->picChangeNum) {
		bPicChanage = true;
	}
	if (this->now_picChangeNum >= this->picChangeNum) {
		this->getPicName();
		if (this->pic_index == 0) {
			if (this->status& Status::ATTACK) {
				this->afterAttack();
			}
		}
	}
	if (this->picChangeNum == 0) {
		this->now_picChangeNum = 0; 
	}
	else
	this->now_picChangeNum %= this->picChangeNum;
	
	//图片是否有改变
	if (strcmp(this->lastPicName,picName) != 0||GameController::bSreeenChange) {
		//SpriteController::changeSprite(this);
		this->bUI = true;
	}
	else
	{
		this->bUI = false;
	}
	//获取个sprite
	if (this->spritesNode == NULL) {
		
		SpriteController::getOneTag(this);
		this->bUI = true;
	}

	sprintf(this->lastPicName, "%s", picName);
}

void Obj::deleteSprite() {
	this->progress = NULL;
	SpriteController::freeSprites(this);
}

void Obj::objOutSreen() {
	
	this->resetUIData();
}

void Obj::ShowObj() {
	Vec2 vec = CoverInfo::coverData->getPicList(this->type, this->status, this->fx);
	if (true&&this->X + (vec.x + 1) > GameController::position_x  - GameController::screenSizeW / 2
		&& this->X - (vec.x + 1)  <  GameController::position_x + GameController::screenSizeW / 2
		&&this->Y + (vec.y + 1)  > GameController::position_y - GameController::screenSizeH / 2
		&& this->Y - (vec.y + 1) < GameController::position_y + GameController::screenSizeH / 2
		) {
		this->dearShowObj();
		
	}
	else {
		this->last_fx = Direction(-1);
		this->bShow = false;
		this->dearNotShowObj();
	}
}

void Obj::dearNotShowObj() {
	//刚出sreen 释放sprite
	if (this->spritesNode != NULL) {
		this->objOutSreen();
		auto vec2 = this->getScreenPosition();
		this->lastX = vec2.x;
		this->lastY = vec2.y;
	}
	//加这一段仅仅是为了在非现实状态下的obj完成attack动作，哎，效率好低 有待提高
	if(this->picChangeNum !=0)
	if (this->now_picChangeNum++ >= this->picChangeNum) {
		this->now_picChangeNum %= this->picChangeNum;
		this->getPicName(false);
		if (this->pic_index == 0) {
			if (this->status& Status::ATTACK) {
				this->afterAttack();
			}
		}
	}
}
//设置血条坐标
Vec2 Obj::getScreenPositionP() {
	
	auto vec2 = GameController::getScreenUnitSize();
	return Vec2(0,vec2.height   * (CoverInfo::coverData->getPicList(this->type, this->status, this->fx).y /2)) ;
}

Vec2 Obj::getScreenPosition() {
	float x = GameController::position_x - GameController::screenSizeW / 2.0;
	float y = GameController::position_y - GameController::screenSizeH / 2.0;
	auto vec2 = GameController::getScreenUnitSize();
	Position* position = CoverInfo::coverData->getPicOffset(this->type, this->status, this->fx);
	return Vec2(vec2.width * (this->X - x + position->x),
		vec2.height   * (this->Y - y+ position->y)) + Director::getInstance()->getVisibleOrigin();
}

void Obj::InitBShowProgress() {
	this->progress->setProgress(this->now_HP*1.0 / this->HP * 100);
	((CCSprite*)this->spritesNode->list[1])->setVisible(this->bShowProgress);
}
bool Obj::InitBShowName() {
	((CCSprite*)this->spritesNode->list[3])->setVisible(this->bShowName);
	return this->bShowName;
}
void Obj::SetBShowName(bool bShowName) {
	if (this->bShowName != bShowName) {
		this->bShowName = bShowName;
		((CCSprite*)this->spritesNode->list[3])->setVisible(this->bShowName);
	}
}
void Obj::SetBShowProgress(bool bShowProgress) {
	if (this->bShowProgress != bShowProgress) {
		this->bShowProgress = bShowProgress;
		((CCSprite*)this->spritesNode->list[1])->setVisible(this->bShowProgress);
	}
}

bool Obj::GetBShowProgress() {
	return this->bShowProgress;
}

Vec2 Obj::getProgressSizeScale() {
	if (this->wPScale == 0 && this->hPScale == 0) {
		auto size = this->progress->progress->getSpriteFrame()->getRect().size;
		this->wPScale = GameController::wUnit *  CoverInfo::coverData->getPicList(this->type, this->status, this->fx).x / size.width;
		this->hPScale = GameController::hUnit * 0.3 / size.height;
	}
	return Vec2(wPScale, hPScale);
}
void Obj::resetSizeScale() {
	this->wScale == 0;
	this->hScale == 0;
}
Vec2 Obj::getSizeScale() {
	if(this->wScale == 0 && this->hScale == 0||this->bsclae_change){
		int status_ = 0;
		if (this->status&Status::ATTACK)
		{
			status_ = 0;
		}else if (this->status&Status::MOVE)
		{
			status_ = 1;
		}else if (this->status&Status::STAND){
			status_ = 2;
		}
		if (this->fx == -1)this->fx = Direction::DOWN;
		if (SpriteController::spriteScale[this->type][status_][int(this->fx)].x == 0) {
			this->pic_index = 0;
			this->getPicName();
			auto frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picName);
			
			
			Size tmp = frame->getRect().size;
			SpriteController::spriteScale[this->type][status_][int(this->fx)] = Vec2(tmp.width,tmp.height);
		}
		Vec2 size = SpriteController::spriteScale[this->type][status_][int(this->fx)];
		Vec2 vec = CoverInfo::coverData->getPicList(this->type, this->status, this->fx);
		this->wScale = GameController::wUnit * vec.x / size.x;
		this->hScale = GameController::hUnit * vec.y / size.y;
		
	}
	return Vec2(wScale, hScale);
}

void Obj::run(int tid) {
	
	//this->doChangeFX();
	this->dataDear();
	this->tid = tid;
	this->ShowObj();
	if (this->bMove)
	{
		this->unitSpeedY = this->getUnitSpeedY();
		this->unitSpeedX = this->getUnitSpeedX();
	}
	bool tmp = true;
	if(this->stepMove(this->fx,this->next_poisition,this->now_moveNum, tmp/*this->CrossSearchMap*/))
	this->objMove();
	
	
}

void Obj::dataDear() {
	if(this->fx_change_now_time > 0)
	this->fx_change_now_time--;
	/*if (GameController::bSreeenChange) {
		
	}*/
}


void Obj::setProbeList(int index,Vec2 vec2, vector<MapController::SynInfo*>&list,int& len, void* obj) {

	try
	{
		list.at(index)->x = vec2.x;
		list.at(index)->y = vec2.y;
		list.at(index)->obj = obj;
		list.at(index)->high = this->high;
		list.at(index)->start_high = this->start_high;
	}
	catch (const std::exception&)
	{
		MapController::SynInfo* tmp = (MapController::SynInfo*)malloc(sizeof(MapController::SynInfo));
		list.push_back(tmp);
		len++;
		list.at(index)->x = vec2.x;
		list.at(index)->y = vec2.y;
		list.at(index)->obj = obj;
		list.at(index)->high = this->high;
		list.at(index)->start_high = this->start_high;
	}
}

void Obj::AIMMove_getNewFX(bool init) {
	if (init) {
		this->wayFindNode->init();
		this->wayFindNode->setAIMing(true);
	}
	if (this->X > this->aim_x) {
		this->setStatus(Status(this->status | Status::MOVE));
		//this->status = Status(this->status|Status::MOVE);
		this->wayFindNode->addFX(Direction::LEFT);
		this->wayFindNode->bxMove = true;
	}
	else if (this->X < this->aim_x) {
		this->setStatus(Status(this->status | Status::MOVE));
		//this->status = Status(this->status | Status::MOVE);
		this->wayFindNode->addFX(Direction::RIGHT);
		this->wayFindNode->bxMove = true;
	}
	else if (this->Y > this->aim_y) {
		this->setStatus(Status(this->status | Status::MOVE));
		//this->status = Status(this->status | Status::MOVE);
		this->wayFindNode->addFX(Direction::DOWN);
		this->wayFindNode->bxMove = false;
	}
	else if (this->Y < this->aim_y) {
		this->setStatus(Status(this->status | Status::MOVE));
		//this->status = Status(this->status | Status::MOVE);
		this->wayFindNode->addFX(Direction::UP);
		this->wayFindNode->bxMove = false;
	}
	else {
		this->setStatus(Status(this->status ^ Status::MOVE));
		//this->status = Status(this->status ^ Status::MOVE);
	}
}
//获取aim移动方向
void Obj::getAIMMove() {
	
	/*if (this->getDirection() == -1) {
		AIMMove_getNewFX();
	}2017年2月9日21:40:44*/
	if (this->wayFindNode->bFxFinish) {
		this->wayFindNode->bFxFinish = false;
		AIMMove_getNewFX();
	}
	this->setDirection((Direction) this->wayFindNode->getNowFX());
	if (this->getDirection() == -1)
		this->setDirection ((Direction)this->wayFindNode->getFXInIndex(0));
}

bool Obj::canPutDown() {
	/*int param;
	MapController::changeMap(getmap[i]->x + X, getmap[i]->y + Y, &p, obj, MapController::Type::CONFIRM_NEXT, param);
*/
	return true;
}

void Obj::completeAIM() {
	this->wayFindNode->setAIMing(false);
	if (!this->bAI) {
		this->status = Status(this->status ^ Status::MOVE);
	}
	else {
		this->wayFindType = WayFindType::SIMPLE;
		this->status = Status(this->status ^ Status::MOVE);
	}
}
bool Obj::stepMove(Direction fx, Vec2 next_position_, int& now_move_num, bool& crossSearchMap_) {
	//后台坐标 变化
	//可移动now_move_num = mvoenum 重新赋值
	//在减为0前 表示此次移动一格还没结束，继续移动
	//变为 0 表示移动一格移动完，将now_move_num = -1，表示不可移动 后台坐标重新变化，
	if (!this->bMove)
		return false;
	
	if (now_move_num > 0) {

		now_move_num--;
		if (this->spritesNode != NULL) {
			//加判断是因为，当一格没移动完，移动状态变化了，则会变为-1，且此时不能移动
			Vec2 tmp = this->getScreenPosition();
			if (this->bAI || !GameController::positionSreenCenter(this->next_poisition, Vec2(1.0 / this->moveNum, 1.0 / this->moveNum), this->now_moveNum == 0/*this->now_moveNum == 0 true*//*注释内容是为了使屏幕镜头一个个移动 但是这样会导致物体移动时一卡一卡*/)) {
				switch (this->getDirection())
				{
				case Direction::DOWN:
					tmp.y -= (moveNum - now_move_num)* this->unitSpeedY;

					break;
				case Direction::UP:
					tmp.y += (moveNum - now_move_num) * this->unitSpeedY;
					break;
				case Direction::RIGHT:
					tmp.x += (moveNum - now_move_num) * this->unitSpeedX;
					break;
				case Direction::LEFT:
					tmp.x -= (moveNum - now_move_num) * this->unitSpeedX;
					break;
				}
				((CCSprite*)this->spritesNode->list[0])->setPosition(tmp);


			}
		}

	}
	//移动完了一格，将后台信息同步
	if (now_move_num == 0) {
		this->X = next_position_.x;
		this->Y = next_position_.y;
		if (this->spritesNode != NULL) {
			((CCSprite*)this->spritesNode->list[0])->setZOrder(-(this->GetZOrderY() - GameController::zero_y));
		}
		//this->Movelock = false;
		/*if (crossSearchMap_) {
			crossSearchMap_ = false;
			MapController::ObjMap_add(this);
		}*/
		now_move_num = -1;
		//GameController::positionSreenCenter(Vec2(0, 0));
	}
	//状态必须为移动
	if (!(this->status & Status::MOVE))
		return false;
	//移动完一格再继续新移动
	if (now_move_num > 0)
		return false;
	return true;
}

void Obj::objMove() {
	
	switch (this->wayFindType)
	{
	case WayFindType::AIM:
		if (this->wayFindNode->getAIMing()) {
			if (this->X != this->aim_x || this->Y != this->aim_y) {
				this->getAIMMove();
				// 判断x或 y方向的移动是否完成 重新获取移动 且取消此次移动【和下面保持一致】
				if (((this->getDirection() == Direction::RIGHT || this->getDirection() == Direction::LEFT) && this->wayFindNode->bxMove && this->aim_x == this->X) ||
					((this->getDirection() == Direction::UP || this->getDirection() == Direction::DOWN) && !this->wayFindNode->bxMove && this->aim_y == this->Y)) {
					this->AIMMove_getNewFX(true);
					this->wayFindNode->bFxFinish = true;
					//this->setDirection((Direction) -1); 2017年2月9日21:40:44
				}else
				//判断存储的上个方向是否可用 可用即用上一个的
				if ((this->wayFindNode->getLastFX() != -1 && MapController::probelMap(this, this->wayFindNode->getLastFX(), true) == 0))
				{
					this->setDirection((Direction)this->wayFindNode->useLastFX());
				}

			}
			else {
				this->completeAIM();
				Vec2 position = this->getScreenPosition();
			}
		}
		break;
	case WayFindType::SIMPLE:break;
	case WayFindType::PATROL:
		this->PATROL_getWay();
		break;
	case WayFindType::WANDERING:
		this->WANDERING();
		break;
	default:
		break;
	}
	if (this->wayFindNode->bFxFinish)return;
	Obj* result =(Obj*) MapController::probelMap(this);
	switch (this->getDirection())
	{
	case Direction::DOWN:

		if (result== 0){
			if (this->Y % UNIT_OBJ_MAP == 0) {
				MapController::ObjMap_delete(this);
				//this->CrossSearchMap = true;
				this->Y--;
				MapController::ObjMap_add(this);
				this->Y++;
			}
			//先存起来，等移动完 在赋值
			this->next_poisition.x = this->X;
			this->next_poisition.y = this->Y - 1;
		}
		break;
	case Direction::UP:
		if (result == 0) {
			if (this->Y % UNIT_OBJ_MAP == UNIT_OBJ_MAP - 1) {
				MapController::ObjMap_delete(this);
				//this->CrossSearchMap = true;
				this->Y++;
				MapController::ObjMap_add(this);
				this->Y--;
			}
			this->next_poisition.x = this->X;
			this->next_poisition.y = this->Y + 1;
			
		}
		break;
	case Direction::LEFT:
		if (result == 0) {
			if (this->X % UNIT_OBJ_MAP == 0) {
				MapController::ObjMap_delete(this);
				//this->CrossSearchMap = true;
				this->X--;
				MapController::ObjMap_add(this);
				this->X++;
			}
			this->next_poisition.x = this->X - 1;
			this->next_poisition.y = this->Y;
		}
		break;
	case Direction::RIGHT:
		if (result == 0) {
			if (this->X % UNIT_OBJ_MAP == UNIT_OBJ_MAP - 1) {
				MapController::ObjMap_delete(this);
				//this->CrossSearchMap = true;
				this->X++;
				MapController::ObjMap_add(this);
				this->X--;
			}
			this->next_poisition.x = this->X + 1;
			this->next_poisition.y = this->Y;
		}
		break;
	default:
		break;
	}
	if (result != NULL) {
		unableMove(result);
	}
	else {
		this->now_moveNum = this->moveNum;
		//this->Movelock = true;
		this->afterMove();
	}
	
}

void Obj::AIMMoveFull() {
	this->wayFindType = WayFindType::SIMPLE;
	this->setStatus(Status(this->status ^ Status::MOVE));
};
void Obj::afterMove() {}

void Obj::setAim(int x, int y) {
	if (this->wayFindType != WayFindType::AIM) {
		this->wayFindType = WayFindType::AIM;
	}
	if (aim_x == x && aim_y == y)return;
	this->aim_x = x;
	this->aim_y = y;
	
	this->AIMMove_getNewFX(true);
}

bool Obj::unableMove(Obj*obj) {
	int i;
	
	switch (this->wayFindType)
	{
	case WayFindType::AIM:
			if (!this->wayFindNode->getAIMing())
			return true;
			//this->wayFindNode->addFX(this->fx);
			switch (this->getDirection())
			{
			case Direction::DOWN:
				if (this->wayFindNode->getFXInIndex(this->wayFindNode->getLen() - 3) == this->getDirection()) {
					this->wayFindNode->setNowFX(Direction::UP);
				}
				else {
					if (this->X > this->aim_x)
						this->wayFindNode->addFX(Direction::LEFT);
					else
						this->wayFindNode->addFX(Direction::RIGHT);
				}
				break;
			case Direction::UP:
				if (this->wayFindNode->getFXInIndex(this->wayFindNode->getLen() - 3) == this->getDirection()) {
					this->wayFindNode->setNowFX(Direction::DOWN);
				}
				else {
					if (this->X > this->aim_x)
						this->wayFindNode->addFX(Direction::LEFT);
					else
						this->wayFindNode->addFX(Direction::RIGHT);
				}
				
				break;
			case Direction::RIGHT:
				if (this->wayFindNode->getFXInIndex(this->wayFindNode->getLen() - 3) == this->getDirection()) {
					this->wayFindNode->setNowFX(Direction::LEFT);
				}
				else {
					if (this->Y > this->aim_y)
						this->wayFindNode->addFX(Direction::DOWN);
					else
						this->wayFindNode->addFX(Direction::UP);
				}
				
				break;
			case Direction::LEFT:
				if (this->wayFindNode->getFXInIndex(this->wayFindNode->getLen() - 3) == this->getDirection()) {
					this->wayFindNode->setNowFX(Direction::RIGHT);
				}
				else {
					if (this->Y > this->aim_y)
						this->wayFindNode->addFX(Direction::DOWN);
					else
						this->wayFindNode->addFX(Direction::UP);
				}
				
				break;
			default:
				break;
			}
			break;
	case WayFindType::SIMPLE:
	case WayFindType::PATROL:
		if (!this->bAI)return true;
	case WayFindType::WANDERING:
		
		i = rand() % 2 == 0 ? -1 : 1;
		this->setDirection(Direction((this->getDirection() + i + 4) % 4));
		break;
	
	default:
		break;
	}
	return true;
	
}
//暴露的调用对象方法的接口
void* Obj::Method(std::string methName, void* param) {
	

	if (methName == "GetID") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetID());
		return data;
	}
	if (methName == "SetID") {
		this->SetID(((ClassData::ObjData*)param)->_int);
		return NULL;
	}
	if (methName == "GetHP") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetHP());
		return data;
	}
	if (methName == "SetHP") {
		this->SetHP(((ClassData::ObjData*)param)->_int,NULL);
		return NULL;
	}
	if (methName == "GetMP") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetMP());
		return data;
	}
	if (methName == "SetMP") {
		this->SetMP(((ClassData::ObjData*)param)->_int);
		return NULL;
	}
	if (methName == "GetX") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetX());
		return data;
	}
	if (methName == "SetX") {
		this->SetX(((ClassData::ObjData*)param)->_int);
		return NULL;
	}
	if (methName == "GetY") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetY());
		return data;
	}
	if (methName == "SetY") {
		this->SetY(((ClassData::ObjData*)param)->_int);
		return NULL;
	}
	if (methName == "GetZ") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetZ());
		return data;
	}
	if (methName == "SetZ") {
		this->SetZ(((ClassData::ObjData*)param)->_int);
		return NULL;
	}
	if (methName == "GetHigh") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetHigh());
		return data;
	}
	if (methName == "SetHigh") {
		this->SetHigh(((ClassData::ObjData*)param)->_int);
		return NULL;
	}

	if (methName == "GetBottomHigh") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetBottomHigh());
		return data;
	}
	if (methName == "SetBottomHigh") {
		this->SetBottomHigh(((ClassData::ObjData*)param)->_int);
		return NULL;
	}

	if (methName == "GetH") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetH());
		return data;
	}
	if (methName == "SetH") {
		this->SetH(((ClassData::ObjData*)param)->_int);
		return NULL;
	}

	if (methName == "GetW") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetW());
		return data;
	}
	if (methName == "SetW") {
		this->SetW(((ClassData::ObjData*)param)->_int);
		return NULL;
	}

	if (methName == "GetW") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetW());
		return data;
	}
	if (methName == "SetW") {
		this->SetW(((ClassData::ObjData*)param)->_int);
		return NULL;
	}
	/*if (methName == "RemoveNode") {
		this->RemoveNode(((ClassData::ObjData*)param)->_RemoveNodeData.srcList, ((ClassData::ObjData*)param)->_RemoveNodeData.deleteList);
		return NULL;
	}*/
	if (methName == "die") {
		this->die();
		return NULL;
	}
	if (methName == "run") {
		this->run(((ClassData::ObjData*)param)->_int);
		return NULL;
	}
	if (methName == "getScreenPosition") {
		Vec2 vec2 = this->getScreenPosition();
		return new ClassData::ObjData(vec2.x, vec2.y);;
	}
	if (methName == "setDirection") {
		this->setDirection((Direction)((ClassData::ObjData*)param)->_int);
		return NULL;
	}
	if (methName == "setStatus") {
		this->setStatus((Status)((ClassData::ObjData*)param)->_int);
		return NULL;
	}
}
