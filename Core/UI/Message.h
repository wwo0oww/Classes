#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Message :public Layer{
public:
	enum class Type {
		TEXT,
	};
	static Message* create(Type type,Scene * scene);
	void setText(std::string str);
	void show();
	void show(int s);
	static void schedule();
private:
	Scene*scene;
	int schedule_count;
	Type type;
	Label* label;
	bool used;
	static Vector<Message*>MessageList;
};