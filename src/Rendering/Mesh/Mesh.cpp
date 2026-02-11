#include "Rendering/Mesh/Mesh.h"
#include <glad/glad.h>

Mesh::Mesh(const float* vertices, uint32_t floatCount, uint32_t strideFloats)
{
	m_strideBytes = strideFloats * sizeof(float);
	m_vertexCount = floatCount / strideFloats;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, floatCount * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_strideBytes, (void*)0);


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, m_strideBytes, (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::Draw() const
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertexCount);
	glBindVertexArray(0);
}

Mesh* Mesh::Cube()
{
    // 36 vertices, each: pos(3) + color(3)
    static float v[] = {
        // front
        -0.5f,-0.5f, 0.5f,  1,0,0,  0.5f,-0.5f, 0.5f,  0,1,0,  0.5f, 0.5f, 0.5f,  0,0,1,
        -0.5f,-0.5f, 0.5f,  1,0,0,  0.5f, 0.5f, 0.5f,  0,0,1, -0.5f, 0.5f, 0.5f,  1,1,0,
        // back
        -0.5f,-0.5f,-0.5f,  1,0,1, -0.5f, 0.5f,-0.5f,  0,1,1,  0.5f, 0.5f,-0.5f,  1,1,1,
        -0.5f,-0.5f,-0.5f,  1,0,1,  0.5f, 0.5f,-0.5f,  1,1,1,  0.5f,-0.5f,-0.5f,  0,0,0,
        // left
        -0.5f,-0.5f,-0.5f,  1,0,0, -0.5f,-0.5f, 0.5f,  0,1,0, -0.5f, 0.5f, 0.5f,  0,0,1,
        -0.5f,-0.5f,-0.5f,  1,0,0, -0.5f, 0.5f, 0.5f,  0,0,1, -0.5f, 0.5f,-0.5f,  1,1,0,
        // right
         0.5f,-0.5f,-0.5f,  1,0,1,  0.5f, 0.5f, 0.5f,  0,1,1,  0.5f,-0.5f, 0.5f,  1,1,1,
         0.5f,-0.5f,-0.5f,  1,0,1,  0.5f, 0.5f,-0.5f,  0,0,0,  0.5f, 0.5f, 0.5f,  0,1,1,
         // top
         -0.5f, 0.5f,-0.5f,  1,0,0, -0.5f, 0.5f, 0.5f,  0,1,0,  0.5f, 0.5f, 0.5f,  0,0,1,
         -0.5f, 0.5f,-0.5f,  1,0,0,  0.5f, 0.5f, 0.5f,  0,0,1,  0.5f, 0.5f,-0.5f,  1,1,0,
         // bottom
         -0.5f,-0.5f,-0.5f,  1,0,1,  0.5f,-0.5f, 0.5f,  0,1,1, -0.5f,-0.5f, 0.5f,  1,1,1,
         -0.5f,-0.5f,-0.5f,  1,0,1,  0.5f,-0.5f,-0.5f,  0,0,0,  0.5f,-0.5f, 0.5f,  0,1,1
    };

    static Mesh cube(v, (uint32_t)(sizeof(v) / sizeof(float)), 6);
    return &cube;
}