#pragma once
#include"../Obj.h"

class Biological :public Obj{
	//����
private:
	//����
	std::vector<Obj*>m_children;
	//ĸ��
	Obj*parent;
public:

	//����
private:
public:
	//��ȡ���������Ա
	std::vector<Obj*>GetChildren();
	//���Ӻ��ӽڵ�
	virtual void AddChild(Obj*);
	//�������Ӻ��ӽڵ�
	virtual void AddChildren(std::vector<Obj*>children);

	//�Ƴ����ӽڵ�
	virtual void RemoveChild(Obj*);
	//�����Ƴ����ӽڵ�
	virtual void RemoveChildren(std::vector<Obj*>children);
	//�����Ƴ����ӽڵ�
	virtual void RemoveChildren(std::vector<int>children);
	//��ɫ����
	virtual void die();

	virtual void BeforeRemoveNode();
};
