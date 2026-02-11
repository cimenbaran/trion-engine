#pragma once
#include <string>

class Shader
{
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetMat4(const char* name, const float* value16) const;

private:
    unsigned int m_program = 0;
};
