#ifndef SCENE3_H
#define SCENE3_H
#include "MMath.h"
#include "Scene.h"
#include "Body.h"
#include <SDL.h>
class Scene3 :public Scene {
protected:
	SDL_Window* window;
	Matrix4 projection;

	Body* character1;
	SDL_Surface* char1Image;
	Vec3 char1Pos;
	Body* character2;
	SDL_Surface* char2Image;
	Vec3 char2Pos;
public:
	Scene3(SDL_Window* sdlWindow);
	~Scene3();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};
#endif

