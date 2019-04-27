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
#include "ModuleCharSelectScene.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleCharSelectScene::ModuleCharSelectScene()
{
	Charactersbox = { 111, 0, 112, 56 };
	P1Selector = { 130, 65, 28 , 31};
	PortraitP1 = { 0, 0, 128,123};
	for (int i = 0; i < 8; i++)
	{
		CharactersR[i] = { 0,(i * 24),24,24 };
	}
}

ModuleCharSelectScene::~ModuleCharSelectScene()
{}

// Load assets
bool ModuleCharSelectScene::Start()
{
	LOG("Loading Selector scene");
	graphics = App->textures->Load("UI_AOF.png");
	printFont = { 4,870, 318 ,13 };
	font_start = App->fonts->Load("UI_AOF.png", "abcdefghijklmnopqrstuvwxyz", printFont, 1);

	
	return true;
}

// UnLoad assets
bool ModuleCharSelectScene::CleanUp()
{
	SDL_DestroyTexture(graphics);
	LOG("Unloading Selector scene");

	return true;
}

// Update: draw background
update_status ModuleCharSelectScene::Update()
{
	//INPUTS--------------------------------------------------
	for (int i = 0; i < 69; i++) {
		if (App->input->keyboard[i] == KEY_STATE::KEY_UP) {
			keyup[i] = true;
		}
	}
	//PLAYER1: ---------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		if (iy == 1)
		{
			iy = 0;
		}
	}
	if ((App->input->keyboard[SDL_SCANCODE_A] == 1) && keyup[SDL_SCANCODE_A])
	{
		if (ix <= 3 && keyup[SDL_SCANCODE_A])
		{
			ix--;
			keyup[SDL_SCANCODE_A] = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		if (iy == 0)
		{
			iy = 1;
		}
	}
	if ((App->input->keyboard[SDL_SCANCODE_D] == 1) && keyup[SDL_SCANCODE_D])
	{
		if (ix >= 0 && keyup[SDL_SCANCODE_D])
		{
			ix++;
			keyup[SDL_SCANCODE_D] = false;
		}
	}
	if (ix > 3)
	{
		ix = 3;
	}
	if (ix < 0)
	{
		ix = 0;
	}
	//PLAYER2: ---------------------------------------


	//PORTRAITS: -----------------------------------------

	// Draw everything --------------------------------------
	App->render->DrawQuad({ 0, 0, 650, 500 }, 0, 0, 255, 255, false);
	App->render->Blit(graphics, 96, 154, &Charactersbox, 1.0f, false, false);
	App->render->Blit(graphics, 98, 156, &CharactersR[0], 1.0f, false, false);
	App->render->Blit(graphics, 126, 156, &CharactersR[1], 1.0f, false, false);
	App->render->Blit(graphics, 154, 156, &CharactersR[2], 1.0f, false, false);
	App->render->Blit(graphics, 182, 156, &CharactersR[3], 1.0f, false, false);
	App->render->Blit(graphics, 98, 183, &CharactersR[4], 1.0f, false, false);
	App->render->Blit(graphics, 126, 183, &CharactersR[5], 1.0f, false, false);
	App->render->Blit(graphics, 154, 183, &CharactersR[6], 1.0f, false, false);
	App->render->Blit(graphics, 182, 183, &CharactersR[7], 1.0f, false, false);
	App->render->Blit(graphics, P1posX[ix], P1posY[iy], &P1Selector, 1.0f, false, false);


	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack((Module*)App->scene_characterselect, (Module*)App->scene_karuta, 2.0f);
	}
	//--------------------------------------------------------
	return UPDATE_CONTINUE;
}