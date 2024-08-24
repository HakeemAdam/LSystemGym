#include "LSystemPreset.h"

const LSystemPreset LSystemPresets::Dragon =
{
    "Dragon Curve",
    "FX",
    {{'X', "X+YF+"}, {'Y', "-FX-Y"}},
    90
};

const LSystemPreset LSystemPresets::Sierpinski =
{
    "Sierpinski Triangle",
    "F-G-G",
    {{'F', "F-G+F+G-F"}, {'G', "GG"}},
    120
};

const LSystemPreset LSystemPresets::Plant =
{
    "Fractal Plant",
    "X",
    {{'X', "F+[[X]-X]-F[-FX]+X"}, {'F', "FF"}},
    20
};

const LSystemPreset LSystemPresets::KochCurveA =
{
    "Koch Curve A",
    " F-F-F-F",
    {{'F', "FF-F-F-F-F-F+F"}},
    90
};

const LSystemPreset LSystemPresets::KochCurveB =
{
    "Koch Curve B",
    " F-F-F-F",
    {{'F', "FF-F-F-F-FF"}},
    90
};

const LSystemPreset LSystemPresets::KochCurveC =
{
    "Koch Curve C",
    " F-F-F-F",
    {{'F', "FF-F+F-F-FF"}},
    90
};

const LSystemPreset LSystemPresets::KochCurveD =
{
    "Koch Curve D",
    " F-F-F-F",
    {{'F', "FF-F--F-F"}},
    90
};

const std::vector<LSystemPreset>& LSystemPresets::GetAllPresets()
{
    static const std::vector<LSystemPreset> allPresets = { Dragon, Sierpinski, Plant, KochCurveA, KochCurveB, KochCurveC, KochCurveD };
    return allPresets;
}
