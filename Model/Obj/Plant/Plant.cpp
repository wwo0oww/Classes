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
//��ɫ����
void Plant::die() {
	Obj::die();
}
//��ɫ �
void Plant::run(int tid) {
	Obj::run(tid);
}//��������
 //��¶�ĵ��ö��󷽷��Ľӿ�
void* Plant::Method(std::string methName, void* param) {
	return Obj::Method(methName, param);

}