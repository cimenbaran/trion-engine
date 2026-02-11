#pragma once
#include <memory>

class Scene;

class ISceneFactory
{
public:
    virtual ~ISceneFactory() = default;
    virtual std::shared_ptr<Scene> Create() = 0;
};
