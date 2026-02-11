#include "Components/MeshRenderer.h"
#include "Rendering/Shader/Shader.h"
#include "Rendering/Mesh/Mesh.h"
#include "Rendering/RenderContext.h"
#include "Object/GameObject.h"
#include "Components/Transform.h"
#include "Math/Mat4.h"

static const char* kVS = R"(
#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;

uniform mat4 u_MVP;

out vec3 vColor;

void main()
{
    vColor = aColor;
    gl_Position = u_MVP * vec4(aPos, 1.0);
}
)";

static const char* kFS = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0);
}
)";

MeshRenderer::MeshRenderer()
{
    m_shader = std::make_shared<Shader>(kVS, kFS);
    m_mesh = Mesh::Cube();
}

void MeshRenderer::Render()
{
    auto* owner = Owner();
    if (!owner) return;

    Transform* tr = owner->GetTransform();
    if (!tr) return;

    const Mat4 M = tr->WorldMatrix();
    const Mat4 V = RenderContext::View();
    const Mat4 P = RenderContext::Projection();

    const Mat4 MVP = P * V * M;

    m_shader->Bind();
    m_shader->SetMat4("u_MVP", MVP.m);
    m_mesh->Draw();
    m_shader->Unbind();
}
