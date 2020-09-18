#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<SDL.h>
class GameObject {

public:
	virtual bool onCreate() = 0;
	virtual void onDestroy() = 0;
	virtual void Update(const float deltatime) = 0;
	virtual void Render() const= 0;
	virtual void HandleEvents(const SDL_Event& event) = 0;
};
#endif