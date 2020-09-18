#ifndef SCENE2_H
#define SCENE2_H
#include "MMath.h"
#include "Scene.h"
#include "Body.h"
#include <SDL.h>
class Scene2:public Scene {
protected:
	SDL_Window* window;
	Matrix4 projection;
	Body* bodies[2];
	SDL_Surface* ballImage;
	SDL_Surface* ball2Image;
	Vec3 ballPos;
	Vec3 ball2Pos;
public:
	Scene2(SDL_Window* sdlWindow);
	~Scene2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};
#endif

