#include "GameObject.h"
#include "Components/Component.h"
#include "Components/Transform.h"


GameObject::GameObject(const std::string& name)
	: m_name(name)
{
	AddComponent<Transform>();
}

void GameObject::Update()
{
	for (auto& c : m_components)
	{
		c->Update();
	}
}
void GameObject::Render()
{
	for (auto& c : m_components)
	{
		c->Render();
	}
}