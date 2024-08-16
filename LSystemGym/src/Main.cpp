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

	const int winndowWidth = 800;
	const int windowHeight = 800;


	float angle = 90;

	InitWindow(windowHeight, winndowWidth, "L-System Gym");

	SetTargetFPS(120);
	rlImGuiSetup(true);

	Lsystem lsystem;
	lsystem.AddRule('F', "FF+[+F-F-F]-[-F+F+F]");
	LSystemController controller;

	std::string res = lsystem.GenerateLsystem(5, "F");


	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		// gui

		rlImGuiBegin();

		controller.DrawUI();

		rlImGuiEnd();

		angle = controller.GetAngel();
		

		Visualizer::VisualiseLsystem(res, winndowWidth / 2, windowHeight - 50, angle, 6);
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}