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
#include "ModuleCharSelectScene.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleCharSelectScene::ModuleCharSelectScene()
{
	Charactersbox = { 111, 0, 112, 56 };
	P1Selector = { 130, 65, 28 , 31};
	P2Selector = { 158, 68, 28 , 31};
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
	startTime = SDL_GetTicks();
	graphics = App->textures->Load("RESOURCES/UI_AOF.png");
	graphics2 = App->textures->Load("RESOURCES/UI_AOF2.png");
	printFont = { 0,844, 360 ,12 };
	printFont2 = { 0,861, 360 ,8 };
	font_start = App->fonts->Load("RESOURCES/UI_AOF.png", "abcdefghijklmnñopqrstuvwxyz0123456789.'!+,-$_", printFont, 1);
	font_mini = App->fonts->Load("RESOURCES/UI_AOF.png", "abcdefghijklmnñopqrstuvwxyz0123456789.'!+,-$_", printFont, 1);
	App->audio->PlayMusic("RESOURCES/MUSIC_FXS/MUSIC/CHAMP_SELECT/champ_select_theme.ogg", -1);

	
	return true;
}

// UnLoad assets
bool ModuleCharSelectScene::CleanUp()
{
	App->audio->StopMusic();
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
	if (App->input->keyboard[SDL_SCANCODE_W] == 1 || App->input->JoystickGetPos(App->input->controller[0], UP))
	{
		if (iy == 1)
		{
			iy = 0;
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/CHARACTER_SECTION/champ_select.wav"));
		}
	
		
	}
	if ((App->input->keyboard[SDL_SCANCODE_A] == 1 || App->input->JoystickGetPos(App->input->controller[0], LEFT)) && keyup[SDL_SCANCODE_A])
	{
		if (ix <= 3 && keyup[SDL_SCANCODE_A])
		{
			if (ix != 0)
			{
				App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/CHARACTER_SECTION/champ_select.wav"));
			}
			ix--;
			keyup[SDL_SCANCODE_A] = false;
		}
		
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == 1 || App->input->JoystickGetPos(App->input->controller[0], DOWN))
	{
		if (iy == 0)
		{
			iy = 1;
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/CHARACTER_SECTION/champ_select.wav"));
		}
	}
	if ((App->input->keyboard[SDL_SCANCODE_D] == 1 || App->input->JoystickGetPos(App->input->controller[0], RIGHT)) && keyup[SDL_SCANCODE_D])
	{
		if (ix >= 0 && keyup[SDL_SCANCODE_D])
		{
			if (ix != 3)
			{
				App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/CHARACTER_SECTION/champ_select.wav"));
			}
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
	if (iy == 1)
	{
		PortraitP1 = { 0, (4 + ix) * 128, 128,128 };
		NameP1 = { 128, (4 + ix) * 15, 128, 15 };
	}
	if (iy == 0)
	{
		PortraitP1 = { 0, ix * 128, 128,128 };
		NameP1 = { 128, ix * 15, 128, 15 };
	}

	//..................................................................................
	//PLAYER2: ---------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_I] == 1 || App->input->JoystickGetPos(App->input->controller[1], UP))
	{
		if (jy == 1)
		{
			jy = 0;
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/CHARACTER_SECTION/champ_select.wav"));
		}
	}
	if ((App->input->keyboard[SDL_SCANCODE_J] == 1 || App->input->JoystickGetPos(App->input->controller[1], LEFT)) && keyup[SDL_SCANCODE_J])
	{
		if (jx <= 3 && keyup[SDL_SCANCODE_J])
		{
			if (jx != 0)
			{
				App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/CHARACTER_SECTION/champ_select.wav"));
			}
			jx--;
			keyup[SDL_SCANCODE_J] = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_K] == 1 || App->input->JoystickGetPos(App->input->controller[1], DOWN))
	{
		if (jy == 0)
		{
			jy = 1;
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/CHARACTER_SECTION/champ_select.wav"));
		}
	}
	if ((App->input->keyboard[SDL_SCANCODE_L] == 1 || App->input->JoystickGetPos(App->input->controller[1], RIGHT)) && keyup[SDL_SCANCODE_L])
	{
		if (jx >= 0 && keyup[SDL_SCANCODE_L])
		{			
			if (jx != 3)
			{
				App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/CHARACTER_SECTION/champ_select.wav"));
			}
			jx++;
			keyup[SDL_SCANCODE_L] = false;
		}
		
	}
	if (jx > 3)
	{
		jx = 3;
	}
	if (jx < 0)
	{
		jx = 0;
	}
	if (jy == 1)
	{
		PortraitP2 = { 0, (4 + jx) * 128, 128,128 };
		NameP2 = { 128, (4 + jx) * 15, 128, 15 };
	}
	if (jy == 0)
	{
		PortraitP2 = { 0, jx * 128, 128,128 };
		NameP2 = { 128, jx * 15, 128, 15 };
	}



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
	App->render->Blit(graphics2, 220, 8, &PortraitP2, 1.0f, true, false);
	App->render->Blit(graphics2, 168, 137, &NameP2, 1.0f, false, false);
	App->render->Blit(graphics2, 8, 8, &PortraitP1, 1.0f, false, false);
	App->render->Blit(graphics2, 8, 137, &NameP1, 1.0f, false, false);
	App->render->Blit(graphics, P1posX[ix], P1posY[iy], &P1Selector, 1.0f, false, false);
	App->render->Blit(graphics, P2posX[jx], P2posY[jy], &P2Selector, 1.0f, false, false);
	App->fonts->BlitText(72, 11, font_start, "vs_mode_select_player", printFont);
	App->fonts->BlitText(136, 80, font_mini, "time", printFont2);
	//App->fonts->BlitText(144, 87, font_mini, "10", printFont2);
//TIMER----------------------------------------------------------
	int currenttime = 0;
	currenttime = (SDL_GetTicks() - startTime) / 1000;

	if (currenttime <= 10)
	{
		currentTimerposX = 731 + (8 *currenttime);
	}

	timerR = { 1008,currentTimerposX,16,8 };

	App->render->Blit(graphics, 150, 87, &timerR, 1.0f, false, false);

	if (currenttime >= 10)
	{
		App->fade->FadeToBlack((Module*)App->scene_characterselect, (Module*)App->scene_china, 1.0f);
	}


	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || SDL_GameControllerGetButton(App->input->controller[0], SDL_CONTROLLER_BUTTON_A) || SDL_GameControllerGetButton(App->input->controller[1], SDL_CONTROLLER_BUTTON_A))
	{
		App->fade->FadeToBlack((Module*)App->scene_characterselect, (Module*)App->scene_china, 2.0f);
	}
	//--------------------------------------------------------
	return UPDATE_CONTINUE;
}