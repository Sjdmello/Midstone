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

	//filling in the info for the characters, probably gonna make these char classes rather than bodies later
	charBody = new Body(Vec3(10.0f, 20.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	character = new Character(charBody, IMG_Load("Ball.png"));

	return true;
}

void Scene3::OnDestroy() {
	//vacuum sealed
	delete charBody;
	delete character;
}

void Scene3::Update(const float time) {
	character->Update(time);
}

void Scene3::Render() {
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0.0f, 0.0f, 0.0f));

	//bunch of math to get the positions right
	Vec3 position = character->getPos();
	Vec3 screenPosition = projection * position;
	SDL_Rect dstrect;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	//actually putting stuff on screen
	SDL_BlitSurface(character->getImage(), nullptr, screenSurface, &dstrect);
	SDL_UpdateWindowSurface(window);
}

void Scene3::HandleEvents(const SDL_Event& event) {
	character->HandleEvents(event);
}