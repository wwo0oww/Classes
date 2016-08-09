#include"Biological.h"
//获取所有孩子成员
std::vector<Obj*> Biological::GetChildren() {
	return this->m_children;
}
//增加孩子节点
void Biological::AddChild(Obj*child) {
	if(child)
	this->m_children.push_back(child);
}
//批量增加孩子节点
void Biological::AddChildren(std::vector<Obj*> children) {
	for (std::vector<Obj*>::iterator it = children.begin();it != children.end();it++){
		if (*it)
		this->m_children.push_back(*it);
	}
}
//移除孩子节点
void Biological::RemoveChild(Obj*child) {
	for (std::vector<Obj*>::iterator it = this->m_children.begin();it != m_children.end();it++) {
		if ((*it)->GetID() == child->GetID()) {
			this->m_children.erase(it);
			break;
		}
	}
}
//批量移除孩子节点
void  Biological::RemoveChildren(std::vector<Obj*>children) {
	std::vector<int> IDList;
	for (std::vector<Obj*>::iterator it = children.begin();it != children.end();it++) {
		IDList.push_back((*it)->GetID());
	}
	this->RemoveChildren(IDList);
}

//批量移除孩子节点
void  Biological::RemoveChildren(std::vector<int>children) {
	 this->RemoveNode(&this->m_children,children);
}

void Biological::BeforeRemoveNode() {
	Obj::BeforeRemoveNode();
	
}

void Biological::die() {
	Obj::die();

}