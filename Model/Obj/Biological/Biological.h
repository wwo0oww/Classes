#pragma once
#include"../Obj.h"

class Biological :public Obj{
	//属性
private:
	//孩子
	std::vector<int>m_children;
	//母亲
	int parent;
public:

	//方法
private:
public:
	//获取所有子类成员
	std::vector<int>GetChildren();
	//增加孩子节点
	virtual void AddChild(int);
	//批量增加孩子节点
	virtual void AddChildren(std::vector<int>children);

	//移除孩子节点
	virtual void RemoveChild(int);
	//批量移除孩子节点
	virtual void RemoveChildren(std::vector<int>children);
	//角色死亡
	virtual void die();

	virtual void BeforeRemoveNode(int);

	virtual void RemoveParent();	
	
};
