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

	printFont = { 0,844, 360 ,12 };
	rArt = { 208,5,96,80 };
	rFightingB = { 0,149,200, 75 };
	rOf = { 10,5,94,63 };
	rSNK = { 7, 378, 73,19 };
	rFighting = { 0,72,200, 75 };
}

ModuleSceneSplash::~ModuleSceneSplash()
{}

// Load assets
bool ModuleSceneSplash::Start()
{
	LOG("Loading Splash scene");
	App->audio->PlayMusic("RESOURCES/Splash_song.ogg", 1);
	splashTitle = App->textures->Load("RESOURCES/InitSplash.png");
	UI = App->textures->Load("RESOURCES/UI_AOF.png");
	printFontBM = App->fonts->Load("RESOURCES/UI_AOF.png", "abcdefghijklmnñopqrstuvwxyz0123456789.'!+,-$_", printFont, 1);

	timer = -50;
	App->render->camera.x = 0;
	if(App->player->IsEnabled() == true) App->player->Disable();
	return true;
}

// UnLoad assets
bool ModuleSceneSplash::CleanUp()
{
	SDL_DestroyTexture(UI);
	SDL_DestroyTexture(splashTitle);
	App->audio->StopMusic();
	LOG("Unloading Splash scene");

	return true;
}

// Update: draw background
update_status ModuleSceneSplash::Update()
{
	// Draw everything --------------------------------------
	//App->render->Blit(graphics, 0, 0, &background, 0.75f); 
	constTimer++;
	if (timer < 65) {
		timer += 5;
		App->render->Blit(splashTitle, (int)timer, 25, &rArt, 0.75f);
	}
	else if (timer < 80 && timer > 65) { timer += 3; App->render->Blit(splashTitle, (int)timer, 25, &rArt, 0.75f); }
	else if (timer < 86 && timer > 80) { timer += 2; App->render->Blit(splashTitle, 80, 25, &rArt, 0.75f); }
	else if (timer < 100 && timer > 86) { timer += 2; App->render->Blit(splashTitle, 170 - (int)timer, 25, &rArt, 0.75f); }
	else { timer++; (App->render->Blit(splashTitle, 70, 25, &rArt, 0.75f)); }

	App->render->Blit(splashTitle, 155, 35, &rOf, 0.75f);

	if (timer < 235 && timer > 100) { timer+=3; (App->render->Blit(splashTitle, 50, 340 - (int)timer, &rFighting, 0.75f)); }
	else if (timer < 285 && timer > 235) 
	{ 
		timer++;
		App->render->Blit(splashTitle, 50, 340 - (int)timer, &rFighting, 0.75f);
		/*App->render->Blit(splashTitle, 70, 310 - (int)timer, &rArt, 0.75f);*/
	}
	else if (timer < 295 && timer >285) 
	{ 
		timer++; 
		(App->render->Blit(splashTitle, 50, -230 + (int)timer, &rFighting, 0.75f));
		/*App->render->Blit(splashTitle, 70, -280 + (int)timer, &rArt, 0.75f);*/
	}
	else if (timer > 295) {
		App->render->Blit(splashTitle, 50, 65, &rFighting, 0.75f);
	/*	App->render->Blit(splashTitle, 70, 15, &rArt, 0.75f);*/
	}
	
	
	if (timer > 95) {
		App->render->Blit(UI, 20, 190, &rSNK, 0.75f);
		App->fonts->BlitText(95, 198, printFontBM, "snk_corp.of_america", printFont);
		App->fonts->BlitText(255, 198, printFontBM, "$1992", printFont);
		App->fonts->BlitText(245, 105, printFontBM, "tm", printFont);
		if (constTimer > 120) { constTimer %= 120; }
		if (constTimer < 60)
		{
			App->fonts->BlitText(80, 155, printFontBM, "push_start_button", printFont);
		}
	}
	
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack((Module*)App->scene_splash, (Module*)App->scene_characterselect, 1.0f);

	}
	return UPDATE_CONTINUE;
}