#ifndef __MODULESCENESPLASH_H__
#define __MODULESCENESPLASH_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Application.h"

struct SDL_Texture;

class ModuleSceneSplash : public Module
{
public:
	ModuleSceneSplash();
	~ModuleSceneSplash();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* Art = nullptr;
	int font_start = -1;
	float timer=0;
	SDL_Rect background, printFont,rArt,rOf, rFightingB;
};

#endif 
