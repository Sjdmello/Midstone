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

	Body* character;
	SDL_Surface* charImage;
	Vec3 charPos;
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

