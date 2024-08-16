#ifndef LSYSTEMCONTROLER_H
#include "imgui.h"

class LSystemController
{
public:
	LSystemController() :m_angle(90), m_iterations(5) {};
	~LSystemController() {};

	void DrawUI();
	float GetAngel() const { return m_angle; }
	int GetIteration() const { return m_iterations; }

private:
	float m_angle;
	int m_iterations;

};

#endif // !LSYSTEMCONTROLER_H
