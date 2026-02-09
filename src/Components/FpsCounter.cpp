#include "FpsCounter.h"
#include "Core/Time.h"
#include <iostream>

void FPSCounter::Update()
{
	m_timer += Time::DeltaTime();
	m_frames++;

	if (m_timer >= 1.0f)
	{
		std::cout << "FPS: " << m_frames << std::endl;
		m_frames = 0;
		m_timer = 0.0f;
	}
}