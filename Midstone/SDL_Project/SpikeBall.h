#ifndef SPIKEBALL_H
#define SPIKEBALL_H

#include "GameObject.h"
#include "Body.h"
#include <SDL.h>

class SpikeBall:public GameObject {
protected:
	Body* physics;
	SDL_Surface* image;

	float minY;
	float maxY;
	float velCap;
	Vec3 currentVel;
public:
	SpikeBall(Body* body, SDL_Surface* sprite, float minHeight, float maxHeight);
	~SpikeBall();

	bool onCreate();
	void onDestroy();
	void Update(const float deltatime);
	void Render() const;
	void HandleEvents(const SDL_Event& event);

	inline Body* getPhys() { return physics; }
	inline SDL_Surface* getImage() { return image; }
	inline Vec3 getPos() { return physics->GetPos(); }
	inline Vec3 getVel() { return physics->GetVel(); }
	inline Vec3 getAccel() { return physics->GetAccel(); }
};
#endif
