#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneSplash.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleFonts.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneSplash::ModuleSceneSplash()
{
	// Background / sky
	background.x = 15;
	background.y = 0;
	background.w = 320;
	background.h = 240;

	rArt = { 208,5,96,80 };
	rOf = { 10,5,94,63 };
}

ModuleSceneSplash::~ModuleSceneSplash()
{}

// Load assets
bool ModuleSceneSplash::Start()
{
	LOG("Loading Splash scene");
	App->audio->PlayMusic("Splash_song.ogg", -1);
	graphics = App->textures->Load("Splash.png");

	Art = App->textures->Load("InitSplash.png");

	printFont = { 0,844, 296 ,12 };
	font_start = App->fonts->Load("UI_AOF.png", "abcdefghijklmnñopqrstuvwxyz0123456789", printFont, 1);

	if(App->player->IsEnabled() == true) App->player->Disable();
	return true;
}

// UnLoad assets
bool ModuleSceneSplash::CleanUp()
{
	SDL_DestroyTexture(graphics);
	App->audio->StopMusic();
	LOG("Unloading Splash scene");

	return true;
}

// Update: draw background
update_status ModuleSceneSplash::Update()
{
	// Draw everything --------------------------------------
	//App->render->Blit(graphics, 0, 0, &background, 0.75f); 
	
	if (timer < 65){ timer += 3; App->render->Blit(Art, (int)timer, 10, &rArt, 0.75f); }
	else if (timer < 80 && timer > 65){ timer += 1; App->render->Blit(Art, (int)timer, 10, &rArt, 0.75f); }
	else if(timer < 85 && timer > 80 ){ timer += 2; App->render->Blit(Art, 80, 10, &rArt, 0.75f); }
	else if (timer < 100 && timer > 85) { timer += 1; App->render->Blit(Art, 170 - (int)timer, 10, &rArt, 0.75f); }
	else { timer++; (App->render->Blit(Art, 70, 10, &rArt, 0.75f)); }
	
	App->render->Blit(Art, 155, 20, &rOf, 0.75f);
	
	App->fonts->BlitText(100, 25, font_start, "hello", printFont);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack((Module*)App->scene_splash, (Module*)App->scene_karuta, 2.0f);

	}
	return UPDATE_CONTINUE;
}