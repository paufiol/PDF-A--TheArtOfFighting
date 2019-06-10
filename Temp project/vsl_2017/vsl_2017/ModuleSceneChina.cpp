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
#include "ModuleSlowdown.h"


ModuleSceneChina::ModuleSceneChina()
{
	chinatown.PushBack({0, 0, 548, 224 });
	chinatown.PushBack({ 0, 224, 548,224 });
	chinatown.PushBack({ 0, 448, 548,224 });
	chinatown.PushBack({ 0, 672, 548,224 });
	chinatown.speed = 0.03;

	printRound = { 512,108,100,16 };
	printFight = { 512,140,80,16 };
	
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
	UI = App->textures->Load("RESOURCES/UI_AOF.png");
	/*App->scene_splash->printFontBM= App->fonts->Load("UI_AOF.png", "abcdefghijklmnñopqrstuvwxyz?!._", App->scene_splash->printFont, 1);*/
	
	App->player->playersMove = false;
	initialScene = 0;
	if (P1bool) { roundP1++; !P1bool; }
	if (P2bool) { roundP2++; !P2bool; }

	App->UI->Enable();
	App->player->Enable();	
	App->player2->Enable();
	App->player->position.x = 185;
	App->player->position.y = 112;
	App->player2->position.x = 310;
	App->player2->position.y = 112;
	App->player->current_animation = &App->player->idle;
	App->player2->current_animation = &App->player2->idle;
	return ret;
}

// Load assets
bool ModuleSceneChina::CleanUp()
{
	
	App->audio->StopMusic();
	if (graphics != nullptr) { SDL_DestroyTexture(graphics); }
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
	initialScene++;
	if (initialScene < 120)
	{
		App->render->Blit(UI, 230, 110, &printRound, 1.0f, false, true);

	}
	if (initialScene < 180 && initialScene >121)
	{
		App->render->Blit(UI, 240, 110, &printFight, 1.0f, false, true);
	}
	if (initialScene == 181) { App->player->playersMove = true; }

	if (App->player->p1Won)
	{
		
		if (roundP1 == 1)
		{
			App->slow->StartSlowdown(60, 60);
			if (App->slow->finished)
			{
				P1bool = true;
				App->fade->FadeToBlack((Module*)App->scene_china, (Module*)App->scene_end, 3.0f);
			}
		}
		
		if (roundP1 == 0)
		{	
			App->slow->StartSlowdown(60, 60);	
			if (App->slow->finished)
			{
				printRound = { 512,171,107,16 };
				P1bool = true;
				App->fade->FadeToBlack((Module*)App->scene_china, (Module*)App->scene_china, 3.0f);
			} 
		}
		printWinner = { 595,420,116,40 };
		App->render->Blit(App->UI->graphics, 100, 70, &printWinner, 0.75f, false, false);
	}
	if (App->player->p2Won)
	{
		if (roundP2 == 1)
		{
			App->slow->StartSlowdown(60, 60);
			if (App->slow->finished)
			{
				P2bool = true;
				App->fade->FadeToBlack((Module*)App->scene_china, (Module*)App->scene_end, 3.0f);
			}
		}

		if (roundP2 == 0)
		{
			App->slow->StartSlowdown(60, 60);
			if (App->slow->finished)
			{
				printRound = { 512,171,107,16 };
				P2bool = true;
				App->fade->FadeToBlack((Module*)App->scene_china, (Module*)App->scene_china, 3.0f);
			}
		}
		printWinner = { 725,420,120,40 };
		App->render->Blit(App->UI->graphics, 100, 70, &printWinner, 0.75f, false, false);

	}
	
	if (App->UI->currenttime == 60) //Victory in case of time up.
	{
	
		if (App->player->hp > App->player2->hp)  App->player->p1Won = true;
		if (App->player->hp < App->player2->hp)  App->player->p2Won = true;
		if (App->player->hp == App->player2->hp)
		{
			if (roundP2 == 0 || roundP1 == 0)
			{
				printWinner = { 596,483,104,16 };
				App->slow->StartSlowdown(20, 20);
				App->fade->FadeToBlack((Module*)App->scene_china, (Module*)App->scene_china, 3.0f);	
			}
			if (roundP2 == 1 || roundP1 == 1) 
			{
				printWinner = { 596,483,104,16 };
				App->slow->StartSlowdown(20, 20);
				App->fade->FadeToBlack((Module*)App->scene_china, (Module*)App->scene_end, 3.0f);
			}
				
			App->render->Blit(App->UI->graphics, 100, 70, &printWinner, 0.75f, false, false);
		}
	}

	return UPDATE_CONTINUE;
}