#include"Building.h"
Building::Building() {
}
void Building::init() {
	Obj::init();
}
void Building::dearCollision(Obj*) {}
//角色死亡
void Building::die() {
	Obj::die();
}
//角色 活动
//对象运行
void Building :: run(int tid) {
	Obj::run(tid);
}
int Building::GetZOrderY() {
	return Obj::GetZOrderY();
}
//暴露的调用对象方法的接口
void* Building ::Method(std::string methName, void* param) {
	return Obj::Method(methName, param);
	
}