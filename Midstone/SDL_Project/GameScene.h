#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "MMath.h"
#include "Scene.h"
#include "Body.h"
#include "Character.h"
#include "Platform.h"
#include "SpikeBall.h"
#include <SDL.h>
class GameScene :public Scene {
protected:
	//member variables
	SDL_Window* window;
	Matrix4 projection;
	Character* character;
	Body* charBody;
	SpikeBall* spikeBall;
	Body* spikeBody;
	SDL_Surface* backgroundImage;

	Platform* P1;
	Platform* P2;
	Platform* P3;
		
	Vec3 min;
	Vec3 max;

public:
	GameScene(SDL_Window* sdlWindow);
	~GameScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};
#endif


