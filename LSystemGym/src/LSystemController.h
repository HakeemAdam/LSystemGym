#ifndef LSYSTEMCONTROLER_H
//#include "Lsystem.h"
#include "imgui.h"
#include <string>
#include <map>

class Lsystem;
struct LSystemPreset;
struct Color;

class LSystemController
{
public:
	LSystemController(Lsystem* lsytem);
	~LSystemController();

	void DrawUI();
	void InitLystem();
	void InitDefaultRules();
	void SetPreset(const LSystemPreset& preset);

	float GetAngel() const { return m_angle; }
	int GetLength() const { return m_length; }
	int GetIteration() const { return m_iterations; }
	ImColor GetColor() const { return m_currentColor; }

private:
	float m_angle;
	int m_length;
	int m_iterations;
	
	ImColor m_currentColor;

	std::string m_currentAxiom;
	std::string m_currentRule;

	std::map<char, std::string> m_currentRules;

	Lsystem* m_lsystem;

};

#endif // !LSYSTEMCONTROLER_H
