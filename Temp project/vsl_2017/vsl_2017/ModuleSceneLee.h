#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Application.h"

struct SDL_Texture;

class ModuleSceneLee : public Module
{
public:
	ModuleSceneLee();
	~ModuleSceneLee();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect background, printWinner;
};

#endif // __MODULESCENEHONDA_H__
