#pragma once
#include"cocos2d.h"
#include"Model\data.h"
#include<iostream>
#include<functional>
class Obj {
	//����
private:
	//Ψһ��ʶ
	long ID;
	//Ѫ��
	float HP;
	//ħ��
	float MP;
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

public:
	std::map<int, Obj*>id_obj;

	//����
protected:
	//�����г�ʼ�� ����
	void init();
	Obj();
	template <class T>
	T lambda_CS(T param, std::function<T(Obj* context, T param)>func);
	//���Բ���
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
	virtual void  BeforeRemoveNode();
	//��ɫ����
	virtual void die();
	//��ɫ �
	virtual void run();//��������
public:
	 static void Method(std::string ,void* );

};