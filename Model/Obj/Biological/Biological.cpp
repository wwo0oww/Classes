#include"Biological.h"
#include"Model\data.h"
//��ȡ���к��ӳ�Ա
std::vector<int> Biological::GetChildren() {
	return this->m_children;
}
//���Ӻ��ӽڵ�
void Biological::AddChild(int childId) {
	this->m_children.push_back(childId);
}
//�������Ӻ��ӽڵ�
void Biological::AddChildren(std::vector<int> children) {
	for (std::vector<int>::iterator it = children.begin();it != children.end();it++){
		if (*it)
		this->m_children.push_back(*it);
	}
}
//�Ƴ����ӽڵ�
void Biological::RemoveChild(int child) {
	for (std::vector<int>::iterator it = this->m_children.begin();it != m_children.end();it++) {
		if (*it == child) {
			this->m_children.erase(it);
			break;
		}
	}
}


//�����Ƴ����ӽڵ�
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
//��ȡĿ��ID
long Biological::GetaimID() {
	return this->aimID;
}
//����Ŀ��ID
void Biological::SetaimID(long aimID) {
	this->aimID = aimID;
}
//��ȡĿ������
std::map<float, float>Biological::GetaimPositoin() {
	return this->aimPositoin;
}
//����Ŀ������
void Biological::SetaimPositoin(std::map<float, float>) {
}
//��ȡ��޶����б�
std::map<long, int>Biological::GethateObjs() {
	return this->hateObjs;
}
//���ó�޶����б�
void Biological::SethateObjs(std::map<long, int> hateObjs) {
	
}
//���ó�޶���
void Biological::SethateObjs(std::map<long, int> hateObjs) {

}
//��ȡ�־�����б�
std::map<long, int>Biological::GetfearObjs() {
}
//���ÿ־�����б�
void Biological::SetfearObjs(std::map<long, int>) {

}
//���ÿ־����
void Biological::SetfearObjs(std::map<long, int>) {

}
//��¶�ĵ��ö��󷽷��Ľӿ�
void* Biological::Method(std::string methName, void* param) {
	/*if (methName == "GetID") {
		ClassData::ObjData *data = new ClassData::ObjData(this->GetID());
		return data;
	}
	if (methName == "SetID") {
		this->SetID(((ClassData::ObjData*)param)->_int);
		return NULL;
	}*/
	return NULL;
}