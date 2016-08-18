#pragma once
#include"../Obj.h"

class Biological :public Obj{
	//����
private:
	//����
	std::vector<int>m_children;
	//ĸ��
	int parent;
public:

	//����
private:
public:
	//��ȡ���������Ա
	std::vector<int>GetChildren();
	//���Ӻ��ӽڵ�
	virtual void AddChild(int);
	//�������Ӻ��ӽڵ�
	virtual void AddChildren(std::vector<int>children);

	//�Ƴ����ӽڵ�
	virtual void RemoveChild(int);
	//�����Ƴ����ӽڵ�
	virtual void RemoveChildren(std::vector<int>children);
	//��ɫ����
	virtual void die();

	virtual void BeforeRemoveNode(int);

	virtual void RemoveParent();	
	
};
