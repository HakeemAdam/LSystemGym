#include "LSystemVisualizer.h"
#include <cmath>
#include <stack>
#include <vector>
//#include "raymath.h"
#include "raylib.h"

struct LineSegment
{
	Vector2 start;
	Vector2 end;
};

void Visualizer::VisualiseLsystem(const std::string& lstring, float startX, float startY, float angle, float length)
{
	std::vector<LineSegment> segments;

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
			
			segments.push_back({ {x,y}, {x2,y2} });
			//DrawLine(x, y, x2, y2, BLACK);
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

	Rectangle screenBounds = { 0,0,GetScreenWidth(), GetScreenHeight() };

	for (const auto& segment : segments)
	{
		if (CheckCollisionPointRec(segment.start, screenBounds) ||
			CheckCollisionPointRec(segment.end, screenBounds))
		{
			DrawLineV(segment.start, segment.end, BLACK);
		}
		
	}
}
