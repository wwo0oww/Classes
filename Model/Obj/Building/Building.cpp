#include"Building.h"
Building::Building() {
}
void Building::init() {
	Obj::init();
}
void Building::dearCollision(Obj*) {}
//��ɫ����
void Building::die() {
	Obj::die();
}
//��ɫ �
//��������
void Building :: run(int tid) {
	Obj::run(tid);
}
int Building::GetZOrderY() {
	return Obj::GetZOrderY();
}
//��¶�ĵ��ö��󷽷��Ľӿ�
void* Building ::Method(std::string methName, void* param) {
	return Obj::Method(methName, param);
	
}