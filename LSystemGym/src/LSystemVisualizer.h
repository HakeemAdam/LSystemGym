#ifndef LSYSTEMVISUALIZER_H
#include <string>
#include <vector>
#include "raylib.h"

struct Color;
struct LineSegment
{
	Vector2 start;
	Vector2 end;
	Color color;
};

enum class AnimationMode
{
	None,
	Growth,
	Fade, 
	Cycle
};

class Visualizer {
public:
	static std::vector<LineSegment> GenerateLSystem(const std::string& lstring, float startX, float startY, float angle, float length, Color col);


	void SetFullSegments(const std::vector<LineSegment>& segments);
	void StartAnimation(int mode);
	void StopAnimation();
	void SetAnimationSpeed(float speed);
	void AnimateAndDraw();
	void DrawOnly();

	float GetAnimationAngle() const { return m_animationAngle; }

private:
	AnimationMode m_currentMode = AnimationMode::None;
	float m_animationProgress = 0.0f;
	float m_animationSpeed = 1.0f;
	float m_animationAngle = 0.0f;
	std::vector<LineSegment> m_fullSegments;

};


#endif // !LSYSTEMVISUALIZER_H

