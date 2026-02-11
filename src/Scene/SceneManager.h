#pragma once
#include <memory>

class Scene;
class Camera;

class SceneManager 
{
public:
	static void LoadInitialScene();
	static void Update();
	static void Render();

	static void SetActiveScene(std::shared_ptr<Scene> scene);
	static std::shared_ptr<Scene> GetActiveScene();
	static bool HasActiveScene();


	/*
	Returns nullptr if no active camera present in scene
	*/
	static Camera* GetMainCamera(); 
	static bool HasMainCamera();

private:
	static std::shared_ptr<Scene> s_activeScene;
};