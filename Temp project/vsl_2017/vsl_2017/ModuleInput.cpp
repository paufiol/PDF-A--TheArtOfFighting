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
	if (SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
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
	
	

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	
	//SDL_memcpy(oldcontroller, controller, sizeof(Uint8)*SDL_CONTROLLER_BUTTON_MAX*2);

	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller[i] = SDL_GameControllerOpen(i);
			if (controller[i] == NULL) {
				LOG("Can't open controller %s", SDL_GetError());

			}
		}
	}

	SDL_PumpEvents();

	keyboard = (Uint8*)SDL_GetKeyboardState(NULL);

	

	if(keyboard[SDL_SCANCODE_ESCAPE])
	return update_status::UPDATE_STOP;

	if (SDL_GameControllerGetButton(controller[0], SDL_CONTROLLER_BUTTON_BACK))
	return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	//if (joystick[0] != nullptr) SDL_JoystickClose( joystick[0] );
	if (controller[0] != nullptr) SDL_GameControllerClose(controller[0]);
	if (controller[1] != nullptr) SDL_GameControllerClose(controller[1]);
	
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}

bool ModuleInput::JoystickGetPos(SDL_GameController * gamepad, DIRECTION direction) {
	bool ret = false;
	
	int deadzone = 7849;
	int xAxis = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTX);
	int yAxis = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTY);

	if (xAxis > deadzone && direction == RIGHT) ret = true;
	if (xAxis < -deadzone && direction == LEFT) ret = true;

	if (yAxis < -deadzone && direction == UP) ret = true;
	if (yAxis > deadzone && direction == DOWN) ret = true;

	if (yAxis < -deadzone && xAxis > deadzone && direction == UPRIGHT) ret = true;
	if (yAxis > deadzone && xAxis > -deadzone && direction == DOWNLEFT) ret = true;
	if (yAxis > deadzone && xAxis > deadzone && direction == LEFTUP) ret = true;
	if (yAxis < -deadzone && xAxis > -deadzone && direction == RIGHTDOWN) ret = true;

	return ret;
}

bool ModuleInput::ButtonTrigger(SDL_GameController * gamepad, SDL_GameControllerButton button) {
	if (gamepad == controller[0]) {
		if (SDL_GameControllerGetButton(controller[0], button) == true && SDL_GameControllerGetButton(oldcontroller[0], button)) {
			return true;		
		}
	}
	if (gamepad == controller[1]) {
		if (SDL_GameControllerGetButton(controller[1], button) == true && SDL_GameControllerGetButton(oldcontroller[1], button)) {
			return true;
		}
	}

	return false;
}