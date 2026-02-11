#pragma once
#include "Components/Component.h"
#include "Math/Mat4.h"

class Camera : public Component
{
public:
	// Perspective parameters
	float fovYDeg = 60.0f;
	float nearPlane = 0.1f;
	float farPlane = 200.f; // Draw Distance

	// Might change this in future to be a static Camera variable
	//		for a scene with multiple Cameras
	bool isPrimary = true;

	// Matrices
	Mat4 GetProjectionMatrix() const;
	Mat4 GetViewMatrix() const;

	void SetAspect(float aspect) { m_aspect = aspect; m_aspectManual = true; }

	void Update() override;

private:
	float GetAspect() const;


	mutable float m_aspect = 16.0f / 9.0f;
	bool m_aspectManual = false;
};