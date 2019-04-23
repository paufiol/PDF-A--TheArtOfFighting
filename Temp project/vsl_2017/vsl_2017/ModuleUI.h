#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "ModuleTextures.h"
#include "Globals.h"
#include "ModuleRender.h"

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Rect lifebar1rect, lifebar2rect, emptylb, timerrect, staminabar1rect,
		staminabar2rect, avatar1rect, avatar2rect;
	int currentTimerposX;
	int startTime;

	SDL_Texture* graphics = nullptr;

};
#endif
