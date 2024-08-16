#ifndef LSYSTEMCONTROLER_H
#include "imgui.h"

class LSystemController
{
public:
	LSystemController() :m_angle(90) {};
	~LSystemController() {};

	void DrawUI();
	float GetAngel() { return m_angle; }

private:
	float m_angle;

};

#endif // !LSYSTEMCONTROLER_H
