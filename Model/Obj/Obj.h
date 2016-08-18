#pragma once
#include"cocos2d.h"
#include"Model\data.h"
#include<iostream>
#include<functional>
class Obj {
	//属性
private:
	//唯一标识
	long ID;
	//血量
	float HP;
	//魔量
	float MP;
	//x坐标
	float X;
	//y坐标
	float Y;
	//z坐标 高度
	float Z;
	//高度 离地最高距离
	float m_high;
	//高度 底部距地高度
	float m_bottomHigh;
	//占地高度
	float H;
	//占地宽度
	float W;

	//多线程 见 数据 互斥访问  临界区
	CRITICAL_SECTION cs;

	//

public:
	std::map<int, Obj*>id_obj;

	//方法
protected:
	//对象公有初始化 部分
	void init();
	Obj();
	template <class T>
	T lambda_CS(T param, std::function<T(Obj* context, T param)>func);
	//属性操作
	//获取ID
	virtual long GetID();
	//设置ID
	virtual void SetID(long);

	//获取血量
	virtual float GetHP();
	//设置血量
	virtual void SetHP(float);

	//获取魔量
	virtual float GetMP();
	//设置魔量
	virtual void SetMP(float);

	//获取X坐标
	virtual float GetX();
	//设置X坐标
	virtual void SetX(float);

	//获取Y坐标
	virtual float GetY();
	//设置Y坐标
	virtual void SetY(float);

	//获取Z坐标
	virtual float GetZ();
	//设置Z坐标
	virtual void SetZ(float);

	//获取离地高度
	virtual float GetHigh();
	//设置离地高度
	virtual void SetHigh(float);

	//获取离地高度
	virtual float GetBottomHigh();
	//设置离地高度
	virtual void SetBottomHigh(float);

	//获取高度
	virtual float GetH();
	//设置高度
	virtual void SetH(float);

	//获取宽度
	virtual float GetW();
	//设置宽度
	virtual void SetW(float);
	//移除节点 要移除的源列表 要从源列表移除的ID列表 
	virtual void RemoveNode(std::vector<Obj*>*, std::vector<int>);
	//移除前要做的事
	virtual void  BeforeRemoveNode();
	//角色死亡
	virtual void die();
	//角色 活动
	virtual void run();//对象运行
public:
	 static void Method(std::string ,void* );

};