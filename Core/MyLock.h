#pragma once

#include"Model\data.h"

class MyLock {
private:
#ifdef WIN_32
	CRITICAL_SECTION lock;
#else
#ifdef ANDROID
	mutex*lock;
#endif
#endif // WIN_32

public:
	MyLock();
	void Init();
	void Lock();
	void UnLock();
	void Delete();
	~MyLock();
};