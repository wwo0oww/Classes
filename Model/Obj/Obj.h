#pragma once
#include"cocos2d.h"

#include<iostream>
#include<functional>
enum Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,
};
class Obj {
	//����
public:
	struct Position {
		float x;
		float y;
	}*PPosition;
private:
	//Ψһ��ʶ
	long ID;
	//Ѫ��
	float HP;
	//ħ��
	float MP;
	Position* postion;
	//x����
	float X;
	//y����
	float Y;
	//z���� �߶�
	float Z;
	//�߶� �����߾���
	float m_high;
	//�߶� �ײ���ظ߶�
	float m_bottomHigh;
	//ռ�ظ߶�
	float H;
	//ռ�ؿ��
	float W;

	//���߳� �� ���� �������  �ٽ���
	CRITICAL_SECTION cs;

	//
	Direction fx;

	Direction next_fx;
public:
	

	//����
	//�����г�ʼ�� ����
	void init();
	template <class T>
	T lambda_CS(T param, std::function<T(Obj* context, T param)>func);
	//���Բ���
	//��ȡpostion
	virtual Position* Getpostion();
	//����postion
	virtual void Setpostion(Position);
	//��ȡID
	virtual long GetID();
	//����ID
	virtual void SetID(long);

	//��ȡѪ��
	virtual float GetHP();
	//����Ѫ��
	virtual void SetHP(float);

	//��ȡħ��
	virtual float GetMP();
	//����ħ��
	virtual void SetMP(float);

	//��ȡX����
	virtual float GetX();
	//����X����
	virtual void SetX(float);

	//��ȡY����
	virtual float GetY();
	//����Y����
	virtual void SetY(float);

	//��ȡZ����
	virtual float GetZ();
	//����Z����
	virtual void SetZ(float);

	//��ȡ��ظ߶�
	virtual float GetHigh();
	//������ظ߶�
	virtual void SetHigh(float);

	//��ȡ��ظ߶�
	virtual float GetBottomHigh();
	//������ظ߶�
	virtual void SetBottomHigh(float);

	//��ȡ�߶�
	virtual float GetH();
	//���ø߶�
	virtual void SetH(float);

	//��ȡ���
	virtual float GetW();
	//���ÿ��
	virtual void SetW(float);
	//�Ƴ��ڵ� Ҫ�Ƴ���Դ�б� Ҫ��Դ�б��Ƴ���ID�б� 
	virtual void RemoveNode(std::vector<Obj*>*, std::vector<int>);
	//�Ƴ�ǰҪ������
	virtual void  BeforeRemoveChildren();
	//��ɫ����
	virtual void die();
	//��ɫ �
	virtual void run();//��������

	virtual void setDirection(Direction fx);

	virtual Direction getDirection();

	//��¶�ĵ��ö��󷽷��Ľӿ�
	virtual void* Method(std::string ,void* = NULL );

	Obj();



};