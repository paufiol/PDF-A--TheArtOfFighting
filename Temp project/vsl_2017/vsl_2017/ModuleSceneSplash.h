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

	SDL_Texture* UI = nullptr;
	SDL_Texture* splashTitle = nullptr;
	bool art = false, of = false;
	int printFontBM = -1;
	float timer;
	int constTimer = 0;
	SDL_Rect background, printFont,rSNK,rArt,rOf, rFighting , rFightingB, rArtB, rOfB;

	int startTime;
	int currentTIMEY;
	SDL_Rect timerR;
};

#endif 
