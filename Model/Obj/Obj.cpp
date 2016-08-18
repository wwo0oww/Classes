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