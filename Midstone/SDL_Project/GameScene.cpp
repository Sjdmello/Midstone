#include "GameScene.h"
#include <SDL.h>
#include <SDL_Image.h>

GameScene::GameScene(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
}

GameScene::~GameScene() {
}


bool GameScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0, 100.0, 0.0, 150.0, 0.0, 1.0);
	projection = ndc * ortho;

	//filling in the info for the character.
	charBody = new Body(Vec3(10.0f, 38.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 0.1f);
	character = new Character(charBody, IMG_Load("Ball.png"));
	
	//filling in the info for the spikeball.
	spikeBody = new Body(Vec3(70.0f, 60.0f, 0.0f), Vec3(0.0f, 15.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	spikeBall = new SpikeBall(spikeBody, IMG_Load("SpikeBall.png"), 50.0f, 120.0f);
	spikeBall->getPhys()->SetRad(2.5f);

	// Creating platforms
	P1 = new Platform(12.0f,29.0f,78.0f,60.0f);
	P2 = new Platform(36.0f, 59.0f, 120.0f, 102.0f);
	P3 = new Platform(64.0f, 87.0f, 78.0f, 60.0f);

	backgroundImage = IMG_Load("Background.jpg");
	
	//sets a boundary so the objects can't move off screen.
	min = Vec3(-1.0f, 35.0f, 0.0f);
	max = Vec3(95.5f, 150.0f, 1.0f);

	return true;
}



void GameScene::OnDestroy() {
	//delete all pointers.
	if (charBody) delete charBody;
	if (character) delete character;
	if (spikeBody) delete spikeBody;
	if (spikeBall) delete spikeBall;
	if (backgroundImage) delete backgroundImage;
}

void GameScene::Update(const float time) {
	character->Update(time);
	spikeBall->Update(time);
	
	//check object collisions.
	if (Collider::SphereSphereCollision(*character->getPhys(), *spikeBall->getPhys()) == true) {
		Collider::SphereSphereCollisionResponse(*character->getPhys(), *spikeBall->getPhys());
	}

	//check to keep character on screen.
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

	//Keep spikeball on screen.
	if (spikeBall->getPos().x > max.x - spikeBall->getPhys()->GetRad()) {
		spikeBall->getPhys()->SetPos(Vec3(max.x - spikeBall->getPhys()->GetRad(), spikeBall->getPos().y, spikeBall->getPos().z));
	}
	if (spikeBall->getPos().x < min.x + spikeBall->getPhys()->GetRad()) {
		spikeBall->getPhys()->SetPos(Vec3(min.x + spikeBall->getPhys()->GetRad(), spikeBall->getPos().y, spikeBall->getPos().z));
	}
	if (spikeBall->getPos().y > max.y - spikeBall->getPhys()->GetRad()) {
		spikeBall->getPhys()->SetPos(Vec3(spikeBall->getPos().x, max.y - spikeBall->getPhys()->GetRad(), spikeBall->getPos().z));
	}
	if (spikeBall->getPos().y < min.y + spikeBall->getPhys()->GetRad()) {
		spikeBall->getPhys()->SetVel(Vec3(-spikeBall->getPhys()->GetVel()));
	}

	//p1
	if (character->getPos().x >= P1->getLeft() && character->getPos().x <= P1->getRight()
		&& character->getPos().y >= P1->getBottom() 
		&& character->getPos().y + character->getPhys()->GetRad()<= P1->getTop()) {
		printf("Collision \n");
		if (character->getPos().y >= P1->getTop() - 3.0f) {
			printf("Collision");
			character->setOnGround(true);
			character->getPhys()->SetVel(Vec3(character->getVel().x, 0.0f, character->getVel().z));
		} else {
			character->getPhys()->SetVel(Vec3(-character->getVel().x, -character->getVel().y, -character->getVel().z));
		}
	}
	//p2
	if (character->getPos().x >= P2->getLeft() && character->getPos().x <= P2->getRight()
		&& character->getPos().y >= P2->getBottom()
		&& character->getPos().y + character->getPhys()->GetRad() <= P2->getTop()) {
		if (character->getPos().y >= P2->getTop() - 3.0f) {
			character->setOnGround(true);
			character->getPhys()->SetVel(Vec3(character->getVel().x, 0.0f, character->getVel().z));
		} else {
			character->getPhys()->SetVel(Vec3(-character->getVel().x, -character->getVel().y, -character->getVel().z));
		}
	}
	//p3
	if (character->getPos().x >= P3->getLeft() && character->getPos().x <= P3->getRight()
		&& character->getPos().y >= P3->getBottom()
		&& character->getPos().y + character->getPhys()->GetRad() <= P3->getTop()) {
		if (character->getPos().y >= P3->getTop() - 3.0f) {
			character->setOnGround(true);
			character->getPhys()->SetVel(Vec3(character->getVel().x, 0.0f, character->getVel().z));
		} else {
			character->getPhys()->SetVel(Vec3(-character->getVel().x, -character->getVel().y, -character->getVel().z));
		}
	}
	
}

void GameScene::Render() {
	SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0.0f, 0.0f, 0.0f));

	//renders the background.
	Vec3 position = Vec3(0.0f, 150.0f, 0.0f);
	Vec3 screenPosition = projection * position;
	SDL_Rect dstrect;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	SDL_BlitSurface(backgroundImage, nullptr, screenSurface, &dstrect);

	//character render
	position = character->getPos();
	screenPosition = projection * position;
	dstrect;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	SDL_BlitSurface(character->getImage(), nullptr, screenSurface, &dstrect);

	//spike ball render
	position = spikeBall->getPos();
	screenPosition = projection * position;
	dstrect;
	dstrect.x = static_cast<int>(screenPosition.x);
	dstrect.y = static_cast<int>(screenPosition.y);
	dstrect.h = 0;
	dstrect.w = 0;

	SDL_BlitSurface(spikeBall->getImage(), nullptr, screenSurface, &dstrect);

	SDL_UpdateWindowSurface(window);
}

void GameScene::HandleEvents(const SDL_Event& event) {
	character->HandleEvents(event);
}