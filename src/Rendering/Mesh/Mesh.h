#pragma once
#include <cstdint>

class Mesh
{
public:
    Mesh(const float* vertices, uint32_t floatCount, uint32_t strideFloats);
    ~Mesh();

    void Draw() const;

    // Convenience
    static Mesh* Cube(); // returns a shared static cube

private:
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
    uint32_t m_vertexCount = 0;
    uint32_t m_strideBytes = 0;
};
