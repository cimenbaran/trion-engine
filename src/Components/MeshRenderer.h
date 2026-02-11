#pragma once
#include "Components/Component.h"
#include <memory>

class Shader;
class Mesh;

class MeshRenderer : public Component
{
public:
    MeshRenderer();
    ~MeshRenderer() override = default;

    void Render() override;

private:
    std::shared_ptr<Shader> m_shader;
    Mesh* m_mesh = nullptr;
};
