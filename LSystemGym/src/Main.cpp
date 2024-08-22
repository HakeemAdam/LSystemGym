#include <iostream>
#include "raylib.h"
#include "Lsystem.h"
#include "LSystemVisualizer.h"
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

	float mouseX = static_cast<float>(winndowWidth) / 2;
	float mouseY = static_cast<float>(windowHeight) - 200;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
	InitWindow(windowHeight, winndowWidth, "L-System Gym");

	SetTargetFPS(120);
	rlImGuiSetup(true);

	Lsystem lsystem;
	LSystemController controller(&lsystem);
	controller.InitLystem();

	Visualizer visualizer;

	std::vector<LineSegment> segments;

	Color col;
	ImColor uiCol;
	

	while (!WindowShouldClose())
	{
		// events
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
		{
			mouseX = GetMousePosition().x;
			mouseY = GetMousePosition().y;
		}
		
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

		segments = Visualizer::GenerateLSystem(res,mouseX , mouseY, angle, length, col);
		
		visualizer.SetFullSegments(segments);
		visualizer.StartAnimation(AnimationMode::Growth);


		visualizer.AnimateAndDraw();

		
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}