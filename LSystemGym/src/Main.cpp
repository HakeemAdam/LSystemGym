#include <iostream>
#include "raylib.h"
#include "Lsystem.h"


int main()
{
	std::cout << "Hello Lsystem" << '\n';

	const int winndowWidth = 800;
	const int windowHeight = 800;

	InitWindow(windowHeight, winndowWidth, "L-System Gym");

	SetTargetFPS(120);


	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);


		EndDrawing();
	}

	CloseWindow();
	return 0;
}