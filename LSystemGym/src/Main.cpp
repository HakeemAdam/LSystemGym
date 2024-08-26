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
	float speed;

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

	ImFont font = controller.LoadCustomFont();
	rlImGuiReloadFonts();

	while (!WindowShouldClose())
	{
		// events
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
		{
			mouseX = GetMousePosition().x;
			mouseY = GetMousePosition().y;
			controller.SetShouldRegenerate(true);
		}
		
		BeginDrawing();
		ClearBackground(SKYBLUE);

		// gui

		rlImGuiBegin();
		
		ImGui::PushFont(&font);
		
		controller.DrawUI();

		ImGui::PopFont();
		
		rlImGuiEnd();

		angle = controller.GetAngel();
		length = controller.GetLength();
		uiCol = controller.GetColor();
		col = rlImGuiColors::Convert(uiCol);
		speed = controller.GetAnimationSpeed();
		visualizer.SetAnimationSpeed(speed);
		
		// Draw

		if (controller.GetAnimationMode() == 3)
		{
			angle = visualizer.GetAnimationAngle();
			controller.SetAngle(angle);
		}

		if (controller.ShouldRegenerate() || controller.GetAnimationMode() ==3 )
		{
			std::string res = lsystem.GetCurrentString();
			segments = Visualizer::GenerateLSystem(res, mouseX, mouseY, angle,
				static_cast<float>(length), col);
			visualizer.SetFullSegments(segments);
		}

		if (controller.ShouldAnimate())
		{
			visualizer.StartAnimation(controller.GetAnimationMode());
		}

		visualizer.AnimateAndDraw();
		controller.ResetFlags();
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}