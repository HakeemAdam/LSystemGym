#ifndef LSYSTEMCONTROLER_H
//#include "Lsystem.h"
#include "imgui.h"
#include <string>
#include <map>
#include <vector>

class Lsystem;
struct LSystemPreset;
struct Color;
enum class AnimationMode;

class LSystemController
{
public:
	LSystemController(Lsystem* lsytem);
	~LSystemController();

	void DrawUI();
	void InitLystem();
	
	float GetAngel() const { return m_angle; }
	void SetAngle(int angle) { m_angle = angle; }
	int GetLength() const { return m_length; }
	int GetIteration() const { return m_iterations; }
	ImColor GetColor() const { return m_currentColor; }

	int GetAnimationMode() const { return m_animationMode; }
	float GetAnimationSpeed() const { return m_animationSpeed; }

	bool ShouldRegenerate() const { return m_shouldRegenerate; }
	bool ShouldAnimate() const { return m_shouldAnimate; }
	void ResetFlags();
	bool SetFlags(bool flag);
	void SetShouldRegenerate(bool value) { m_shouldRegenerate = value; }
	void SetPreset(const LSystemPreset& preset);

	ImFont LoadCustomFont();

private:
	float m_angle;
	int m_length;
	int m_iterations;
	float m_animationSpeed;
	
	ImColor m_currentColor;

	std::string m_currentAxiom;
	std::string m_currentRule;
	std::vector<std::string> m_rulesInputs;

	std::map<char, std::string> m_currentRules;

	Lsystem* m_lsystem;

	int m_animationMode;
	bool m_shouldRegenerate;
	bool m_shouldAnimate;

	const LSystemPreset* m_currentPreset;
	void InitDefaultRules();
	void UpdateRules();


};

#endif // !LSYSTEMCONTROLER_H
