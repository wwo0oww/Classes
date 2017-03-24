#include"Plant.h"
Plant::Plant() {
#ifdef DEBUG
	CCLOG("start");
#endif
}
void Plant::init() {
	Obj::init();
}
//Position* Plant::SetCoverPosition() {
//	return Obj::SetCoverPosition();
//}

int Plant::GetZOrderY() {
	return Obj::GetZOrderY();
}
void Plant::setDirection(Direction fx) {
	Obj::setDirection(fx);
}
//角色死亡
void Plant::die() {
	Obj::die();
}
//角色 活动
void Plant::run(int tid) {
	Obj::run(tid);
}//对象运行
 //暴露的调用对象方法的接口
void* Plant::Method(std::string methName, void* param) {
	return Obj::Method(methName, param);

}