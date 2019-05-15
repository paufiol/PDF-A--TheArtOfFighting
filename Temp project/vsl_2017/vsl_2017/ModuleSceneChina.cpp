#include "Globals.h"
#include "Application.h"
#include "ModuleSceneChina.h"
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


ModuleSceneChina::ModuleSceneChina()
{
	chinatown.PushBack({0, 0, 0, 0 });
	chinatown.PushBack({ 0, 0, 0 ,0 });
	chinatown.speed = 0.00;

	
}

ModuleSceneChina::~ModuleSceneChina()
{}

// Load assets
bool ModuleSceneChina::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	App->player->p1Won = false;
	App->player->p2Won = false;
	App->audio->PlayMusic("RESOURCES/MUSIC_FXS/MUSIC/FIGHT_SONG/Ryuhaku_Todoh.ogg", -1);
	graphics = App->textures->Load("RESOURCES/Chinatown.png");
	/*App->scene_splash->printFontBM= App->fonts->Load("UI_AOF.png", "abcdefghijklmnñopqrstuvwxyz?!._", App->scene_splash->printFont, 1);*/

	App->UI->Enable();
	App->player->Enable();	
	App->player2->Enable();
	return ret;
}

// Load assets
bool ModuleSceneChina::CleanUp()
{
	
	App->audio->StopMusic();
	SDL_DestroyTexture(graphics);
	LOG("Unloading Karuta stage");
	App->player->Disable();
	App->player2->Disable();
	App->UI->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneChina::Update()
{
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, 0, 0, &r, 0.75f);
	if (App->player->p1Won)
	{
		App->UI->roundp1 = 1;
		printWinner = { 595,420,116,40 };
		App->render->Blit(App->UI->graphics, 100, 70, &printWinner, 0.75f,false,false);
		if(App->UI->roundp1 == 1)
		{
			App->fade->FadeToBlack((Module*)App->scene_china, (Module*)App->scene_china, 3.0f);
		}

		if (App->UI->roundp1 > 1)
		{
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
			{
				App->fade->FadeToBlack((Module*)App->scene_china, (Module*)App->scene_end, 3.0f);
			}

		}

	}
	if (App->player->p2Won)
	{
		//App->UI->roundp2++;

		printWinner = { 725,420,120,40 };
		App->render->Blit(App->UI->graphics, 100, 70, &printWinner, 0.75f, false, false);
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		{
			App->fade->FadeToBlack((Module*)App->scene_china, (Module*)App->scene_end, 3.0f);
		}

	}

	

	return UPDATE_CONTINUE;
}