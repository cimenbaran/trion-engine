#pragma once

/*

Abstract Component Class

*/


class GameObject;

class Component
{
public:
    virtual ~Component() = default;
    
    GameObject* Owner() const { return m_owner; }
    
    virtual void OnEnable() {}
    virtual void OnDisable() {}
    virtual void Update() {}
    virtual void Render() {}

private:
    friend class GameObject;
    void SetOwner(GameObject* owner) { m_owner = owner; }

    GameObject* m_owner = nullptr;
};