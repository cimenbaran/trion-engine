#pragma once
#include <vector>
#include <memory>

class GameObject;

class Scene
{
public:
	Scene() = default;

	// Scene Objects
	void AddObject(const std::shared_ptr<GameObject>& object);
	void RemoveObject(const std::shared_ptr<GameObject>& object);

	// Lifecycle
	void Update();
	void Render();

	const std::vector<std::shared_ptr<GameObject>>& GetObjects() const;

private:

	std::vector<std::shared_ptr<GameObject>> m_objects;
};