#pragma once
#include "Scene/ISceneFactory.h"

class BootScene : public ISceneFactory
{
public:
    std::shared_ptr<Scene> Create() override;
};