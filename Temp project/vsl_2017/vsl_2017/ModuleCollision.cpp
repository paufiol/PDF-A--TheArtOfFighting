#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER1_ATTACK] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER2_ATTACK] = true;
	matrix[COLLIDER_WALL][COLLIDER_SPECIAL_ATTACK1] = true;
	matrix[COLLIDER_WALL][COLLIDER_SPECIAL_ATTACK2] = true;

	matrix[COLLIDER_PLAYER1][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER1] = false;
	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER1_ATTACK] = false;
	matrix[COLLIDER_PLAYER1][COLLIDER_PLAYER2_ATTACK] = true;
	matrix[COLLIDER_PLAYER1][COLLIDER_SPECIAL_ATTACK1] = false;
	matrix[COLLIDER_PLAYER1][COLLIDER_SPECIAL_ATTACK2] = true;

	matrix[COLLIDER_PLAYER2][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER1_ATTACK] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_PLAYER2_ATTACK] = false;
	matrix[COLLIDER_PLAYER2][COLLIDER_SPECIAL_ATTACK1] = true;
	matrix[COLLIDER_PLAYER2][COLLIDER_SPECIAL_ATTACK2] = false;

	matrix[COLLIDER_PLAYER1_ATTACK][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER1_ATTACK][COLLIDER_PLAYER1] = false;
	matrix[COLLIDER_PLAYER1_ATTACK][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_PLAYER1_ATTACK][COLLIDER_PLAYER1_ATTACK] = false;
	matrix[COLLIDER_PLAYER1_ATTACK][COLLIDER_PLAYER2_ATTACK] = false;
	matrix[COLLIDER_PLAYER1_ATTACK][COLLIDER_SPECIAL_ATTACK1] = false;
	matrix[COLLIDER_PLAYER1_ATTACK][COLLIDER_SPECIAL_ATTACK2] = false;

	matrix[COLLIDER_PLAYER2_ATTACK][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER2_ATTACK][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_PLAYER2_ATTACK][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_PLAYER2_ATTACK][COLLIDER_PLAYER1_ATTACK] = false;
	matrix[COLLIDER_PLAYER2_ATTACK][COLLIDER_PLAYER2_ATTACK] = false;
	matrix[COLLIDER_PLAYER2_ATTACK][COLLIDER_SPECIAL_ATTACK1] = false;
	matrix[COLLIDER_PLAYER2_ATTACK][COLLIDER_SPECIAL_ATTACK2] = false;

	matrix[COLLIDER_SPECIAL_ATTACK1][COLLIDER_WALL] = true;
	matrix[COLLIDER_SPECIAL_ATTACK1][COLLIDER_PLAYER1] = false;
	matrix[COLLIDER_SPECIAL_ATTACK1][COLLIDER_PLAYER2] = true;
	matrix[COLLIDER_SPECIAL_ATTACK1][COLLIDER_PLAYER1_ATTACK] = false;
	matrix[COLLIDER_SPECIAL_ATTACK1][COLLIDER_PLAYER2_ATTACK] = false;
	matrix[COLLIDER_SPECIAL_ATTACK1][COLLIDER_SPECIAL_ATTACK1] = false;
	matrix[COLLIDER_SPECIAL_ATTACK1][COLLIDER_SPECIAL_ATTACK2] = false;

	matrix[COLLIDER_SPECIAL_ATTACK2][COLLIDER_WALL] = true;
	matrix[COLLIDER_SPECIAL_ATTACK2][COLLIDER_PLAYER1] = true;
	matrix[COLLIDER_SPECIAL_ATTACK2][COLLIDER_PLAYER2] = false;
	matrix[COLLIDER_SPECIAL_ATTACK2][COLLIDER_PLAYER1_ATTACK] = false;
	matrix[COLLIDER_SPECIAL_ATTACK2][COLLIDER_PLAYER2_ATTACK] = false;
	matrix[COLLIDER_SPECIAL_ATTACK2][COLLIDER_SPECIAL_ATTACK1] = false;
	matrix[COLLIDER_SPECIAL_ATTACK2][COLLIDER_SPECIAL_ATTACK2] = false;

}

bool ModuleCollision::Start() {
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if(c1->CheckCollision(c2->rect) == true)
			{
				if(matrix[c1->type][c2->type] && c1->callback) 
					c1->callback->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->callback) 
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN && App->player->keyup[SDL_SCANCODE_F1]) {
		debug = !debug;
		if (App->player->keyup[SDL_SCANCODE_F1])
		{
			App->player->keyup[SDL_SCANCODE_F1] = false;
		};
	}


	if(debug == false)
		return;

	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
			case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 128, 0, 128, alpha);
			case COLLIDER_SPECIAL_ATTACK1: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case COLLIDER_SPECIAL_ATTACK2: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
			case COLLIDER_PLAYER1: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
			case COLLIDER_PLAYER2: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			case COLLIDER_PLAYER1_ATTACK: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
			case COLLIDER_PLAYER2_ATTACK: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback, int damage)
{
	Collider* ret = nullptr;
	
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}
	ret->damage = damage;
	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{

	return ((r.x + r.w > rect.x) && (r.x < rect.x + rect.w) &&
		(r.y + r.h > rect.y) && (r.y < rect.y + rect.h));

}