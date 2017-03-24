#include"CanAttackObj.h"
#include"Controller\MapController.h"
CanAttackObj::CanAttackObj(Obj*self) {
	this->self = self;
	this->attackObj = (Obj::AttackObj*)malloc(sizeof(Obj::AttackObj));
	attackObj->attackNode = NULL;
}
void CanAttackObj::AttackObjDie(Obj*obj) {
	
}
bool CanAttackObj::CanAttack() {
	return this->send_bullet_now_time >= this->send_bullet_time;
}
void CanAttackObj::run() {
	if (this->send_bullet_now_time < this->send_bullet_time) {
		this->send_bullet_now_time++;
	}
}
void CanAttackObj::resetAttackTime() {
	this->send_bullet_now_time = 0;
}
