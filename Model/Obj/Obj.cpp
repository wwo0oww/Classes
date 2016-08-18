#include "Obj.h"

template <typename T>
T Obj::lambda_CS(T param, std::function<T(Obj* context, T param)>func) {
#ifdef WIN_32
	EnterCriticalSection(&this->cs);
#endif
	if (this == NULL) {
		
	}
	return func(this, param);

#ifdef WIN_32
	LeaveCriticalSection(&this->cs);
#endif
}
//对象公有初始化 部分
void Obj::init() {
	InitializeCriticalSection(&this->cs);
}
//
Obj::Obj() {
	this->init();
}

//获取ID
long Obj::GetID() {
	return this->ID;
}
//设置ID
void Obj::SetID(long ID) {
	this->ID = ID;
}

//获取血量
float Obj::GetHP() {
	return this->HP;
}

//设置血量
void Obj::SetHP(float HP) {
	this->HP = HP;
}


//获取魔量
float Obj::GetMP() {
	return this->MP;
}


//设置魔量
void Obj::SetMP(float MP) {
	this->MP = MP;
}

//获取X坐标
float Obj::GetX() {
	return this->X;
}
//设置X坐标
void Obj::SetX(float X) {
	 this->X = X;
}

//获取Y坐标
float Obj::GetY() {
	return this->Y;
}
//设置Y坐标
void Obj::SetY(float Y) {
	this->Y = Y;
}

//获取Z坐标
float Obj::GetZ() {
	return this->Z;
}
//设置Z坐标
void Obj::SetZ(float Z) {
	this->Z = Z;
}

//获取离地高度
float Obj::GetHigh() {
	return this->m_high;
}
//设置离地高度
void Obj::SetHigh(float high) {
	this->m_high = high;
}

//获取离地高度
float Obj::GetBottomHigh() {
	return this->m_bottomHigh;
}
//设置离地高度
void Obj::SetBottomHigh(float bottomHigh) {
	this->m_bottomHigh = bottomHigh;
}

//获取高度
float Obj::GetH() {
	return this->H;
}
//设置高度
void Obj::SetH(float H){
	this->H = H;
}

//获取宽度
float Obj::GetW() {
	return this->W;
}
//设置宽度
void Obj::SetW(float W) {
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
			this->BeforeRemoveNode();
			(*src).erase((*src).begin() + i);
			srcLength--;
		}
		else {
			i++;
		}
	}
}
void Obj::BeforeRemoveNode() {
	printf("Obj:BeforeRemoveNode");
}

void Obj::die() {}

void Obj::run() {

}
void Obj::Method(std::string methName, void* param) {
	
}