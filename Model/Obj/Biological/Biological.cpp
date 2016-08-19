#include"Biological.h"
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
				BeforeRemoveNode(*it);
				this->m_children.erase(it);
				break;
			}
		}
	}
}

void Biological::BeforeRemoveNode(int childId) {
	//std::map<int, Obj*>::iterator it = this-id_obj.find(childId);
	//(*it).second->
}

void Biological::die() {
	Obj::die();

}
void Biological::RemoveParent() {
	this->parent = -1;
}