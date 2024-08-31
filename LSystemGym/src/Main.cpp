#include <iostream>
#include "raylib.h"
#include "Lsystem.h"
#include "LSystemVisualizer.h"
#include "LSystemController.h"
#include "LSystemCamera.h"
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

	/*Camera3D cam;
	cam.position = Vector3{ 0,0,10 };
	cam.target = Vector3{ -1,0,0 };
	cam.up = Vector3{ 0.0f, -1.0f, 0.0f };
	cam.fovy = 25.0f;
	cam.projection = CAMERA_PERSPECTIVE;*/



	Lsystem lsystem;
	LSystemController controller(&lsystem);
	controller.InitLystem();
	Visualizer visualizer;
	LSystemCamera cam;

	std::vector<LineSegment> segments;
	Color col;
	ImColor uiCol;

	ImFont font = controller.LoadCustomFont();
	rlImGuiReloadFonts();
	Vector2 previousMousePosition = GetMousePosition();

	while (!WindowShouldClose())
	{
		// cam
		
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			cam.Update();
			UpdateCamera(cam.GetCamera(), CAMERA_PERSPECTIVE);
		}

	
		cam.SetRotationFactor(controller.GetAnimationSpeed());
		cam.SetCameraTime(GetFrameTime());
		cam.Rotate();
		
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


		// 3d
		BeginMode3D(*cam.GetCamera());
		//DrawGrid(20, 1);
		

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
			segments = Visualizer::GenerateLSystem(res, 0, 0, angle,
				static_cast<float>(length) *0.01 , col);
			visualizer.SetFullSegments(segments);
		}

		if (controller.ShouldAnimate())
		{
			visualizer.StartAnimation(controller.GetAnimationMode());
		}

		if (!controller.isPaused())
		{
			visualizer.AnimateAndDraw();
		}
		else
		{
			visualizer.DrawOnly();
		}

		EndMode3D();
		
		controller.ResetFlags();
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}