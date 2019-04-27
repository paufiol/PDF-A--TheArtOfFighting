#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;


class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* A, Collider* B);


public:

	int hp = 100;
	int stamina = 100;
	bool flip = true;
	jump jumping = JUMP_NOT;
	bool keyup = true;

	bool p2Won = false;

	fPoint speed;

	Animation* current_animation = &idle;

	Collider * playerCollider = nullptr;
	Collider * melee = nullptr;
	Collider * koukenCollider = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation jump;
	Animation kick;
	Animation crouchidle;
	Animation koukenR;
	Animation damaged;
	Animation back;
	iPoint position;


};

#endif
