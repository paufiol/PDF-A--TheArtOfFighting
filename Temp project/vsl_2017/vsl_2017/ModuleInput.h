#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
//#include "SDL\include\SDL_joystick.h"
#include "SDL\include\SDL_gamecontroller.h"

typedef unsigned char Uint8;

enum KEY_STATE
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_IDLE
};

enum DIRECTION
{
	UP,
	UPRIGHT,
	RIGHT,
	RIGHTDOWN,
	DOWN,
	DOWNLEFT,
	LEFT,
	LEFTUP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	bool JoystickGetPos(SDL_GameController * gamepad, DIRECTION direction);
	bool ButtonTrigger(SDL_GameController * gamepad, SDL_GameControllerButton button);


public:
	
	Uint8 *keyboard = nullptr;
	
	bool isNew_A[16] = { true };
	bool isNew_B[16] = { true };
	bool isNew_Direction_A[8] = { true };
	bool isNew_Direction_B[8] = { true };
	
	SDL_GameController *controller[2];
	//SDL_Joystick *joystick[2];
	
	//Uint8 *oldkeyboard = nullptr;
};

#endif // __ModuleInput_H__