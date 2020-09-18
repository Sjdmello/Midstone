#include "Scene0.h"
#include <SDL.h>
#include <SDL_Image.h>
Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
}

Scene0::~Scene0(){
}

bool Scene0::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0, 75.0, 0.0, 100.0, 0.0, 1.0); 
	projection = ndc * ortho;

	jetski = new Body(Vec3(0.0f, 10.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 386.0f);
	jetskiImage = IMG_Load("jetski.png");

	red = 128;
	green = 64;
	blue = 32;
	redMax = false;
	greenMax = false;
	blueMax = false;

	timePassed = 0.0;
	framesPassed = 0.0;
	jetskiForce = 500.0;
	doneMoving = false;

	if (jetskiImage == nullptr) {
		return false;
	}
	
	return true;
}

void Scene0::HandleEvents(const SDL_Event& event) {

}

void Scene0::OnDestroy() {
	delete jetski;
	jetski = nullptr;
}

void Scene0::Update(const float time) {
	if (red <= 0) {
		redMax = false;
		red = 0;
		red = red + 6;
	}
	if (red >= 255) {
		redMax = true;
		red = 255;
		red = red - 6;
	}
	if (redMax == true) {
		red--;
	}
	else {
		red++;
	}
	if (green <= 0) {
		greenMax = false;
		green = 0;
		green = green + 6;
	}
	if (green >= 255) {
		greenMax = true;
		green = 255;
		green = green - 6;
	}
	if (greenMax == true) {
		green--;
	}
	else {
		green++;
	}
	if (blue <= 0) {
		blueMax = false;
		blue = 0;
		blue = blue + 6;
	}
	if (blue >= 255) {
		blueMax = true;
		blue = 255;
		blue = blue - 6;
	}
	if (blueMax == true) {
		blue--;
	}
	else {
		blue++;
	}

	if (doneMoving == false) {
		if (timePassed >= 5.5f) {
			jetskiForce = 0.0f;
		}
		if (timePassed >= 10.0f) {
			jetskiForce = -625.0f;
		}
		if (timePassed > 14.5f) {
			jetskiForce = 0.0f;
			doneMoving = true;
		}
		jetski->ApplyForce(Vec3(jetskiForce, 0.0, 0.0));
		jetski->Update(time, 0.0f, 0.0f);
	}
	framesPassed++;
	timePassed = framesPassed * 0.0167f;
}

void Scene0::Render() {
	Vec3 position = jetski->GetPos();
	Vec3 screenPosition = projection * position;
	SDL_Rect dstrect;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, red, green, blue));
	SDL_BlitSurface(jetskiImage, nullptr, screenSurface, &dstrect);

	SDL_UpdateWindowSurface(window);


}