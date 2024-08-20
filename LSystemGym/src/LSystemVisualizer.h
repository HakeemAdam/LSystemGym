#ifndef LSYSTEMVISUALIZER_H
#include <string>

struct Color;

class Visualizer {
public:
	static void VisualiseLsystem(const std::string& lstring, float startX, float startY, float angle, float length, Color col);

};


#endif // !LSYSTEMVISUALIZER_H

