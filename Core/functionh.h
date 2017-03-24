#pragma once
#ifndef  FUNCTION_h
#define FUNCTION_h
//#include"cocos2d.h"
template<class TData>
static TData*static_add(TData*&head,TData*&tail) {
	if (tail->next == NULL) {
		tail->next = (TData*)malloc(sizeof(TData));
		tail->next->next = NULL;
		tail->next->last = tail;
	}
	TData* tmp = tail;
	tail = tail->next;
	return tmp;
}
template<class TData>
static void static_delete(TData*&p,TData*&head, TData*&tail) {
	if (p->last == NULL) {
		TData* tmp = tail->next;
		tail->next = p;
		p->last = tail;
		if (tmp != NULL)
			tmp->last = p;
		head = p->next;
		p->next = tmp;

		head->last = NULL;
	}
	else {
		p->last->next = p->next;
		p->next->last = p->last;

		TData* tmp = tail->next;
		tail->next = p;
		p->last = tail;
		p->next = tmp;
		if (tmp != NULL)
			tmp->last = p;
	}
}
static int numb_add(int src, int add, int base = 16, int weishu = 4) {
	int places = 0;
	int tmp = add;
	while (tmp / base > 0) {
		places++;
		tmp = tmp / base;
	}
	int i = 0;
	int num = 1;
	while (i++ < places) {
		num *= base;
	}
	src -= num*(src / num%base);
	src += add;
	return src;
}
static bool numb_get(int src, int num) {
	return src&num;
}
#endif // ! FUNCTION.h

//int getCurrentTime()
//{
//	/*struct cc_timeval now;
//	CCTime::gettimeofdayCocos2d(&now, NULL);
//
//	return now.tv_sec * 1000 + now.tv_usec / 1000;*/
//	return 0;
//}