#ifndef LSYSTEM_PRESET_H

#include <string>
#include <map>
#include <vector>


struct LSystemPreset
{
	std::string name;
	std::string axiom;
	std::map<char, std::string> rules;
};

class LSystemPresets
{
public:
	static const LSystemPreset Dragon;
	static const LSystemPreset Sierpinski;
	static const LSystemPreset Plant;

	static const std::vector<LSystemPreset>& GetAllPresets();

};
#endif // !LSYSTEM_PRESET_H
