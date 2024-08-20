#include <iostream>
#include "raylib.h"
#include "Lsystem.h"
#include "LSystemVisualizer.h"
#include <cmath>
#include <stack>
#include "LSystemController.h"
#include "rlImGui.h"
#include "rlImGuiColors.h"

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
	LSystemController controller(&lsystem);
	controller.InitLystem();

	Color col;
	ImColor uiCol;
	

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
		uiCol = controller.GetColor();
		col = rlImGuiColors::Convert(uiCol);
		
		std::string res = lsystem.GetCurrentString();

		Visualizer::VisualiseLsystem(res, winndowWidth/2, windowHeight-200, angle, length, col);
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}