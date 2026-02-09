#pragma once
#include "Component.h"

class FPSCounter : public Component 
{
public:
	void Update() override;

private:
	float m_timer = 0.0f;
	int m_frames = 0;
};
