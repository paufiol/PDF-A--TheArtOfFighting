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
	int ReglaDe3(float num1, float num2, float num3);
	int ColorSelector(int currentstamina);

public:
	SDL_Rect lifebar1rect, lifebar2rect, emptylb, staminabar1rect, staminabar2rect;
	SDL_Rect timerrect, avatar1rect, avatar2rect, whiterect;
	SDL_Rect printFont1, printFont2;
	Animation* current_animation = &Roundball;
	Animation Roundball;
	SDL_Rect BallRec;

	int font_start = -1;
	int font_mini = -1;

	int currentTimerposX;
	int startTime;
	int currenttime = 0;

	int currenthp1, currenthp2;

	int currentsta1, currentsta2, staminatest;

	int characterID[9];
	SDL_Texture* graphics = nullptr;

};
#endif
