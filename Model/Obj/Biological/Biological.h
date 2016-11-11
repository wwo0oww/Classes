#pragma once
#include"../Obj.h"

class Biological :public Obj{
	//属性
private:
	//孩子
	std::vector<int>m_children;
	//母亲
	long parent;
	//目标ID
	long aimID;
	//目标坐标
	std::map<float, float>aimPositoin;
	//仇恨对象列表
	std::map<long, int>hateObjs;
	//恐惧对象列表
	std::map<long, int>fearObjs;
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

	virtual void run();
	//
	virtual void BeforeRemoveChildren(int);
	//移出父亲节点
	virtual void RemoveParent();	
	//获取目标ID
	virtual long GetaimID();
	//设置目标ID
	virtual void SetaimID(long);
	//获取目标坐标
	virtual std::map<float, float>GetaimPositoin();
	//设置目标坐标
	virtual void SetaimPositoin(std::map<float, float>);
	//获取仇恨对象列表
	virtual std::map<long, int>GethateObjs();
	//设置仇恨对象列表
	virtual void SethateObjs(std::map<long, int>);
	//设置仇恨对象
	virtual void SethateObj(long,int);
	//获取恐惧对象列表
	virtual std::map<long, int>GetfearObjs();
	//设置恐惧对象列表
	virtual void SetfearObjs(std::map<long, int>);
	//设置恐惧对象
	virtual void SetfearObj(long, int);

	virtual void setDirection(Direction fx);

	virtual Direction getDirection() ;

	//暴露的调用对象方法的接口
	virtual void* Method(std::string, void* = NULL);

};
