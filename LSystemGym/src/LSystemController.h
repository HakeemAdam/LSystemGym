#ifndef LSYSTEMCONTROLER_H
//#include "Lsystem.h"
#include "imgui.h"
#include <string>

class Lsystem;

class LSystemController
{
public:
	LSystemController(Lsystem* lsytem);
	~LSystemController();

	void DrawUI();
	void InitLystem();
	void InitDefaultRules();

	float GetAngel() const { return m_angle; }
	int GetLength() const { return m_length; }
	int GetIteration() const { return m_iterations; }

private:
	float m_angle;
	int m_length;
	int m_iterations;

	std::string m_currentAxiom;
	std::string m_currentRule;

	Lsystem* m_lsystem;

};

#endif // !LSYSTEMCONTROLER_H
