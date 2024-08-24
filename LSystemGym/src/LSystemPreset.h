#ifndef LSYSTEM_PRESET_H

#include <string>
#include <map>
#include <vector>


struct LSystemPreset
{
	std::string name;
	std::string axiom;
	std::map<char, std::string> rules;
	float angle;
};

class LSystemPresets
{
public:
	static const LSystemPreset Dragon;
	static const LSystemPreset Sierpinski;
	static const LSystemPreset Plant;
	static const LSystemPreset KochCurveA;
	static const LSystemPreset KochCurveB;
	static const LSystemPreset KochCurveC;
	static const LSystemPreset KochCurveD;

	static const LSystemPreset QuadraticGosper;
	static const LSystemPreset QuadraticSnowflake;

	static const LSystemPreset HilbeertCurve;
	static const LSystemPreset HexagonalGosper;

	static const LSystemPreset Kolam;
	static const LSystemPreset SnakeKolam;
	static const LSystemPreset Pentaplexity;

	static const std::vector<LSystemPreset>& GetAllPresets();

};
#endif // !LSYSTEM_PRESET_H
