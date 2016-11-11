#pragma once
#include<stdio.h>
#include"Model\data.h"
#include<Windows.h>
class MyLock {
private:
#ifdef WIN_32
	CRITICAL_SECTION lock;
#endif // WIN_32
public:
	MyLock();
	void Init();
	void Lock();
	void UnLock();
	void Delete();
	~MyLock();
};