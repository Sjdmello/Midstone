#ifndef CHARACTER_H
#define CHARACTER_H
#include "GameObject.h"
#include "Body.h"
#include "Debug.h"
#include <SDL.h>
class Character:public GameObject{
protected:
	SDL_Surface* characterImage;
	Body* physics;
	Vec3 moveDir;
	Vec3 currentVel;
	bool tickSwapper;
	bool isMoving;
	bool CharacterOnGround;
	bool CanJump;
	float velCap;
	Debug system;

public:
	Character(Body* body, SDL_Surface* sprite);
	~Character();
	bool onCreate();
	void onDestroy();
	void Update(const float deltatime);
	void Render() const;
	void HandleEvents(const SDL_Event& event);

	inline Body* getPhys() { return physics; }
	inline SDL_Surface* getImage() { return characterImage; }
	inline Vec3 getPos() { return physics->GetPos(); }
	inline Vec3 getVel() { return physics->GetVel(); }
	inline Vec3 getAccel() { return physics->GetAccel(); }

	inline bool getOnGround() { return CharacterOnGround; }
	inline void setOnGround(bool newOnGround) { CharacterOnGround = newOnGround; }

};
#endif
