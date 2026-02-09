#include "SceneManager.h"
#include "Scene.h"
#include "Object/GameObject.h"
#include "Components/Transform.h"
#include "Components/FPSCounter.h"

std::shared_ptr<Scene> SceneManager::s_activeScene;

void SceneManager::LoadInitialScene()
{
	s_activeScene = std::make_shared<Scene>();

	auto root = std::make_shared<GameObject>("Root");
	root->GetTransform()->position = { 0,0,0 };

	auto child = std::make_shared<GameObject>("Child");
	child->GetTransform()->position = { 1,0,0 };
	child->GetTransform()->SetParent(root->GetTransform());

	auto fpsObject = std::make_shared<GameObject>("FPS Counter");
	fpsObject->AddComponent<FPSCounter>();


	s_activeScene->AddObject(root);
	s_activeScene->AddObject(child);
	s_activeScene->AddObject(fpsObject);
}

void SceneManager::Update()
{
	s_activeScene->Update();
}

void SceneManager::Render()
{
	s_activeScene->Render();
}
