#pragma once
#include"../Model/data.h"
class LogControoler {
// Ù–‘
private:
	LogControoler * m_Instance;
public:
//∑Ω∑®
private:
	LogControoler() {
		
	}
public:
	LogControoler*GetInstance() {
		if (m_Instance == nullptr) {
			m_Instance = new LogControoler();
		}
		return m_Instance;
	}

};