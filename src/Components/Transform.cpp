#include "Transform.h"

void Transform::AddChild(Transform* child)
{
    if (!child) return;
    m_children.push_back(child);
}

void Transform::RemoveChild(Transform* child)
{
    if (!child) return;
    for (size_t i = 0; i < m_children.size(); ++i)
    {
        if (m_children[i] == child)
        {
            m_children.erase(m_children.begin() + (long long)i);
            return;
        }
    }
}

void Transform::SetParent(Transform* newParent)
{
    if (m_parent == newParent) return;

    // Detach from old parent
    if (m_parent)
        m_parent->RemoveChild(this);

    m_parent = newParent;

    // Attach to new parent
    if (m_parent)
        m_parent->AddChild(this);
}

Mat4 Transform::LocalMatrix() const
{
    Mat4 T = Mat4::Translate(position);
    Mat4 R = Mat4::RotateEulerDegrees(rotationEulerDeg);
    Mat4 S = Mat4::Scale(scale);
    return T * R * S;
}

Mat4 Transform::WorldMatrix() const
{
    if (!m_parent)
        return LocalMatrix();
    return m_parent->WorldMatrix() * LocalMatrix();
}
