#ifndef PLATFORM_H
#define PLATFORM_H
#include "GameObject.h"
#include "Body.h"
#include <SDL.h>
class Platform
{
protected:
	Body* platform;
	float xLeft;
	float xRight;
	float yTop;
	float yBottom;


public:


	
Platform(Body* body);
Platform(float _xLeft, float _xRight, float _yTop, float _yBottom);
~Platform();
bool onCreate();
void onDestroy();
void Update(const float deltatime);
void Render() const;
void HandleEvents(const SDL_Event& event);

inline float getLeft() { return xLeft; }
inline float getRight() { return xRight; }
inline float getTop() { return yTop; }
inline float getBottom() { return yBottom; }

};

#endif