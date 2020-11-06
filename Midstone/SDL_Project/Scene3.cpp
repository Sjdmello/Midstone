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
	character1 = new Body(Vec3(0.0f, 50.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 386.0f);
	char1Image = IMG_Load("Ball.png");
	char1Pos = character1->GetPos();

	character2 = new Body(Vec3(1.0f, 50.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 386.0f);
	char2Image = IMG_Load("Ball2.png");
	char2Pos = character2->GetPos();

	return true;
}

void Scene3::OnDestroy() {

}

void Scene3::Update(const float time) {

}

void Scene3::Render() {
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0.0f, 0.0f, 0.0f));

	//temporary render to apease daniel.
	Vec3 position = char1Pos;
	Vec3 screenPosition = projection * position;
	SDL_Rect dstrect;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	SDL_BlitSurface(char1Image, nullptr, screenSurface, &dstrect);

	position = char2Pos;
	screenPosition = projection * position;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	SDL_BlitSurface(char2Image, nullptr, screenSurface, &dstrect);

	SDL_UpdateWindowSurface(window);
}

void Scene3::HandleEvents(const SDL_Event& event) {

}