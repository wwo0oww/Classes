#pragma once
#include"../Obj.h"

class Biological :public Obj{
	//属性
private:
	//孩子
	std::vector<Obj*>m_children;
	//母亲
	Obj*parent;
public:

	//方法
private:
public:
	//获取所有子类成员
	std::vector<Obj*>GetChildren();
	//增加孩子节点
	virtual void AddChild(Obj*);
	//批量增加孩子节点
	virtual void AddChildren(std::vector<Obj*>children);

	//移除孩子节点
	virtual void RemoveChild(Obj*);
	//批量移除孩子节点
	virtual void RemoveChildren(std::vector<Obj*>children);
	//批量移除孩子节点
	virtual void RemoveChildren(std::vector<int>children);
	//角色死亡
	virtual void die();

	virtual void BeforeRemoveNode();
};
