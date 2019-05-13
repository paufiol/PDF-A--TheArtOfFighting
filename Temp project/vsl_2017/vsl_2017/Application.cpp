#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleCharSelectScene.h"
#include "ModuleSceneBar.h"
#include "ModuleSceneKaruta.h"
#include "ModuleSceneSplash.h"
#include "ModuleSceneEnd.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleSceneLee.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	modules[5] = scene_karuta = new ModuleSceneKaruta();
	modules[6] = scene_bar = new ModuleSceneBar();
	modules[7] = scene_splash = new ModuleSceneSplash();
	modules[8] = scene_end = new ModuleSceneEnd();
	modules[9] = scene_characterselect = new ModuleCharSelectScene();
	modules[10] = player = new ModulePlayer();
	modules[11] = player2 = new ModulePlayer2();
	modules[12] = particles = new ModuleParticles();
	modules[13] = collision = new ModuleCollision();
	modules[14] = fade = new ModuleFadeToBlack();
	modules[15] = UI = new ModuleUI();
	modules[16] = fonts = new ModuleFonts();
	modules[17] = scene_lee = new ModuleSceneLee();

	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	player2->Disable();
	// Disable the map that you do not start with
	scene_characterselect->Disable();
	scene_karuta->Disable();
	scene_bar->Disable();
	scene_end->Disable();
	scene_splash->Enable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}