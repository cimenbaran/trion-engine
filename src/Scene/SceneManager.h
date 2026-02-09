#pragma once
#include <memory>

class Scene;

class SceneManager 
{
public:
	static void LoadInitialScene();
	static void Update();
	static void Render();

private:
	static std::shared_ptr<Scene> s_activeScene;
};