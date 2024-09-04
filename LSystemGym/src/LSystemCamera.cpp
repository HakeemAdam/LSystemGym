#include "LSystemCamera.h"
#include <cmath>

LSystemCamera::LSystemCamera() : m_angle(0), m_distance(10),
                                 m_rotationFactor(0.01), m_deltaTime(0.0f), m_isRotating(false)
{
    m_camera.position = Vector3{0, 5, 10};
    m_camera.target = Vector3{-1, 0, 0};
    m_camera.up = Vector3{0.0f, -1.0f, 0.0f};
    m_camera.fovy = 45.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
}

void LSystemCamera::Update()
{
    if (m_isRotating)
    {
        Rotate();
    }
    float x = std::sin(m_angle) * m_distance;
    float z = std::cos(m_angle) * m_distance;
    m_camera.position = Vector3{x, m_camera.position.y, z};
}

void LSystemCamera::Rotate()
{
    m_angle += m_rotationFactor * m_deltaTime;
    if (m_angle > PI * 2)
    {
        m_angle -= PI * 2;
    }
    //Update();
}

Camera3D* LSystemCamera::GetCamera()
{
    return &m_camera;
}

void LSystemCamera::StartRotation(float speed)
{
    m_rotationFactor = speed;
    m_isRotating = true;
}

void LSystemCamera::StopRotation()
{
    m_isRotating = false;
}
