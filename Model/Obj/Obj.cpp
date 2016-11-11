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
//�����г�ʼ�� ����
void Obj::init() {
	InitializeCriticalSection(&this->cs);
}
//
Obj::Obj() {
	this->init();
}

//��ȡID
long Obj::GetID() {
	return this->ID;
}
//����ID
void Obj::SetID(long ID) {
	this->ID = ID;
}

//��ȡѪ��
float Obj::GetHP() {
	return this->HP;
}

//����Ѫ��
void Obj::SetHP(float HP) {
	this->HP = HP;
}


//��ȡħ��
float Obj::GetMP() {
	return this->MP;
}


//����ħ��
void Obj::SetMP(float MP) {
	this->MP = MP;
}
//��ȡpostion
 Obj::Position* Obj::Getpostion() {
	 return this->postion;
}
//����postion
 void Obj::Setpostion(Position position) {
	 this->postion->x = position.x;
	 this->postion->y = position.y;
 }

//��ȡX����
float Obj::GetX() {
	return this->X;
}
//����X����
void Obj::SetX(float X) {
	 this->X = X;
}

//��ȡY����
float Obj::GetY() {
	return this->Y;
}
//����Y����
void Obj::SetY(float Y) {
	this->Y = Y;
}

//��ȡZ����
float Obj::GetZ() {
	return this->Z;
}
//����Z����
void Obj::SetZ(float Z) {
	this->Z = Z;
}

//��ȡ��ظ߶�
float Obj::GetHigh() {
	return this->m_high;
}
//������ظ߶�
void Obj::SetHigh(float high) {
	this->m_high = high;
}

//��ȡ��ظ߶�
float Obj::GetBottomHigh() {
	return this->m_bottomHigh;
}
//������ظ߶�
void Obj::SetBottomHigh(float bottomHigh) {
	this->m_bottomHigh = bottomHigh;
}

//��ȡ�߶�
float Obj::GetH() {
	return this->H;
}
//���ø߶�
void Obj::SetH(float H){
	this->H = H;
}

//��ȡ���
float Obj::GetW() {
	return this->W;
}
//���ÿ��
void Obj::SetW(float W) {
	this->W = W;
}
//��ĳ���б���IDΪʶ��ɾ������
void Obj::RemoveNode(std::vector<Obj*>* src, std::vector<int> node) {
	int deleteLength = node.size();
	bool bHas = false;//��ǰ���ӽڵ��Ƿ���Ҫɾ��
	int srcLength = (*src).size();

	for (int i = 0; i < srcLength; ) {
		bHas = false;
		for (int j = 0; j < deleteLength; j++) {
			if (node[j] == (*src)[i]->GetID()) {//��Ҫɾ�б���������ӽڵ�
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
//��¶�ĵ��ö��󷽷��Ľӿ�
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