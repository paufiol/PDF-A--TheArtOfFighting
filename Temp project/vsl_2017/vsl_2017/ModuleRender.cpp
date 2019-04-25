#include "Globals.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"

ModuleRender::ModuleRender() : Module()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{
	int speed = 3;

	/* if(App->input->keyboard[SDL_SCANCODE_UP] == 1)
		camera.y += speed; */

	/* if(App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
		camera.y -= speed; */
	
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1) {
		
			camera.x += speed;
		
	}

	if (App->input->keyboard[SDL_SCANCODE_B] == 1) {
		
			camera.x += 0;
		
	}
	
	if (App->player->IsEnabled() && App->player2->IsEnabled()) {
		//camera.x = App->player->position.x + ((App->player2->position.x + (App->player2->playerCollider->rect.w / 2)) + (App->player->position.x + (App->player->playerCollider->rect.w/2)))/2 - SCREEN_WIDTH / 2;
		
		if (!App->player->p1Won)
		{
			camera.x = -(App->player->position.x + (App->player2->playerCollider->rect.w / 2) + App->player2->position.x + (App->player->playerCollider->rect.w / 2)) + SCREEN_WIDTH;
		}
		else if (App->player->p1Won)
		{
			camera.x = -(App->player->position.x - (App->player->playerCollider->rect.w / 2) - SCREEN_WIDTH);
		}
	}
	if (camera.x > 0) camera.x = 0;
	if ((camera.x) < -595 + SCREEN_WIDTH/2) camera.x = -595 + SCREEN_WIDTH / 2;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, bool flip, bool use_camera)
{
	bool ret = true;
	SDL_Rect rect;
	if (use_camera)
	{
		rect.x = (int)(camera.x ) + x * SCREEN_SIZE;
		rect.y = (int)(camera.y ) + y * SCREEN_SIZE;
		//rect.x = x * SCREEN_SIZE;
		//rect.y = y * SCREEN_SIZE;
	}
	else
	{
		rect.x = x * SCREEN_SIZE;
		rect.y = y * SCREEN_SIZE;
	}

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;
	
	
	if (flip) {
		rect.x -= (section->w - 57);
		
		if (SDL_RenderCopyEx(renderer, texture, section, &rect, NULL, NULL, SDL_FLIP_HORIZONTAL) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
	else {
		if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
	return ret;
}

//DEBUG TOOL
bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}


	
	return ret;
}

