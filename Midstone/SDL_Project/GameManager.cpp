#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene2.h"
#include "Scene3.h"
#include <iostream>

GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 850;
	const int SCREEN_HEIGHT = 600;
	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (ptr == nullptr) {
		OnDestroy();
		return false;
	}
	if (ptr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	currentScene = new Scene3(ptr->GetSDL_Window());
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	timer->Start();
	while (isRunning) {
		timer->UpdateFrameTicks();
		HandleEvents();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

void GameManager::HandleEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_QUIT) {
			isRunning = false;
		}
		else {
			currentScene->HandleEvents(sdlEvent);
		}
	}
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}