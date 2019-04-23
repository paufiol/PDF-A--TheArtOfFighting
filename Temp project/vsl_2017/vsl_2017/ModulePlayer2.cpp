#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	position.x = 200;
	position.y = 112;


	// idle animation (arcade sprite sheet)
	idle.PushBack({ 0, 8, 66, 108 });
	idle.PushBack({ 66, 8, 67 , 108 });
	idle.PushBack({ 133, 8, 69, 108 });
	idle.speed = 0.1f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({ 632, 348, 57, 108 });
	forward.PushBack({ 689, 348, 58, 108 });
	forward.PushBack({ 747, 348, 69, 108 });
	forward.PushBack({ 816, 348, 58, 108 });
	forward.PushBack({ 874, 348, 67, 108 });
	forward.speed = 0.15f;

	jump.PushBack({ 0,  456, 60, 130 });
	jump.PushBack({ 60, 456, 66, 130 });
	jump.PushBack({ 126, 456, 62, 130 });
	jump.PushBack({ 188, 456, 57 , 130 });
	jump.PushBack({ 245, 456, 53, 130 });
	jump.PushBack({ 0, 456, 56, 130 });
	jump.PushBack({ 299, 456, 56, 130 });
	jump.speed = 0.1f;
	jump.lock = true;

	punch.PushBack({ 485, 348,  58, 108 });
	punch.PushBack({ 543, 348,  89, 108 });
	punch.PushBack({ 485, 348,  58, 108 });
	punch.speed = 0.2f;
	punch.lock = true;

	koukenR.PushBack({ 176, 873, 66, 112 });
	koukenR.PushBack({ 242, 873, 88, 112 });
	koukenR.PushBack({ 330, 884, 85, 96 });
	koukenR.PushBack({ 415, 888, 81, 97 });
	koukenR.PushBack({ 496, 877, 102, 108 });
	koukenR.speed = 0.2f;
	koukenR.lock = true;


	//AQUI haced que de patadas

	kick.PushBack({ 669, 235, 60, 109 });
	kick.PushBack({ 729, 235, 61, 113 });
	kick.PushBack({ 790, 235, 103, 113 });
	kick.PushBack({ 729, 235, 61, 113 });
	kick.PushBack({ 669, 235, 60, 109 });
	kick.speed = 0.2f;
	kick.lock = true;

}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryo.png");
	player = App->collision->AddCollider({ position.x, position.y - 108, 57, 108 }, COLLIDER_PLAYER2, this);


	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{


	int speed = 1;
	float speed_y = 2.5f;

	if (current_animation->Finished() || current_animation->lock == false)
	{
		if (current_animation->Finished()) {
			current_animation->Reset();
			if (melee != nullptr) {
				melee->to_delete = true;
			}
		}

		current_animation = &idle;

		if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &forward;
			position.x += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &forward;
			position.x -= speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
		}

		if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN) {
			current_animation = &punch;
			melee = App->collision->AddCollider({ position.x + 50, position.y + 15, 40, 20 }, COLLIDER_PLAYER2_ATTACK, this);
		}

		if ((App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN))
		{
			current_animation = &kick;
			melee = App->collision->AddCollider({ position.x + 50, position.y, 60, 40 }, COLLIDER_PLAYER2_ATTACK, this);
			/*keyup = false;*/
		}
		//if ((App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_UP))
		//{
		//	keyup = true;
		//}


		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN) {
			current_animation = &koukenR;
			App->particles->AddParticle(App->particles->kouken, position.x, position.y, COLLIDER_PLAYER2_ATTACK);
		}
	}


	if (jumping == JUMP_DOWN)
	{
		position.y += (int)speed_y;
		//speed_y -= 0.3f;
		if (position.y >= 112) {
			jumping = JUMP_NOT;
			position.y = 112;
			//speed = 1.5f;
		}
	}
	if (jumping == JUMP_UP)
	{
		position.y -= (int)speed_y;
		//speed_y += 0.3f;
		if (current_animation->current_frame >= 2.5f) {
			jumping = JUMP_DOWN;
		}
	}


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	player->SetPos(position.x, position.y);

	App->render->Blit(graphics, position.x, position.y, &r, 1.0f, flip);

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* A, Collider* B) {
	if (A->type == COLLIDER_PLAYER2_ATTACK && B->type == COLLIDER_PLAYER1) 
	{
		A->to_delete == true;
	} //Player 2 hits player 1
	
}

bool ModulePlayer2::CleanUp() {

	SDL_DestroyTexture(graphics);

	if (player != nullptr) player->to_delete = true;

	return true;

}