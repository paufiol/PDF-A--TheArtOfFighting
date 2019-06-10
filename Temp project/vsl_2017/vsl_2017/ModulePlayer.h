#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL/include/SDL.h"
#include "SDL\include\SDL_scancode.h"

#define MAX_INPUTS 64

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
	
	bool TestSpecial(SDL_Scancode A, SDL_Scancode B, SDL_Scancode C = SDL_SCANCODE_UNKNOWN, SDL_Scancode D = SDL_SCANCODE_UNKNOWN);
	void StoreInput(SDL_Scancode Scancode) {
		input[inputCount] = Scancode;
		timeInput[inputCount] = SDL_GetTicks();
		inputCount++;
		if (inputCount >= MAX_INPUTS) inputCount %= MAX_INPUTS;
	};
private:
	int inputCount = 1;

public:

	int hp = 100;
	int stamina = 100;
	int plusta;
	fPoint speed;
	
	int input[MAX_INPUTS];
	int timeInput[MAX_INPUTS];

	int clock_parabolla = 0;
	bool flip = false;
	int flip_sign;

	jump jumping = JUMP_NOT;
	bool keyup[69] = { true };//This is not a joke.


	int font_start = -1;
	int wFrame = 0;

	bool dashBack= false;
	int dashTime = 0;

	bool p1Won = false, p2Won = false;
	bool playersMove = false;
	bool godMode;
	Animation* current_animation = &idle;

	int spintime;

	Collider * playerCollider = nullptr;
	Collider * melee = nullptr;
	Collider * block = nullptr;
	Collider * koukenCollider = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	
	SDL_Rect winFrame2;

	Animation idle;
	Animation crouchidle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation jump;
	Animation kick;
	Animation koukenR;
	Animation takeDamage;
	Animation crouchpunch;
	Animation crouchkick;
	Animation damaged;
	Animation back;
	Animation doubleback;
	Animation doubleforward;
	Animation flipback;
	Animation flipforward;
	Animation flipkick;
	Animation flippunch;
	Animation victory;
	Animation defeat;
	Animation jumppunch;
	Animation jumpkick;
	Animation sp1;
	Animation sacargarras;
	Animation provocar;
	Animation firekick;
	Animation multipunch;

	iPoint position;

};

#endif