#include "Platform.h"




Platform::Platform(Body* body)
{
	platform = body;
}

Platform::Platform(float _xLeft, float _xRight, float _yTop, float _yBottom)
{
	xLeft = _xLeft;
	xRight = _xRight;
	yTop = _yTop;
	yBottom = _yBottom;
}

Platform::~Platform()
{
}

bool Platform::onCreate()
{

	return true;
}

void Platform::onDestroy()
{
	if (platform) delete platform;

}

void Platform::Update(const float deltatime)
{
}

void Platform::Render() const
{
}

void Platform::HandleEvents(const SDL_Event& event)
{
}
