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

	if (currenttime >= 30)
	{
		currentTimerposX = 928 - (32 * (currenttime - 30));
		timerrect = { currentTimerposX,792,32,24 };
		App->render->Blit(graphics, 136, 8, &timerrect, 1.0f);
	}
	if (currenttime < 30)
	{
		currentTimerposX = 928 - (32 * currenttime);
		timerrect = { currentTimerposX,816,32,24 };
		App->render->Blit(graphics, 136, 8, &timerrect, 1.0f);
	}
//--------------------------------------------------------------------
	//Lifebars:

		return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	SDL_DestroyTexture(graphics);

	return true;
}