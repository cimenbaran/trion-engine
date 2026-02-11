#include "Scene/BootScene.h"
#include "Scene/Scene.h"
#include "Object/GameObject.h"
#include "Components/Transform.h"
#include "Components/FPSCounter.h"
#include "Components/Camera.h"

std::shared_ptr<Scene> BootScene::Create()
{
    auto scene = std::make_shared<Scene>();

    auto root = std::make_shared<GameObject>("Root");
    root->GetTransform()->position = { 0,0,0 };

    auto child = std::make_shared<GameObject>("Child");
    child->GetTransform()->position = { 1,0,0 };
    child->GetTransform()->SetParent(root->GetTransform());

    auto cameraObj = std::make_shared<GameObject>("Main Camera");
    cameraObj->GetTransform()->position = { 0, 1.5f, 5.0f };
    cameraObj->GetTransform()->rotationEulerDeg = { 0, 180.0f, 0 };
    cameraObj->AddComponent<Camera>(); // primary 

    auto fpsObject = std::make_shared<GameObject>("FPS Counter");
    fpsObject->AddComponent<FPSCounter>();

    scene->AddObject(root);
    scene->AddObject(child);
    scene->AddObject(cameraObj);
    scene->AddObject(fpsObject);

    return scene;
}
