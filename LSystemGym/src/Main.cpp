#include <iostream>
#include "raylib.h"
#include "Lsystem.h"
#include "LSystemVisualizer.h"
#include <cmath>
#include <stack>
#include "imgui.h"
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
	//lsystem.AddRule('B', "A");

	std::string res = lsystem.GenerateLsystem(5, "F");

	//std::cout << res << '\n';

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		// gui

		rlImGuiBegin();

		ImGui::Begin("RAY_LSYSTEM", NULL);
		ImGui::Text("Angle");
		ImGui::SliderFloat("Angle", &angle, 0, 360, "%.3f", 0);
		ImGui::End();

		rlImGuiEnd();

		

		Visualizer::VisualiseLsystem(res, winndowWidth / 2, windowHeight - 50, angle, 6);
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
}