#ifndef __MODULECHARSELECTSCENE_H__
#define __MODULECHARSELECTSCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Application.h"

struct SDL_Texture;

class ModuleCharSelectScene : public Module
{
public:
	ModuleCharSelectScene();
	~ModuleCharSelectScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* Art = nullptr;
	int font_start = -1;
	int font_mini = -1;

	int currentTimerposX;
	int startTime;
	SDL_Rect timerR;

	bool keyup[69] = { true };

	SDL_Rect printFont, printFont2, rArt, Charactersbox, P1Selector, P2Selector, CharactersR[8], PortraitP1, NameP1, PortraitP2, NameP2;

	int P1posX[4] = {96, 124, 152, 180};
	int P1posY[2] = {151, 178};
	int ix = 1;
	int iy = 0;
	int P2posX[4] = { 96, 124, 152, 179 };
	int P2posY[2] = { 154, 181 };
	int jx = 2;
	int jy = 0;
};

#endif 