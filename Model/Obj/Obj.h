#pragma once
#include"cocos2d.h"
#include"Model\data.h"
#include<iostream>
class Obj {
	//����
public:
	//Ψһ��ʶ
	CC_SYNTHESIZE(int,id,ID);
	//Ѫ��
	CC_SYNTHESIZE(float,hp, HP);
	//ħ��
	CC_SYNTHESIZE(float,mp, MP);
	//x����
	CC_SYNTHESIZE(float,x,X);
	//y����
	CC_SYNTHESIZE(float,y, Y);
	//z���� �߶�
	CC_SYNTHESIZE(float,z,Z);
	//�߶� �����߾���
	CC_SYNTHESIZE(float,m_high,High);
	//�߶� �ײ���ظ߶�
	CC_SYNTHESIZE(float,m_bottomHigh,);
	//ռ�ظ߶�
	CC_SYNTHESIZE(float,h, H);
	//ռ�ؿ��
	CC_SYNTHESIZE(float ,w,W);
private:
	//����

public:
	//��ĳ���б���IDΪʶ��ɾ������
	virtual void RemoveNode(std::vector<Obj*>*, std::vector<int>);
	
	virtual void  BeforeRemoveNode();

	virtual void die();

	virtual void run();//��������
private:
};