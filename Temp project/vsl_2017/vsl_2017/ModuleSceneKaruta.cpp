#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKaruta.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneSplash.h"
#include "ModuleFonts.h"


ModuleSceneKaruta::ModuleSceneKaruta()
{
	background = {0, 0, 538, 240};
	/*App->scene_splash->printFont = { 0,919,421,16 };*/
	printWinner = { 595,420,116,40 };
}

ModuleSceneKaruta::~ModuleSceneKaruta()
{}

// Load assets
bool ModuleSceneKaruta::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	App->audio->PlayMusic("Splash_song.ogg", -1);
	graphics = App->textures->Load("Karuta.png");
	/*App->scene_splash->printFontBM= App->fonts->Load("UI_AOF.png", "abcdefghijklmnñopqrstuvwxyz?!._", App->scene_splash->printFont, 1);*/

	App->UI->Enable();
	App->player->Enable();	
	App->player2->Enable();
	return ret;
}

// Load assets
bool ModuleSceneKaruta::CleanUp()
{
	
	App->audio->StopMusic();
	SDL_DestroyTexture(graphics);
	LOG("Unloading Karuta stage");
	App->player->Disable();
	App->UI->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneKaruta::Update()
{
	
	App->render->Blit(graphics, 0, 0, &background, 0.75f);
	if (App->player->p1Won)
	{
		
		App->render->Blit(App->UI->graphics, 100, 70, &printWinner, 0.75f,false,false);
	}
	if (App->player->p2Won)
	{
		printWinner = { 725,420,120,40 };
		App->render->Blit(App->UI->graphics, 100, 70, &printWinner, 0.75f, false, false);
	}
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack((Module*)App->scene_karuta, (Module*)App->scene_bar, 3.0f);
	}
	return UPDATE_CONTINUE;
}