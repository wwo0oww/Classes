#include"Biological.h"
//��ȡ���к��ӳ�Ա
std::vector<Obj*> Biological::GetChildren() {
	return this->m_children;
}
//���Ӻ��ӽڵ�
void Biological::AddChild(Obj*child) {
	if(child)
	this->m_children.push_back(child);
}
//�������Ӻ��ӽڵ�
void Biological::AddChildren(std::vector<Obj*> children) {
	for (std::vector<Obj*>::iterator it = children.begin();it != children.end();it++){
		if (*it)
		this->m_children.push_back(*it);
	}
}
//�Ƴ����ӽڵ�
void Biological::RemoveChild(Obj*child) {
	for (std::vector<Obj*>::iterator it = this->m_children.begin();it != m_children.end();it++) {
		if ((*it)->GetID() == child->GetID()) {
			this->m_children.erase(it);
			break;
		}
	}
}
//�����Ƴ����ӽڵ�
void  Biological::RemoveChildren(std::vector<Obj*>children) {
	std::vector<int> IDList;
	for (std::vector<Obj*>::iterator it = children.begin();it != children.end();it++) {
		IDList.push_back((*it)->GetID());
	}
	this->RemoveChildren(IDList);
}

//�����Ƴ����ӽڵ�
void  Biological::RemoveChildren(std::vector<int>children) {
	 this->RemoveNode(&this->m_children,children);
}

void Biological::BeforeRemoveNode() {
	Obj::BeforeRemoveNode();
	
}

void Biological::die() {
	Obj::die();

}