#pragma once
#include"cocos2d.h"
#include"Model\data.h"
#include<iostream>
class Obj {
	//属性
public:
	//唯一标识
	CC_SYNTHESIZE(int,id,ID);
	//血量
	CC_SYNTHESIZE(float,hp, HP);
	//魔量
	CC_SYNTHESIZE(float,mp, MP);
	//x坐标
	CC_SYNTHESIZE(float,x,X);
	//y坐标
	CC_SYNTHESIZE(float,y, Y);
	//z坐标 高度
	CC_SYNTHESIZE(float,z,Z);
	//高度 离地最高距离
	CC_SYNTHESIZE(float,m_high,High);
	//高度 底部距地高度
	CC_SYNTHESIZE(float,m_bottomHigh,);
	//占地高度
	CC_SYNTHESIZE(float,h, H);
	//占地宽度
	CC_SYNTHESIZE(float ,w,W);
private:
	//方法

public:
	//从某个列表，以ID为识别，删除子项
	virtual void RemoveNode(std::vector<Obj*>*, std::vector<int>);
	
	virtual void  BeforeRemoveNode();

	virtual void die();

	virtual void run();//对象运行
private:
};