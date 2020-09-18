#include "Scene1.h"
#include "MMath.h"
#include <SDL.h>
#include <SDL_Image.h>
Scene1::Scene1(SDL_Window* sdlWindow_){
	window = sdlWindow_;
}

Scene1::~Scene1(){

}

bool Scene1::OnCreate(){
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0, 75.0, 0.0, 100.0, 0.0, 1.0);
	projection = ndc * ortho;

	jetski = new Body(Vec3(0.0f, 10.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 386.0f);
	jetskiImage = IMG_Load("jetski.png");

	timePassed = 0.0;
	framesPassed = 0.0;
	jetskiForce = 500.0f;
	forces.x = 500.0f;
	forces.y = 0.0f;
	forces.z = 0.0f;

	return true;
}

void Scene1::OnDestroy(){
	delete jetski;
	jetski = nullptr;
}

void Scene1::Update(const float time){
	if (timePassed > 5.5 && timePassed < 5.6) {
		forces = rotation * forces;
	}
	jetski->ApplyForce(forces);
	jetski->Update(time, 0.0f, 0.0f);
	framesPassed++;
	timePassed = framesPassed * 0.0167f;
}

void Scene1::Render(){
	Vec3 position = jetski->GetPos();
	Vec3 screenPosition = projection * position;
	SDL_Rect dstrect;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0.0f, 0.0f, 0.0f));
	SDL_BlitSurface(jetskiImage, nullptr, screenSurface, &dstrect);

	SDL_UpdateWindowSurface(window);
}

void Scene1::HandleEvents(const SDL_Event& event){

}
