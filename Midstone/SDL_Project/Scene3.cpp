#include "Scene3.h"
#include <SDL.h>
#include <SDL_Image.h>

Scene3::Scene3(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
}

Scene3::~Scene3() {

}

bool Scene3::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0, 75.0, 0.0, 100.0, 0.0, 1.0);
	projection = ndc * ortho;

	character = new Body(Vec3(0.0f, 50.0f, 0.0f), Vec3(20.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 386.0f);
	charImage = IMG_Load("Ball.png");
	charPos = character->GetPos();

	return true;
}

void Scene3::OnDestroy() {

}

void Scene3::Update(const float time) {

}

void Scene3::Render() {
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0.0f, 0.0f, 0.0f));

	SDL_UpdateWindowSurface(window);
}

void Scene3::HandleEvents(const SDL_Event& event) {

}