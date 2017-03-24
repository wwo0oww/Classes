#include"Weapon.h"
Weapon::Weapon():CanHarmObj(this) {
	this->X = -100;
	this->Y = -100;
}
//Position* Weapon::SetCoverPosition() {
//	return Obj::SetCoverPosition();
//}
void Weapon::dearCollision(Obj*obj) {
	
}
void Weapon::init() {
	this->bClearMap = false;
	this->parent = NULL;
	Obj::init();
}
bool Weapon::unableMove(Obj*obj) {
	
	this->boom(obj);
	return true;
}
void Weapon::afterAttack() {
	this->bAlive = -1;
}
void Weapon::boom(Obj*) {
	
}
void Weapon::afterMove() {
	this->now_move_n++;
	if (this->now_move_n >= this->max_move_n) {
		this->X = this->next_poisition.x;
		this->Y = this->next_poisition.y;
		this->boom(NULL);
	}

}

bool Weapon::stepMove(Direction fx, Vec2 next_position, int& now_move_num, bool& crossSearchMap) {
	return Obj::stepMove(fx,next_position,now_move_num,crossSearchMap);
}
//void Weapon::before_die() {
//	Obj::before_die();
//}
void Weapon::die() {
	/*if (this->parent != NULL) {
		parent->dearSonDeath(this);
	}*/
	this->aim_x = -1;
	this->aim_y = -1;
	Obj::die();
	this->parent = NULL;
}
string Weapon::getName() {
	char ch[6];
	int id = this->parent == NULL ? this->ID : this->parent->ID;
	sprintf(ch, "%d", id);
	return string(ch);
}
void Weapon::dearHarm() {
	
}
//角色 活动
void Weapon::run(int tid) {
	Obj::run(tid);
	this->dearHarm();
}//对象运行
void Weapon::objMove() {
	Obj::objMove();
}
//暴露的调用对象方法的接口
void* Weapon::Method(std::string methName, void* param) {
	return Obj::Method(methName, param);

}