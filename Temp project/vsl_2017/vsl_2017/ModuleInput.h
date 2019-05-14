#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_joystick.h"
#include "SDL\include\SDL_gamecontroller.h"

typedef unsigned char Uint8;

enum KEY_STATE
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_IDLE
};


class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	
public:
	
	Uint8 *keyboard = nullptr;
	SDL_GameController *controller[2];
	SDL_Joystick *joystick[2];
	
	//Uint8 *oldkeyboard = nullptr;
};

#endif // __ModuleInput_H__