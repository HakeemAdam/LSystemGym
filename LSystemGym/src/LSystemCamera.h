#ifndef LSYSTEM_CAMERA_H
#define LSYSTEM_CAMERA_H
#include <raylib.h>

class LSystemCamera
{
private:
	Camera3D m_camera;
	float m_angle;
	float m_distance;
	float m_rotationFactor;
	float m_deltaTime;

	bool m_isRotating;

public:
	LSystemCamera();
	void Update();
	void Rotate();
	Camera3D* GetCamera();
	void SetRotationFactor(float factor) { m_rotationFactor = factor; };
	void SetCameraTime(float t) { m_deltaTime = t; };

	void StartRotation(float speed);
	void StopRotation();
	
};

#endif // !LSYSTEM_CAMERA_H
