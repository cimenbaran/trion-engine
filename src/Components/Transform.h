#pragma once

#include "Component.h"
#include "Math/Vec3.h"
#include "Math/Mat4.h"
#include <vector>

class Transform : public Component
{
public:
	Vec3 position{ 0,0,0 };
	Vec3 rotationEulerDeg{ 0,0,0 };
	Vec3 scale{ 1,1,1 };

	// Hierarchy
	Transform* Parent() const { return m_parent; }
	const std::vector<Transform*>& Children() const { return m_children; }

	void SetParent(Transform* newParent);

	Mat4 LocalMatrix() const;
	Mat4 WorldMatrix() const;

private:
	void AddChild(Transform* child);
	void RemoveChild(Transform* child);

	Transform* m_parent = nullptr;
	std::vector<Transform*> m_children;
};