#pragma once
class Singleton {
protected:
	static Singleton * m_Instance;
protected:
	Singleton() {};
public:
	static Singleton*GetInstance() {
		if (m_Instance == nullptr) {
			m_Instance = new Singleton();
		}
		return m_Instance;
	}

};
