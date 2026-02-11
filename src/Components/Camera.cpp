#include "Components/Camera.h"
#include "Object/GameObject.h"
#include "Components/Transform.h"
#include "Platform/Window.h"
#include <cmath>

static const float PI = 3.14159265359f;
static float DegToRad(float deg) { return deg * PI / 180.0f; }

float Camera::GetAspect() const
{
	if (m_aspectManual)
		return m_aspect;

	if (auto* w = Window::Main())
	{
		const int h = w->GetHeight();
		if (h > 0)
		{
			return (float)w->GetWidth() / (float)h;
		}
	}

	// If window is not initialized for a reason, stop exception throwing
	return m_aspect; 
}



Mat4 Camera::GetProjectionMatrix() const
{
	const float aspect = GetAspect();
	return Mat4::Perspective(DegToRad(fovYDeg), aspect, nearPlane, farPlane);
}

Mat4 Camera::GetViewMatrix() const
{
	// Camera uses owner's Transform
	auto* owner = Owner();
	if (!owner) return Mat4::Identity();

	auto* tr = owner->GetTransform();
	if (!tr) return Mat4::Identity();

	const Vec3 pos = tr->position;
	const Vec3 rot = tr->rotationEulerDeg;

	// Very simple yaw/pitch camera (Y = yaw, X = pitch)
	const float yaw = DegToRad(rot.y);
	const float pitch = DegToRad(rot.x);

	Vec3 forward;
	forward.x = std::cos(pitch) * std::sin(yaw);
	forward.y = std::sin(pitch);
	forward.z = -std::cos(pitch) * std::cos(yaw);

	forward = Normalize(forward);

	const Vec3 up = { 0, 1, 0 };
	return Mat4::LookAt(pos, pos + forward, up);
}

void Camera::Update()
{
	if (!m_aspectManual)
		m_aspect = GetAspect();
}

