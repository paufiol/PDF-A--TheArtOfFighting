#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleSlowdown.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

ModuleSlowdown::ModuleSlowdown()
{
}

ModuleSlowdown::~ModuleSlowdown()
{}

// Load assets
bool ModuleSlowdown::Start()
{
	finished = false;
	return true;
}

// Update: draw background
update_status ModuleSlowdown::PostUpdate()
{
	if (slowing_down)
	{
		UpdateSlowdown();
	}

	return UPDATE_CONTINUE;
}
void ModuleSlowdown::StartSlowdown(int duration, int magnitude)
{
	slowdown_duration = duration;
	slowdown_magnitude = magnitude;
	if (!slowing_down) { slowing_down = true; }
}

void ModuleSlowdown::UpdateSlowdown()
{
	if (slowdown_timer <= slowdown_duration) {
		SDL_Delay(slowdown_magnitude);
	}
	else {
		slowing_down = false;
		slowdown_timer = 0;
		finished = true;
	}
	slowdown_timer++;
}
