#ifndef SCENE0_H
#define SCENE0_H

#include "MMath.h"
#include "Scene.h"
#include "Body.h"
//#include "Ball.h"
#include <SDL.h>

using namespace MATH;

class Scene0 : public Scene {
private:
	SDL_Window *window;
	Body* jetski;
	SDL_Surface* jetskiImage;
	Matrix4 projection;
	float timePassed;
	float framesPassed;
	float jetskiForce;
	bool doneMoving;
	int red;
	int blue;
	int green;
	bool redMax;
	bool blueMax;
	bool greenMax;
	
public:
	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};

#endif

