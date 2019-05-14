#ifndef __MODULESCENECHINA_H__
#define __MODULESCENECHINA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Application.h"

struct SDL_Texture;

class ModuleSceneChina : public Module
{
public:
	ModuleSceneChina();
	~ModuleSceneChina();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation chinatown;
	Animation* current_animation = &chinatown;
	SDL_Rect background,printWinner;
};

#endif // __MODULESCENECHINA_H__