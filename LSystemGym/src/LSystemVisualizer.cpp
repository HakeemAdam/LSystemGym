#include "LSystemVisualizer.h"
#include <cmath>
#include <stack>
//#include "raymath.h"
#include "raylib.h"


void Visualizer::VisualiseLsystem(const std::string& lstring, float startX, float startY, float angle, float length)
{
	float x = startX;
	float y = startY;
	float currentAngle = -90;

	std::stack<Vector2> positionStack;
	std::stack<float> angleStack;

	for (char c : lstring)
	{
		switch (c)
		{
		case 'F':
		{
			float x2 = x + length * cos(currentAngle * DEG2RAD);
			float y2 = y + length * sin(currentAngle * DEG2RAD);
			DrawLine(x, y, x2, y2, BLACK);
			x = x2;
			y = y2;
			break;
		}
		case '+':
			currentAngle += angle;
			break;
		case '-':
			currentAngle -= angle;
			break;
		case '[':
			positionStack.push({ x,y });
			angleStack.push(currentAngle);
			break;
		case ']':
			if (!positionStack.empty() && !angleStack.empty())
			{
				Vector2 pos = positionStack.top();
				positionStack.pop();
				x = pos.x;
				y = pos.y;
				currentAngle = angleStack.top();
				angleStack.pop();
			}
			break;
		}
	}
}
