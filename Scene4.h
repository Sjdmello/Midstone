#ifndef SCENE4_H
#define SCENE4_H
#include "MMath.h"
#include "Scene.h"
#include "Body.h"
#include "Character.h"
#include <SDL.h>
class Scene4 :public Scene {
protected:
	SDL_Window* window;
	Matrix4 projection;

	Character* character;
	Body* charBody;

	//delete this later
	Vec3 min;
	Vec3 max;

public:
	Scene4(SDL_Window* sdlWindow);
	~Scene4();
	bool OnCreate();
	bool CharacterOnGround;
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
};
#endif


