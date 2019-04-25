#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "ModuleTextures.h"
#include "Globals.h"
#include "Animation.h"
#include "ModuleRender.h"

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();
	bool Start();
	update_status Update();
	bool CleanUp();
	int ReglaDe3(int num1, int num2, int num3);

public:
	SDL_Rect lifebar1rect, lifebar2rect, emptylb, staminabar1rect, staminabar2rect;
	SDL_Rect timerrect, avatar1rect, avatar2rect;

	Animation Roundball;

	int currentTimerposX;
	int startTime;

	int currenthp1, currenthp2;
	SDL_Texture* graphics = nullptr;

};
#endif
