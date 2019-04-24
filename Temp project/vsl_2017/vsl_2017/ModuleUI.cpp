#include "ModuleUI.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL.h"

ModuleUI::ModuleUI()
{
	
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
	if (currenttime > 60) currenttime %= 60;

	if (currenttime >= 30)
	{
		currentTimerposX = 928 - (32 * (currenttime - 30));
		timerrect = { currentTimerposX,792,32,24 };
		App->render->Blit(graphics, 136, 8, &timerrect, 1.0f, false, false);
	}
	if (currenttime < 30)
	{
		currentTimerposX = 928 - (32 * currenttime);
		timerrect = { currentTimerposX,816,32,24 };
		App->render->Blit(graphics, 136, 8, &timerrect, 1.0f, false, false);
	}
	
//--------------------------------------------------------------------
	//Lifebars:
	lifebar1rect = {765,0, 128,8 };
	App->render->Blit(graphics, 8, 16, &lifebar1rect, 1.0f, false, false);

	lifebar2rect = { 765,0, 128,8 };
	App->render->Blit(graphics, 168, 16, &lifebar2rect, 1.0f, false, false);

	//App->render->DrawQuad({ 0, 0, 10, 10 }, 255, 255, 255, 255, false);
		return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	SDL_DestroyTexture(graphics);

	return true;
}