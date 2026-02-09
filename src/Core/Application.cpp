#include "Application.h"
#include "Platform/Window.h"
#include "Scene/SceneManager.h"
#include "Core/Time.h"

Application::Application()
{
}

void Application::Run()
{
    Window window(1280, 720, "OpenGL Engine");

    SceneManager::LoadInitialScene();

    while (!window.ShouldClose())
    {
        Time::Update();

        SceneManager::Update();
        SceneManager::Render();

        window.SwapBuffers();
        window.PollEvents();
    }
}