#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneSplash.h"
#include "ModuleSceneEnd.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleFonts.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneEnd::ModuleSceneEnd()
{
	textR = { 279,416,271,48 };
	printFont = { 0,844, 360 ,12 };
	ryoR = { 0,0,128,123 };
	// Background / sky

}

ModuleSceneEnd::~ModuleSceneEnd()
{}

// Load assets
bool ModuleSceneEnd::Start()
{
	LOG("Loading End scene");
	App->audio->PlayMusic("Splash_song.ogg", -1);
	UIsprite = App->textures->Load("UI_AOF.png");
	portraitRyo = App->textures->Load("RyoPortrait.png");

	printFontBM = App->fonts->Load("UI_AOF.png", "abcdefghijklmnñopqrstuvwxyz0123456789.'!+,-$_", printFont, 1);
	App->player->Disable();

	return true;
}

// UnLoad assets
bool ModuleSceneEnd::CleanUp()
{
	App->audio->StopMusic();
	SDL_DestroyTexture(UIsprite);
	SDL_DestroyTexture(portraitRyo);
	LOG("Unloading Splash scene");
	
	return true;
}

// Update: draw background
update_status ModuleSceneEnd::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(UIsprite, 40, 170, &textR, 0.75f);
	App->render->Blit(portraitRyo, 46, 47, &ryoR, 0.75f);
	App->fonts->BlitText(50,180, printFontBM, "anytime_anywhere_cross_my_path", printFont);
	App->fonts->BlitText(50, 196, printFontBM, "again_and_you_are_mine!", printFont);
	App->fonts->BlitText(205, 35, printFontBM, "waiting_for", printFont);
	App->fonts->BlitText(200, 52, printFontBM, "a_challenger", printFont);

	int currenttime = 0;
	currenttime = (SDL_GetTicks() - startTime) / 1000;

		currentTimerposX = 800 - (80 * (currenttime - 5));
		if (currenttime > 10) currentTimerposX = 800 - (80 * (10 - 5)); //si es mayor de 60 se queda en 0.
		timerR = { currentTimerposX,253,80,96 };
		App->render->Blit(UIsprite, 200, 72, &timerR, 1.0f, false, false);



	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack((Module*)App->scene_end, (Module*)App->scene_splash, 1.0f);
	}
	return UPDATE_CONTINUE;
}