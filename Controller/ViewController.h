#pragma once
#include"cocos2d.h"
class ViewController {
//����
private:
	static ViewController * m_instance;
//����
private:
	ViewController() {
		
	}
public:
	static ViewController GetInstance() {
	}
};