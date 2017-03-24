#include"ErrorController.h"
ErrorController* ErrorController::m_Instance = new ErrorController();
ErrorController* ErrorController::GetInstance() {
	return m_Instance;
}
int ErrorController::dearError(CODE code) {
	return 0;
}