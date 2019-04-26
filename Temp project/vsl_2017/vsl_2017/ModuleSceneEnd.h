#ifndef __MODULESCENEEND_H__
#define __MODULESCENEEND_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Application.h"

struct SDL_Texture;

class ModuleSceneEnd : public Module
{
public:
	ModuleSceneEnd();
	~ModuleSceneEnd();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int printFontBM = -1;
	SDL_Texture* UIsprite = nullptr,*portraitRyo = nullptr;
	SDL_Rect textR, printFont,ryoR;
	int currentTimerposX;
	int startTime;
	SDL_Rect timerR;

};

#endif
