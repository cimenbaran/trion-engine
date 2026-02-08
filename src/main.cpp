#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* window, int w, int h){ glViewport(0,0,w,h); }

const char* VS = R"(#version 460 core
layout (location = 0) in vec3 aPos;
void main(){ gl_Position = vec4(aPos, 1.0); })";

const char* FS = R"(#version 460 core
out vec4 FragColor;
void main(){ FragColor = vec4(0.9, 0.2, 0.4, 1.0); })";

static GLuint makeShader(GLenum type, const char* src){
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if(!ok)
    { 
        char log[1024]; 
        glGetShaderInfoLog(s,1024,nullptr,log); 
        std::cerr << log << "\n"; 
        glDeleteShader(s);
        return 0;
    }
    return s;
}

int main(){
    if(!glfwInit()){ std::cerr << "GLFW init failed\n"; return -1; }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    // Debug Context
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    GLFWwindow* win = glfwCreateWindow(800, 600, "Hello OpenGL", nullptr, nullptr);
    if(!win){ glfwTerminate(); return -1; }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1); // vsync

    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "GLAD load failed\n"; return -1;
    }

    // triangle geometry
    float verts[] = { -0.6f,-0.5f,0.0f,  0.6f,-0.5f,0.0f,  0.0f,0.6f,0.0f };
    GLuint vao,vbo; glGenVertexArrays(1,&vao); glGenBuffers(1,&vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    // shaders
    GLuint vs = makeShader(GL_VERTEX_SHADER, VS);
    GLuint fs = makeShader(GL_FRAGMENT_SHADER, FS);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs); glAttachShader(prog, fs);
    glLinkProgram(prog);

    // Check Program Status
    GLint linked = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &linked);
    if (!linked) {
        char log[1024];
        glGetProgramInfoLog(prog, 1024, nullptr, log);
        std::cerr << "Program link error:\n" << log << "\n";
    }

    glDeleteShader(vs); glDeleteShader(fs);

    double lastTime = glfwGetTime();
    int frames = 0;

    while(!glfwWindowShouldClose(win)){
#pragma region FPS_Counter


        double currentTime = glfwGetTime();
        frames++;

        // If one second has passed
        if (currentTime - lastTime >= 1.0)
        {
            double fps = frames / (currentTime - lastTime);

            char title[128];
            sprintf_s(title, "Hello OpenGL | FPS: %.1f", fps);
            glfwSetWindowTitle(win, title);

            frames = 0;
            lastTime = currentTime;
        }
#pragma endregion


        glfwPollEvents();
        glClearColor(0.1f,0.12f,0.15f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(prog);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(win);
    }
    glfwDestroyWindow(win);
    glfwTerminate();

    glDeleteProgram(prog);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    return 0;
}
