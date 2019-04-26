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
	SDL_Texture* Art = nullptr;
	int font_start = -1;
	float timer = 0;
	SDL_Rect background, printFont, rArt, Charactersbox;
};

#endif 