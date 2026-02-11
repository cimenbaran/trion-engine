#include "SceneManager.h"
#include "Scene.h"
#include "Object/GameObject.h"
#include "Components/Transform.h"
#include "Components/FPSCounter.h"
#include "Components/Camera.h"
#include "Rendering/RenderContext.h"
#include "Scene/BootScene.h"
#include "Core/Time.h"
#include "Platform/Window.h"
#include <iostream>

std::shared_ptr<Scene> SceneManager::s_activeScene;

void SceneManager::LoadInitialScene()
{
	BootScene boot;
	SetActiveScene(boot.Create());
}

void SceneManager::Update()
{
	if (!s_activeScene)
		return;

	s_activeScene->Update();

	// ---- Debug: print main camera matrices once per second ----
	static float timer = 0.0f;
	timer += Time::DeltaTime();

	if (timer >= 1.0f)
	{
		timer = 0.0f;

		Camera* cam = GetMainCamera();
		if (!cam)
		{
			std::cout << "[SceneManager] No main camera.\n";
			return;
		}

		Mat4 V = cam->GetViewMatrix();
		Mat4 P = cam->GetProjectionMatrix();

		std::cout << "[SceneManager] Main camera OK. dt=" << Time::DeltaTime()
			<< " aspect=" << (Window::Main() ? (float)Window::Main()->GetWidth() / Window::Main()->GetHeight() : -1.0f)
			<< "\n";

		// Print one element from each matrix to confirm they change / exist
		std::cout << "  V.m[12]=" << V.m[12] << " V.m[13]=" << V.m[13] << " V.m[14]=" << V.m[14] << "\n";
		std::cout << "  P.m[0]=" << P.m[0] << " P.m[5]=" << P.m[5] << " P.m[10]=" << P.m[10] << "\n";
	}
}

void SceneManager::Render()
{
	if (!s_activeScene)
		return;

	Camera* cam = GetMainCamera();
	if (cam)
	{
		RenderContext::SetViewProjection(cam->GetViewMatrix(),
			cam->GetProjectionMatrix());
	}
	else
	{
		RenderContext::SetViewProjection(Mat4::Identity(), Mat4::Identity());
	}

	s_activeScene->Render();
}

void SceneManager::SetActiveScene(std::shared_ptr<Scene> scene)
{
	s_activeScene = scene;
}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	return s_activeScene;
}

bool SceneManager::HasActiveScene()
{
	return s_activeScene != nullptr;
}

Camera* SceneManager::GetMainCamera()
{
	if (!s_activeScene)
		return nullptr;

	Camera* firstCamera = nullptr;

	for (const auto& obj : s_activeScene->GetObjects())
	{
		if (!obj)
			continue;

		Camera* cam = obj->GetComponent<Camera>();
		if (!cam)
			continue;

		if (!firstCamera)
			firstCamera = cam;

		if (cam->isPrimary)
			return cam;
	}

	return firstCamera;
}

bool SceneManager::HasMainCamera()
{
	return GetMainCamera() != nullptr;
}
