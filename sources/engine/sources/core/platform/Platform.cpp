#include <string>
#include <iostream>
#include "Platform.h"


Platform* Platform::m_platform = nullptr;
AspectRatio Platform::m_aspect_ratio;
DisplayResolution Platform::m_resolution;


Platform::Platform() : m_window(nullptr)
{
	
}

Platform::~Platform()
{
	
}

void Platform::SetWindowAspectRatio(const AspectRatio& aspect_ratio)
{
	m_aspect_ratio.x = aspect_ratio.x;
	m_aspect_ratio.y = aspect_ratio.y;
}

void Platform::SetWindowResolution(const DisplayResolution& resolution)
{
	m_resolution.width = resolution.width;
	m_resolution.height = resolution.height;
}