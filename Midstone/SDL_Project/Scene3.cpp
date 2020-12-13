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
	Matrix4 ortho = MMath::orthographic(0.0, 100.0, 0.0, 150.0, 0.0, 1.0);
	projection = ndc * ortho;

	//filling in the info for the character.
	charBody = new Body(Vec3(10.0f, 20.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	character = new Character(charBody, IMG_Load("Ball.png"));

	//filling in the info for the spikeball.
	spikeBody = new Body(Vec3(70.0f, 60.0f, 0.0f), Vec3(0.0f, 15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	spikeBall = new SpikeBall(spikeBody, IMG_Load("SpikeBall.png"), 50.0f, 85.0f);

	backgroundImage = IMG_Load("Background.jpg");

	//screen size.
	min = Vec3(-1.0f, 35.0f, 0.0f);
	max = Vec3(95.5f, 150.5f, 1.0f);

	return true;
}

void Scene3::OnDestroy() {
	//vacuum sealed
	if (window) delete window;
	if (charBody) delete charBody;
	if (character) delete character;
	if (spikeBody) delete spikeBody;
	if (spikeBall) delete spikeBall;
	if (backgroundImage) delete backgroundImage;
}

void Scene3::Update(const float time) {
	character->Update(time);
	spikeBall->Update(time);
	//printf("%f %f %f \n", character->getPos().x, character->getPos().y, character->getPos().z);

	//checks to keep character on screen.
	if (character->getPos().x > max.x - character->getPhys()->GetRad()) {
		character->getPhys()->SetPos(Vec3(max.x - character->getPhys()->GetRad(), character->getPos().y, character->getPos().z));
	}
	if (character->getPos().x < min.x + character->getPhys()->GetRad()) {
		character->getPhys()->SetPos(Vec3(min.x + character->getPhys()->GetRad(), character->getPos().y, character->getPos().z));
	}
	if (character->getPos().y > max.y - character->getPhys()->GetRad()) {
		character->getPhys()->SetPos(Vec3(character->getPos().x, max.y - character->getPhys()->GetRad(), character->getPos().z));
	}
	if (character->getPos().y < min.y + character->getPhys()->GetRad()) {
		character->getPhys()->SetPos(Vec3(character->getPos().x, min.y + character->getPhys()->GetRad(), character->getPos().z));
	}

}

void Scene3::Render() {
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0.0f, 0.0f, 0.0f));

	Vec3 position = Vec3(0.0f, 150.0f, 0.0f);
	Vec3 screenPosition = projection * position;
	SDL_Rect dstrect;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	SDL_BlitSurface(backgroundImage, nullptr, screenSurface, &dstrect);

	position = spikeBall->getPos();
	screenPosition = projection * position;
	dstrect;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	SDL_BlitSurface(spikeBall->getImage(), nullptr, screenSurface, &dstrect);

	//bunch of math to get the positions right
	position = character->getPos();
	screenPosition = projection * position;
	dstrect;
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