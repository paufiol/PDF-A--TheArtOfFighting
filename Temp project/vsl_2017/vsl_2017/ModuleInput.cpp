#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	
	SDL_PumpEvents();

	keyboard = (Uint8*)SDL_GetKeyboardState(NULL);
	
	/*if (keyboard != nullptr && oldkeyboard != nullptr) {
		//SDL_SCANCODE_Z; SDL_SCANCODE_A; SDL_SCANCODE_SPACE;
		for (int i = 4; i < 69; i++) {
			if (&keyboard[i] == &oldkeyboard[i] && keyboard[i] == KEY_DOWN)			 
			{ keyboard[i] = KEY_REPEAT; }
			//if (keyboard[i] != oldkeyboard[i] && keyboard[i] != SDL_KEYDOWN) { keyboard[i] = KEY_UP; }
		}
	}
	oldkeyboard = keyboard;*/

	if(keyboard[SDL_SCANCODE_ESCAPE])
	return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}