//#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("RESOURCES/Lee.png");
//<<<<<<< HEAD
	//App->audio->koukenFx = App->audio->LoadChunk("kouken.ogg"); ->DONE
//=======
	//App->audio->koukenFx = App->audio->LoadChunk("kouken.ogg"); 
//>>>>>>> 2433479078b1082cdc5f9a3c0fc665b00183240a

	//kouken.anim.PushBack({ 632, 348, 57, 108 });
		//Sprites super ataque
		//kouken.anim.PushBack({ 598, 879, 54, 106 });
		//kouken.anim.PushBack({ 652, 883, 30, 102 });


	kouken.anim.PushBack({ 736, 905, 72, 47 });
	kouken.anim.PushBack({ 682, 913, 54, 39 });
	kouken.anim.PushBack({ 808, 916, 53, 36 });
	kouken.anim.PushBack({ 861, 931, 36, 21 });
	

	kouken.anim.loop = true;
	kouken.anim.speed = 0.1f;
	kouken.speed.x = 5;


	hit.anim.PushBack({ 977,513,14,17 },2,2);
	hit.anim.PushBack({ 916,498,29,36 });
	hit.life = 100;
	hit.anim.speed = 0.3f;
	hit.anim.loop = false;
	
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	//Aqu� habia una variable declarada, mucho cuidado, las variables se inician en Start() o Init()
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if (p->Update() == false)
		{
			if (p->collider != nullptr) {
			p->collider->to_delete = true;
			delete p;
			active[i] = nullptr;
		}
		}
		else if(SDL_GetTicks() >= p->born)
		{
			if (p->collider != nullptr) {
				if (active[i]->collider->type == COLLIDER_PLAYER1_ATTACK) App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), 1.0F, App->player->flip);
				if (active[i]->collider->type == COLLIDER_PLAYER2_ATTACK) App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), 1.0F, App->player2->flip);
			}
			if (p->collider == nullptr) App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()), 1.0F, App->player->flip);

		/*	SDL_Rect prueba = {App->player->position.x,App->player->position.y,300,50 };
			SDL_SetRenderDrawColor(App->render->renderer, 255, 0, 0, 0);
			SDL_RenderDrawRect(App->render->renderer, &prueba);
			SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 0);*/
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here //AQUI SONIDO HADDOKEN
				
				
			}
		}
	}

	return UPDATE_CONTINUE;
}

Particle * ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;

			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider({x, y, p->anim.GetCurrentFrame().w, p->anim.GetCurrentFrame().h }, collider_type, this, 35);
			active[i] = p;
			return active[i];
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{

		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			c1->to_delete = true;
			App->player->OnCollision(c1, c2);  
			App->player2->OnCollision(c1, c2); 
			delete active[i];
			active[i] = nullptr;

			break;
		}
	}
}
// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	
	//Our version---------
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;

	}
	else
		if(anim.Finished() && anim.loop == false)
			ret = false;

	if (collider != nullptr) {
		if (App->player->flip) {
			collider->SetPos(position.x - collider->rect.w / 10, position.y - collider->rect.h / 2);
		}
		else {
			collider->SetPos(position.x - collider->rect.w / 10 + 4, position.y - collider->rect.h / 2);
		}
	}

	if (collider != nullptr) {
		if ((collider->type == COLLIDER_PLAYER1_ATTACK && App->player->flip) || (collider->type == COLLIDER_PLAYER2_ATTACK && App->player2->flip)) position.x -= speed.x;
		else position.x += speed.x;
		position.y += speed.y;


		/*collider->rect.x = position.x;
		collider->rect.y = position.y;*/
	}
	

	//Other version-------
	/*bool ret = true;

	if (life > 0)
	{
		int ticks = SDL_GetTicks();
		int num = ticks - born;
		if (num > life) {
			ret = false;
		}
	}
	else
		if (anim.Finished()) {
			ret = false;
		}
	if (SDL_GetTicks() >= born)
	{

		if (App->player->flip)
		{
			position.x += speed.x;
			position.y += speed.y;
		}
		else
		{
			position.x -= speed.x;
			position.y -= speed.y;
		}

		if (collider != nullptr) {
			if (App->player->flip) {
				collider->SetPos(position.x - collider->rect.w / 10, position.y - collider->rect.h / 2);
			}
			else {
				collider->SetPos(position.x - collider->rect.w / 10 + 4, position.y - collider->rect.h / 2);
			}
		}
	}*/
	return ret;
}