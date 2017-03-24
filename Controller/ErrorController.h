#pragma once
#include"Core\Controller.h"


class ErrorController : public Controller {
private:
	static ErrorController * m_Instance;
public:
	static ErrorController* GetInstance();
	enum class CODE {
		THREAD_OVER,
	};
	static int dearError(CODE code);
};