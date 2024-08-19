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
	Color color;
};

void Visualizer::VisualiseLsystem(const std::string& lstring, float startX, float startY, float angle, float length)
{
	std::vector<LineSegment> segments;

	float x = startX;
	float y = startY;
	float currentAngle = -90;

	std::stack<Vector2> positionStack;
	std::stack<float> angleStack;

	std::stack<Color> colorStack;
	Color currentColor = BLACK;

	float currentLemght = length;

	for (char c : lstring)
	{
		switch (c)
		{
		case 'F': case 'X' : case 'A':
		{
			float x2 = x + length * cos(currentAngle * DEG2RAD);
			float y2 = y + length * sin(currentAngle * DEG2RAD);
			
			segments.push_back({ {x,y}, {x2,y2}, currentColor });
		
			x = x2;
			y = y2;
			break;
		}
		case 'f':
		{
			x += currentLemght * cos(currentAngle * DEG2RAD);
			y += currentLemght * sin(currentAngle * DEG2RAD);
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
			colorStack.push(currentColor);
			break;
		case ']':
			if (!positionStack.empty() && !angleStack.empty() && !colorStack.empty())
			{
				Vector2 pos = positionStack.top();
				positionStack.pop();
				x = pos.x;
				y = pos.y;
				currentAngle = angleStack.top();
				angleStack.pop();
				currentColor = colorStack.top();
				colorStack.pop();
			}
			break;
		case '!':
			currentLemght *= 0.9f;
			break;
		case '?':
			currentLemght *= 1.1f;
			break;
		}
	}

	Rectangle screenBounds = { 0,0,GetScreenWidth(), GetScreenHeight() };

	for (const auto& segment : segments)
	{
		if (CheckCollisionPointRec(segment.start, screenBounds) ||
			CheckCollisionPointRec(segment.end, screenBounds))
		{
			DrawLineV(segment.start, segment.end, segment.color);
		}
		
	}
}
