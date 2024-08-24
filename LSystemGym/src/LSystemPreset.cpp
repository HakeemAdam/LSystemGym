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

const LSystemPreset LSystemPresets::QuadraticGosper =
{
    "Quadratic Gosper",
    " -YF",
    {{'X', "XFX-YF-YF+FX+FX-YF-YFFX+YF+FXFXYF-FX+YF+FXFX+YF-FXYF-YF-FX+FX+YFYF-"},
      {'Y', "+FXFX-YF-YF+FX+FXYF+FX-YFYF-FX-YF+FXYFYF-FX-YFFX+FX+YF-YF-FX+FX+YFY"}
    },
    90
};

const LSystemPreset LSystemPresets::QuadraticSnowflake =
{
    "Quadratic Snowflake",
    "F",
    {{'F', "F-F+F+F-F"}},
    90
};

const LSystemPreset LSystemPresets::HilbeertCurve =
{
    "Hilbert Curve",
    "X",
    {{'X', "-YF+XFX+FY-"},{'Y', "+XF-YFY-FX+"}},
    90
};

const LSystemPreset LSystemPresets::HexagonalGosper =
{
    "Hexagonal Gosper",
    "XF",
    {{'X', "X+YF++YF-FX--FXFX-YF+"},{'Y', "-FX+YFYF++YF+FX--FX-Y"}},
    60
};

const LSystemPreset LSystemPresets::SnakeKolam =
{
    "Snake Kolam",
    "F+XF+F+XF",
    {{'X', "X{F-F-F}+XF+F+X{F-F-F}+X"}},
    90
};

const LSystemPreset LSystemPresets::Kolam =
{
    "Kolam",
    "(-D--D)",
    {
        {'A', "F++FFFF--F--FFFF++F++FFFF--F"},
        {'B', "F--FFFF++F++FFFF--F--FFFF++F"},
        {'C', "BFA--BFA"},
        {'D', "CFC--CFC"},
    },
    45
};

const LSystemPreset LSystemPresets::Pentaplexity =
{
    "Pentaplexity",
    "F++F++F++F++F",
    {{'F', "F++F++F+++++F-F++F"}},
    36
};

const std::vector<LSystemPreset>& LSystemPresets::GetAllPresets()
{
    static const std::vector<LSystemPreset> allPresets = 
    { 
        Dragon, Sierpinski, Plant, 
        KochCurveA, KochCurveB, KochCurveC, KochCurveD,
        QuadraticGosper, QuadraticSnowflake, HilbeertCurve,
        HexagonalGosper, Kolam, SnakeKolam, Pentaplexity
    };
    return allPresets;
}
