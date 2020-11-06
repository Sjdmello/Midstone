#include "Scene2.h"
#include "Collider.h"
#include "MMath.h"
#include <SDL.h>
#include <SDL_Image.h>
Scene2::Scene2(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
}

Scene2::~Scene2() {

}

bool Scene2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0, 75.0, 0.0, 100.0, 0.0, 1.0);
	projection = ndc * ortho;

	bodies[0] = new Body(Vec3(0.0f, 50.0f, 0.0f), Vec3(20.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 386.0f);
	bodies[1] = new Body(Vec3(60.0f, 50.0f, 0.0f), Vec3(-20.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 386.0f);
	ballImage = IMG_Load("Ball.png");
	ball2Image = IMG_Load("Ball2.png");

	ballPos = bodies[0]->GetPos();
	ball2Pos = bodies[1]->GetPos();

	return true;
}

void Scene2::OnDestroy() {
	for (int i = 0; i < 2;i++) {
		delete bodies[i];
	}
}

void Scene2::Update(const float time) {

	

	if (Collider::SphereSphereCollision(*bodies[1], *bodies[0]) == true) {
		Collider::SphereSphereCollisionResponse(*bodies[1], *bodies[0]);
	}

	for (int i = 0; i < 2; i++) {
		bodies[i]->Update(time, 0.0f);
	}
}

void Scene2::Render() {

	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0.0f, 0.0f, 0.0f));

	for (int i = 0; i < 2; i++) {
		Vec3 position = bodies[i]->GetPos();
		Vec3 screenPosition = projection * position;
		SDL_Rect dstrect;
		dstrect.x = static_cast<int>(screenPosition.x);
		dstrect.y = static_cast<int>(screenPosition.y);
		dstrect.h = 0;
		dstrect.w = 0;

		if (i == 0) {
			SDL_BlitSurface(ballImage, nullptr, screenSurface, &dstrect);
		}
		else {
			SDL_BlitSurface(ball2Image, nullptr, screenSurface, &dstrect);
		}
	}

	SDL_UpdateWindowSurface(window);
}

void Scene2::HandleEvents(const SDL_Event& event) {

}