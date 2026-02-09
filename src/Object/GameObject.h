#pragma once
#include <vector>
#include <memory>
#include <string>

class Component;
class Transform;

class GameObject
{
public:
	explicit GameObject(const std::string& name);

	const std::string& Name() const { return m_name; }

	Transform* GetTransform() const { return m_transform; }

	template<typename T, typename... Args>
	T* AddComponent(Args&&... args);

	template<typename T>
	T* GetComponent() const;

	void Update();
	void Render(); // Will change in the future

private:
	std::string m_name;

	std::vector<std::unique_ptr<Component>> m_components;
	Transform* m_transform = nullptr;
};

template<typename T, typename ...Args>
T* GameObject::AddComponent(Args && ...args)
{
	static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

	auto comp = std::make_unique<T>(std::forward<Args>(args)...);
	comp->SetOwner(this);
	T* raw = comp.get();

	// Cache Transform Component
	
	if constexpr (std::is_same_v<T, Transform>)
		m_transform = raw;

	m_components.push_back(std::move(comp));
	raw->OnEnable();

	return raw;
}

template<typename T>
T* GameObject::GetComponent() const
{
	for (auto& c : m_components)
	{
		if (auto& casted = dynamic_cast<T*>(c.get()))
			return casted;
	}

	return nullptr;
}
