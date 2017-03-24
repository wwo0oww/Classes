#pragma once
#include"../Obj.h"
enum Professional {

};
class Biological :public Obj{
	//����
private:
	//����
	std::vector<int>m_children;
	//ĸ��
	long parent;
	//Ŀ��ID
	long aimID;
	//Ŀ������
	std::map<float, float>aimPositoin;
	//��޶����б�
	std::map<long, int>hateObjs;
	//�־�����б�
	std::map<long, int>fearObjs;
	Professional professional;

public:

	//����
private:
public:
	Biological();
	virtual void init();
	//��ȡ���������Ա
	std::vector<int>GetChildren();
	//���Ӻ��ӽڵ�
	virtual void AddChild(int);
	//�������Ӻ��ӽڵ�
	virtual void AddChildren(std::vector<int>children);

	virtual void sendBullet(Obj*);
	//�Ƴ����ӽڵ�
	virtual void RemoveChild(int);
	//�����Ƴ����ӽڵ�
	virtual void RemoveChildren(std::vector<int>children);
	//��ɫ����
	virtual void die();

	virtual void run(int);
	//
	virtual void BeforeRemoveChildren(int);
	//�Ƴ����׽ڵ�
	virtual void RemoveParent();	
	//��ȡĿ��ID
	virtual long GetaimID();
	//����Ŀ��ID
	virtual void SetaimID(long);
	//��ȡĿ������
	virtual std::map<float, float>GetaimPositoin();
	//����Ŀ������
	virtual void SetaimPositoin(std::map<float, float>);
	//��ȡ��޶����б�
	virtual std::map<long, int>GethateObjs();
	//���ó�޶����б�
	virtual void SethateObjs(std::map<long, int>);
	//���ó�޶���
	virtual void SethateObj(long,int);
	//��ȡ�־�����б�
	virtual std::map<long, int>GetfearObjs();
	//���ÿ־�����б�
	virtual void SetfearObjs(std::map<long, int>);
	//���ÿ־����
	virtual void SetfearObj(long, int);

	virtual void setDirection(Direction fx);



	virtual Direction getDirection() ;

	virtual void dearShowObj();

	virtual void afterAttack();
	
	virtual void ShowObj();

	virtual int GetZOrderY();
	virtual void setStatus(Status);
	//virtual void changeFX(Direction fx);
	virtual void dearSonDeath(Obj*);
	virtual void dearCollision(Obj*);
	//��¶�ĵ��ö��󷽷��Ľӿ�
	virtual void* Method(std::string, void* = NULL);
	virtual void initSpriteFrame(void*);
};
