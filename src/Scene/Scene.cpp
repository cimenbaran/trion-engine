#include "Scene.h"
#include "Object/GameObject.h"

void Scene::AddObject(const std::shared_ptr<GameObject>& object)
{
	if (!object)
		return;

	m_objects.push_back(object);
}

void Scene::RemoveObject(const std::shared_ptr<GameObject>& object)
{
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it)
	{
		if (*it == object)
		{
			m_objects.erase(it);
			return;
		}
	}
	
}

void Scene::Update()
{
	for (auto& obj : m_objects)
		obj->Update();
}

void Scene::Render()
{
	for (auto& obj : m_objects)
		obj->Render();
}


const std::vector<std::shared_ptr<GameObject>>& Scene::GetObjects() const
{
	return m_objects;
}
