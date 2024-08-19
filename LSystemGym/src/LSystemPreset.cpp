#include "LSystemPreset.h"

const LSystemPreset LSystemPresets::Dragon =
{
    "Dragon Curve",
    "FX",
    {{'X', "X+YF+"}, {'Y', "-FX-Y"}}
};

const LSystemPreset LSystemPresets::Sierpinski =
{
    "Sierpinski Triangle",
    "F-G-G",
    {{'F', "F-G+F+G-F"}, {'G', "GG"}}
};

const LSystemPreset LSystemPresets::Plant =
{
    "Fractal Plant",
    "X",
    {{'X', "F+[[X]-X]-F[-FX]+X"}, {'F', "FF"}}
};

const std::vector<LSystemPreset>& LSystemPresets::GetAllPresets()
{
    static const std::vector<LSystemPreset> allPresets = { Dragon, Sierpinski, Plant };
    return allPresets;
}
