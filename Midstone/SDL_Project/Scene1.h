#ifndef SCENE_1_H
#define SCENE_1_H
#include "MMath.h"
#include "Scene.h"
#include "Body.h"
#include <SDL.h>
class Scene1:public Scene {
protected:
	SDL_Window* window;
	Body* jetski;
	SDL_Surface* jetskiImage;
	Matrix4 projection;
	Matrix4 rotation;
	Vec3 forces;
	float jetskiForce;
	float timePassed;
	float framesPassed;
public:
	Scene1(SDL_Window* sdlWindow);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};
#endif
