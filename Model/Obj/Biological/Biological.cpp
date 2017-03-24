#include"Biological.h"
#include"Model\data.h"

void Biological::initSpriteFrame(void* spriteFrameInfo) {
	Obj::initSpriteFrame(spriteFrameInfo);
}
void Biological::init() {

	Obj::init();
}

void Biological::dearCollision(Obj*) {
	
}
void Biological::dearSonDeath(Obj*obj) {
	Obj::dearSonDeath(obj);
}
//void Biological::changeFX(Direction fx) {
//	Obj::changeFX(fx);
//}
//获取所有孩子成员
std::vector<int> Biological::GetChildren() {
	return this->m_children;
}
//增加孩子节点
void Biological::AddChild(int childId) {
	this->m_children.push_back(childId);
}
//批量增加孩子节点
void Biological::AddChildren(std::vector<int> children) {
	for (std::vector<int>::iterator it = children.begin();it != children.end();it++){
		if (*it)
		this->m_children.push_back(*it);
	}
}
//移除孩子节点
void Biological::RemoveChild(int child) {
	for (std::vector<int>::iterator it = this->m_children.begin();it != m_children.end();it++) {
		if (*it == child) {
			this->m_children.erase(it);
			break;
		}
	}
}


//批量移除孩子节点
void  Biological::RemoveChildren(std::vector<int>children) {
	for (std::vector<int>::iterator it_delete = children.begin();it_delete != children.end();it_delete++) {
		for (std::vector<int>::iterator it = this->m_children.begin();it != this->m_children.end();it++) {
			if (*it_delete == *it) {
				BeforeRemoveChildren(*it);
				this->m_children.erase(it);
				break;
			}
		}
	}
}

void Biological::BeforeRemoveChildren(int childId) {
	//std::map<int, Obj*>::iterator it = this-id_obj.find(childId);
	//(*it).second->
}

void Biological::die() {
	Obj::die();

}
void Biological::RemoveParent() {
	this->parent = -1;
}
//获取目标ID
long Biological::GetaimID() {
	return this->aimID;
}
//设置目标ID
void Biological::SetaimID(long aimID) {
	this->aimID = aimID;
}
//获取目标坐标
std::map<float, float>Biological::GetaimPositoin() {
	return this->aimPositoin;
}
//设置目标坐标
void Biological::SetaimPositoin(std::map<float, float>) {
}
//获取仇恨对象列表
std::map<long, int>Biological::GethateObjs() {
	return this->hateObjs;
}
//设置仇恨对象列表
void Biological::SethateObjs(std::map<long, int> hateObjs) {
	
}
//设置仇恨对象
void Biological::SethateObj(long ID, int offset) {

}
//获取恐惧对象列表
std::map<long, int>Biological::GetfearObjs() {
	return this->hateObjs;
}
//设置恐惧对象列表
void Biological::SetfearObjs(std::map<long, int>) {

}
void Biological::dearShowObj() {
	Obj::dearShowObj();
}

void Biological::ShowObj() {
	Obj::ShowObj();
}
//设置恐惧对象
void Biological::SetfearObj(long, int) {

}

void Biological::setDirection(Direction fx) {
	Obj::setDirection(fx);
}
void Biological::setStatus(Status status) {
	Obj::setStatus(status);
}
void Biological::afterAttack() {
	return Obj::afterAttack();
}

void Biological::sendBullet(Obj*) {}



Direction Biological::getDirection() {
	return Obj::getDirection();
}
Biological::Biological() {
}
void Biological::run(int tid) {
	Obj::run(tid);
}
int Biological::GetZOrderY() {
	return Obj::GetZOrderY();
}
//暴露的调用对象方法的接口
void* Biological::Method(std::string methName, void* param) {
	/*if (methName == "GetID") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetID());
		return data;
	}
	if (methName == "SetID") {
		this->SetID(((ClassData::ObjData*)param)->_int);
		return NULL;
	}*/
	Obj::Method(methName, param);
	return NULL;
}