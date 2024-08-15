#include <iostream>
#include "raylib.h"
#include "Lsystem.h"
#include "LSystemVisualizer.h"
#include <cmath>
#include <stack>
#include "imgui.h"
#include "imgui_impl_dx12.h"


int main()
{
	std::cout << "Hello Lsystem" << '\n';

	const int winndowWidth = 800;
	const int windowHeight = 800;

	InitWindow(windowHeight, winndowWidth, "L-System Gym");

	SetTargetFPS(120);

	Lsystem lsystem;
	lsystem.AddRule('F', "FF+[+F-F-F]-[-F+F+F]");
	//lsystem.AddRule('B', "A");

	std::string res = lsystem.GenerateLsystem(5, "F");

	//std::cout << res << '\n';

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		Visualizer::VisualiseLsystem(res, winndowWidth / 2, windowHeight - 50, 25, 6);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}