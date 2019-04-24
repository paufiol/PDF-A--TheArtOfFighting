#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"

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
	Uint8 *oldkeyboard = nullptr;
};

#endif // __ModuleInput_H__