#include "ModuleUI.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

ModuleUI::ModuleUI()
{

	lifebar1rect = { 766,1, 127,7 };
	lifebar2rect = { 766,1, 127,7 };
	emptylb = { 765,9, 128,9 };
	currenthp1 = 127;
	currenthp2 = 127;

	staminabar1rect = { 0,233, 128,8 };
	staminabar2rect = { 0,233, 128,8 };
	currentsta1 = 0;
	currentsta2 = 0;
	staminatest = 100;

	for (int i = 0; i < 9; i++)
	{
		characterID[i] = i * 24;
	}
	avatar1rect = {0,characterID[0],24,24};
	avatar2rect = {0,characterID[0],24,24};
}
ModuleUI::~ModuleUI()
{

}
bool ModuleUI::Start()
{
	LOG("Loading UI textures");
	graphics = App->textures->Load("UI_AOF.png");
	startTime = SDL_GetTicks();
	return true;
}
update_status ModuleUI::Update()
{
	//Timer:
	int currenttime = 0;
	currenttime = (SDL_GetTicks() - startTime) / 1000;
	//if (currenttime > 60) currenttime %= 60;

	if (currenttime >= 30)
	{	
		currentTimerposX = 928 - (32 * (currenttime - 30));
		if(currenttime > 60) currentTimerposX = 928 - (32 * (60 - 30)); //si es mayor de 60 se queda en 0.
		timerrect = { currentTimerposX,792,32,24 };
		App->render->Blit(graphics, 136, 8, &timerrect, 1.0f, false, false);
		
		if (currenttime == 60) //Victory in case of time up.
		{
			if (App->player->hp > App->player2->hp)  App->player->p1Won = true;
			if (App->player->hp < App->player2->hp)  App->player2->p2Won = true;
		}
	}
	if (currenttime < 30)
	{
		currentTimerposX = 928 - (32 * currenttime);
		timerrect = { currentTimerposX,816,32,24 };
		App->render->Blit(graphics, 136, 8, &timerrect, 1.0f, false, false);
	}
	if (currenttime > 60) timerrect = { 60,816,32,24 };
	
	//--------------------------------------------------------------------
		//Lifebars:

	App->render->Blit(graphics, 8, 16, &emptylb, 1.0f, false, false);
	App->render->Blit(graphics, 168, 16, &emptylb, 1.0f, false, false);

	if  (currenthp1 > ReglaDe3(App->player->hp, 100, 127))
	{
		currenthp1 -= 1;
		
		lifebar1rect = { 766,1, currenthp1,7 };
	}
	if (currenthp2 > ReglaDe3(App->player2->hp, 100, 127))
	{
		currenthp2 -= 1;

		lifebar2rect = { 766,1, currenthp2,7 };
	}
	App->render->Blit(graphics, 9, 17, &lifebar1rect, 1.0f, false, false);
	App->render->Blit(graphics, 169, 17, &lifebar2rect, 1.0f, false, false);
	//--------------------------------------------------------------------
	//STAMINABARS:
	if (currentsta1 != ReglaDe3(App->player->stamina, 100, 128))
	{
		if (currentsta1 > ReglaDe3(App->player->stamina, 100, 128))
		{
			currentsta1 -= 1;
			staminabar1rect = { 128 - currentsta1 ,ColorSelector(currentsta1), 128,8 };
		}
		if (currentsta1 < ReglaDe3(App->player->stamina, 100, 128))
		{
			currentsta1 += 1;
			staminabar1rect = { 128 - currentsta1 ,ColorSelector(currentsta1), 128,8 };
		}
	}

	if (currentsta2 != ReglaDe3(App->player2->stamina, 100, 128))
	{
		if (currentsta2 > ReglaDe3(App->player2->stamina, 100, 128))
		{
			currentsta2 -= 1;
			staminabar2rect = { 0,ColorSelector(currentsta2), currentsta2,8 };
		}
		if (currentsta2 < ReglaDe3(App->player2->stamina, 100, 128))
		{
			currentsta2 += 1;
			staminabar2rect = { 0,ColorSelector(currentsta2), currentsta2,8 };
		}
	}

	App->render->Blit(graphics, 43, 24, &staminabar1rect, 1.0f, true, false);
	App->render->Blit(graphics, 168, 24, &staminabar2rect, 1.0f, false, false);

	//---------------------------------------------------------------------------
	//Pictures:
	App->render->DrawQuad({ 32, 66, 48, 50 }, 255, 255, 255, 255, false);
	App->render->DrawQuad({ 518, 66, 48, 50 }, 255, 255, 255, 255, false);
	App->render->Blit(graphics, 17, 34, &avatar1rect, 1.0f, false, false);
	App->render->Blit(graphics, 242, 34, &avatar2rect, 1.0f, true, false);
	//-------------------------------------------------------------------------
	//App->render->DrawQuad({ 0, 0, 10, 10 }, 255, 255, 255, 255, false);
	return UPDATE_CONTINUE;
}

int ModuleUI::ReglaDe3(float newhp, float hpbase, float pixels)
{
	float res = (float)(newhp / hpbase) * pixels;
	return (int)res;
}

int ModuleUI::ColorSelector(int currentstamina)
{
	if (currentstamina < 30)
	{
		return 217;
	}

	if (currentstamina >= 30 && currentstamina < 70)
	{
		return 225;
	}

	if (currentstamina >= 70)
	{
		return 233;
	}
}

bool ModuleUI::CleanUp()
{
	SDL_DestroyTexture(graphics);

	return true;
}