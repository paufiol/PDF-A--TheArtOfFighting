#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;



class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* A, Collider* B);

public:

	int hp = 100;
	
	bool flip = false;
	int flip_sign;

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