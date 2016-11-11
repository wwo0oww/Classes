#include "Obj.h"
#include"Model\data.h"

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
//获取postion
 Obj::Position* Obj::Getpostion() {
	 return this->postion;
}
//设置postion
 void Obj::Setpostion(Position position) {
	 this->postion->x = position.x;
	 this->postion->y = position.y;
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

void Obj::die() {}

void Obj::setDirection(Direction fx) {
	this->next_fx = fx;
}

Direction Obj::getDirection() {
	return this->fx;
}

void Obj::run() {

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
		this->SetHP(((ClassData::ObjData*)param)->_float);
		return NULL;
	}
	if (methName == "GetMP") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetMP());
		return data;
	}
	if (methName == "SetMP") {
		this->SetMP(((ClassData::ObjData*)param)->_float);
		return NULL;
	}
	if (methName == "GetX") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetX());
		return data;
	}
	if (methName == "SetX") {
		this->SetX(((ClassData::ObjData*)param)->_float);
		return NULL;
	}
	if (methName == "GetY") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetY());
		return data;
	}
	if (methName == "SetY") {
		this->SetY(((ClassData::ObjData*)param)->_float);
		return NULL;
	}
	if (methName == "GetZ") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetZ());
		return data;
	}
	if (methName == "SetZ") {
		this->SetZ(((ClassData::ObjData*)param)->_float);
		return NULL;
	}
	if (methName == "GetHigh") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetHigh());
		return data;
	}
	if (methName == "SetHigh") {
		this->SetHigh(((ClassData::ObjData*)param)->_float);
		return NULL;
	}

	if (methName == "GetBottomHigh") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetBottomHigh());
		return data;
	}
	if (methName == "SetBottomHigh") {
		this->SetBottomHigh(((ClassData::ObjData*)param)->_float);
		return NULL;
	}

	if (methName == "GetH") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetH());
		return data;
	}
	if (methName == "SetH") {
		this->SetH(((ClassData::ObjData*)param)->_float);
		return NULL;
	}

	if (methName == "GetW") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetW());
		return data;
	}
	if (methName == "SetW") {
		this->SetW(((ClassData::ObjData*)param)->_float);
		return NULL;
	}

	if (methName == "GetW") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetW());
		return data;
	}
	if (methName == "SetW") {
		this->SetW(((ClassData::ObjData*)param)->_float);
		return NULL;
	}
	if (methName == "RemoveNode") {
		this->RemoveNode(((ClassData::ObjData*)param)->_RemoveNodeData.srcList, ((ClassData::ObjData*)param)->_RemoveNodeData.deleteList);
		return NULL;
	}
	if (methName == "die") {
		this->die();
		return NULL;
	}
	if (methName == "run") {
		this->run();
		return NULL;
	}
}