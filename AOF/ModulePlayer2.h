#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

enum jump
{
	JUMP_DOWN = -1,
	JUMP_NOT = 0,
	JUMP_UP = 1
};

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int hp = 100;
	bool flip = false;
	jump jumping = JUMP_NOT;
	bool keyup = true;

	Animation* current_animation = &idle;

	Collider * player = nullptr;
	Collider * melee = nullptr;
	Collider * koukenCollider = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation jump;
	Animation kick;
	Animation koukenR;
	iPoint position;

};

#endif