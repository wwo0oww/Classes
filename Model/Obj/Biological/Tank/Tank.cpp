#include"Model\Obj\Biological\Tank\Tank.h"
#include"Model\data.h"
void Tank::setDirection(Direction fx) {
	Biological::setDirection(fx);
	
}
Direction Tank::getDirection() {
	return Biological::getDirection();
}
void Tank::run() {
	Biological::run();

}
//暴露的调用对象方法的接口
void* Tank::Method(std::string methName, void* param) {
	if (methName == "getDirection") {
		ClassData::ObjData *data = new ClassData::ObjData(this->getDirection());
		return data;
	}
	if (methName == "setDirection") {
		this->setDirection(((ClassData::ObjData*)param)->_direction);
		return NULL;
	}
	if (methName == "run") {
		this->run();
		return NULL;
	}
}