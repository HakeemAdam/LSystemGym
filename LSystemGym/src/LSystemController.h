#ifndef LSYSTEMCONTROLER_H
//#include "Lsystem.h"
#include "imgui.h"

class Lsystem;

class LSystemController
{
public:
	LSystemController();
	~LSystemController();

	void DrawUI();
	float GetAngel() const { return m_angle; }
	int GetLength() const { return m_length; }

private:
	float m_angle;
	int m_length;

	Lsystem* m_lsystem;

};

#endif // !LSYSTEMCONTROLER_H
