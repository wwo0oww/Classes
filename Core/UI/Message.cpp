#include"Message.h"
#include "Core/AppMacros.h"
 Vector<Message*>Message::MessageList;
Message* Message::create(Type type,Scene * scene) {
	Vector<Message*>::iterator it = MessageList.begin();
	while (it != MessageList.end()) {
		if ((*it)->type == type && (*it)->scene == scene&&!(*it)->used) {
			break;
		}
		it++;
	}
	if (it != MessageList.end()) {
		(*it)->schedule_count = 0;
		(*it)->used = true;
		(*it)->setVisible(true);
		return *it;
	}
	else {
		Message*message = new Message();
		MessageList.pushBack(message);
		message->type = type;
		message->scene = scene;
		message->used = true;
		message->schedule_count = 0;
		switch (type) {
		case Type::TEXT:
			message->label = Label::createWithTTF("", "fonts/arial.ttf", 30);
			message->label->setPosition(100,100);
			message->addChild(message->label);
			break;
		}
		message->scene->addChild(message);
		return message;
	}
}
void Message::setText(std::string str) {
	this->label->setString(str);
}
void Message::schedule() {
	Vector<Message*>::iterator it = MessageList.begin();
	while (it != MessageList.end()) {
		if ((*it)->used && (*it)->schedule_count > 0) {
			(*it)->schedule_count--;
			if ((*it)->schedule_count == 0) {
				(*it)->used = false;
				(*it)->setVisible(false);
			}
		}
		it++;
	}
}
void Message::show() {
	//this->label
	this->setVisible(true);
}
void Message::show(int s) {
	this->schedule_count = s;
	this->setVisible(true);
}