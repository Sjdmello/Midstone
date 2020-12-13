#ifndef SCENE4_H
#define SCENE4_H
#include "MMath.h"
#include "Scene.h"
#include "Body.h"
#include "Character.h"
#include "Platform.h"
#include "SpikeBall.h"
#include <SDL.h>
class Scene4 :public Scene {
protected:
	SDL_Window* window;
	Matrix4 projection;

	Character* character;
	Body* charBody;

	SpikeBall* spikeBall;
	Body* spikeBody;


	Platform* P1;
	Platform* P2;
	Platform* P3;
		
	SDL_Surface* backgroundImage;
	//delete this later
	Vec3 min;
	Vec3 max;

public:
	Scene4(SDL_Window* sdlWindow);
	~Scene4();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};
#endif


