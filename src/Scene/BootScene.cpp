#include "Scene/BootScene.h"
#include "Scene/Scene.h"
#include "Object/GameObject.h"
#include "Components/Transform.h"
#include "Components/FPSCounter.h"
#include "Components/Camera.h"
#include "Components/MeshRenderer.h"

std::shared_ptr<Scene> BootScene::Create()
{
    auto scene = std::make_shared<Scene>();

    auto root = std::make_shared<GameObject>("Root");
    root->GetTransform()->position = { 0,0,0 };

    auto child = std::make_shared<GameObject>("Child");
    child->GetTransform()->position = { 1,0,0 };
    child->GetTransform()->SetParent(root->GetTransform());

    auto cameraObj = std::make_shared<GameObject>("Main Camera");
    cameraObj->GetTransform()->position = { 3.0f, 2.0f, 3.5f };
    cameraObj->GetTransform()->rotationEulerDeg = { -15, -45, 0 };
    cameraObj->AddComponent<Camera>(); // primary 

    auto fpsObject = std::make_shared<GameObject>("FPS Counter");
    fpsObject->AddComponent<FPSCounter>();

    auto cube = std::make_shared<GameObject>("Cube");
    cube->GetTransform()->position = { 0, 0, 0 };
    cube->AddComponent<MeshRenderer>();

    scene->AddObject(root);
    scene->AddObject(child);
    scene->AddObject(cameraObj);
    scene->AddObject(fpsObject);
    scene->AddObject(cube);

    return scene;
}
