#include "LSystemVisualizer.h"
#include <cmath>
#include <stack>



std::vector<LineSegment> Visualizer::GenerateLSystem(const std::string& lstring, float startX, float startY, float angle, float length, Color col)
{
	std::vector<LineSegment> segments;
	float x = startX;
	float y = startY;
	float currentAngle = -90;

	std::stack<Vector2> positionStack;
	std::stack<float> angleStack;

	Color currentColor = col;

	float currentLemght = length;

	for (char c : lstring)
	{
		switch (c)
		{
		case 'F': case 'X' : case 'A': case 'G': case 'Y':
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
		case '!':
			currentLemght *= 0.9f;
			break;
		case '?':
			currentLemght *= 1.1f;
			break;
		}
	}
	return segments;
}

void Visualizer::SetFullSegments(const std::vector<LineSegment>& segments)
{
	m_fullSegments = segments;
}

void Visualizer::StartAnimation(int mode)
{
	m_currentMode = AnimationMode( mode);
	m_animationProgress = 0.0f;
}

void Visualizer::StopAnimation()
{
	m_currentMode = AnimationMode::None;
	m_animationProgress = 0.0f;
}

void Visualizer::SetAnimationSpeed(float speed)
{
	m_animationSpeed = speed;
}

void Visualizer::AnimateAndDraw()
{
	if (m_currentMode == AnimationMode::None)
	{
		for (const auto& segment : m_fullSegments)
		{
			DrawLineV(segment.start, segment.end, segment.color);
		}
	}
	else
	{
		m_animationProgress += GetFrameTime() * m_animationSpeed;
		if (m_animationProgress > 1.0f) m_animationProgress = 1.0f;

		int segmentsToShow = static_cast<int>(m_fullSegments.size() * m_animationProgress);


		for (int i = 0; i < segmentsToShow; i++)
		{
			const auto& segment = m_fullSegments[i];
			if (m_currentMode == AnimationMode::Growth)
			{
				DrawLineV(segment.start, segment.end, segment.color);
			}
			else if (m_currentMode == AnimationMode::Fade)
			{
				Color fadeColor = ColorAlpha(segment.color, m_animationProgress);
				DrawLineV(segment.start, segment.end, segment.color);
			}
		}
	}
}
