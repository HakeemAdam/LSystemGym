#include <iostream>
#include "raylib.h"
#include "Lsystem.h"
#include "LSystemVisualizer.h"
#include <cmath>
#include <stack>
#include "LSystemController.h"
#include "rlImGui.h"

int main()
{
	std::cout << "Hello Lsystem" << '\n';

	const int winndowWidth = 1000;
	const int windowHeight = 1000;


	float angle = 90;
	int length;

	InitWindow(windowHeight, winndowWidth, "L-System Gym");

	SetTargetFPS(120);
	rlImGuiSetup(true);

	Lsystem lsystem;
	//lsystem.AddRule('F', "FF+[+F-F-F]-[-F+F+F]");
	LSystemController controller(&lsystem);
	controller.InitLystem();

	//std::string res = lsystem.GenerateLsystem(controller.GetIteration(), "F");


	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		// gui

		rlImGuiBegin();
		controller.DrawUI();
		rlImGuiEnd();

		angle = controller.GetAngel();
		length = controller.GetLength();
		
		std::string res = lsystem.GetCurrentString();

		Visualizer::VisualiseLsystem(res, winndowWidth/2, windowHeight-200, angle, length);
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}