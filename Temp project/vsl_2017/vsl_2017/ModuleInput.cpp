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
	if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//SDL_GameControllerAddMappingsFromFile();
	/*for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_NumJoysticks() > 0) {
			joystick[i] = SDL_JoystickOpen(i);
			if (!joystick[i]) {
				LOG("Can't open joystick");
			}
		}
	}*/
	// int control = SDL_NumJoysticks();
	
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller[i] = SDL_GameControllerOpen(i);
			if (controller[i] == NULL) {
				LOG("Can't open controller %s", SDL_GetError());

			}
		}
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	
	SDL_PumpEvents();

	keyboard = (Uint8*)SDL_GetKeyboardState(NULL);

	/*for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller[i] = SDL_GameControllerOpen(i);
			if (controller[i] == NULL) {
				LOG("Can't open controller: %s", SDL_GetError());
			}
		}
	}*/
	
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

	if (SDL_GameControllerGetButton(controller[0], SDL_CONTROLLER_BUTTON_BACK))
	return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	if (joystick[0] != nullptr) SDL_JoystickClose( joystick[0] );
	
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}