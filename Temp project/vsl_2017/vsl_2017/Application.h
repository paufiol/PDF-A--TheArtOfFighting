#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18


class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleCharSelectScene;
class ModuleSceneBar;
class ModuleSceneChina;
class ModuleSceneSplash;
class ModuleSceneEnd;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleAudio;
class ModuleParticles;
class ModuleCollision;
class Module;
class ModuleUI;
class ModuleFonts;
class ModuleSlowdown;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleCharSelectScene *scene_characterselect;
	ModuleSceneBar* scene_bar;
	ModuleSceneChina* scene_china;
	ModuleSceneSplash *scene_splash;
	ModuleSceneEnd *scene_end;
	ModulePlayer* player;
	ModulePlayer2*  player2;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleUI* UI;
	ModuleFonts* fonts;
	ModuleSlowdown* slow;


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__