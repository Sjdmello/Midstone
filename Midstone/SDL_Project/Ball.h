#ifndef BALL_H
#define BALL_H
#include "GameObject.h"
#include <SDL.h>
class Ball:public GameObject{
public:
	bool onCreate();
	void onDestroy();
	void Update(const float deltatime);
	void Render() const;
	void HandleEvents(const SDL_Event& event);
};
#endif
