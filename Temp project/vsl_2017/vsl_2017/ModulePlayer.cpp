#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
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

	jump.PushBack({ 0,  456, 60, 130 }, 0, -20);
	jump.PushBack({ 60, 456, 66, 130 }, 0, -20);
	jump.PushBack({ 126, 456, 62, 130 }, 0, -20);
	jump.PushBack({ 188, 456, 57 , 130 }, 0, -20);
	jump.PushBack({ 245, 456, 53, 130 }, 0, -20);
	jump.PushBack({ 0, 456, 56, 130 }, 0, -20);
	jump.PushBack({ 299, 456, 56, 130 }, 0, -20);
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

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryo.png");
	playerCollider = App->collision->AddCollider({ position.x, position.y, 57, 108 }, COLLIDER_PLAYER1, this);

	
	

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (this->position.x >= App->player2->position.x) flip = true;
	if (this->position.x <= App->player2->position.x) flip = false;
	if (flip) flip_sign = -1;
	if (!flip) flip_sign = 1;
	
	playerCollider->SetPos(position.x, position.y);
	playerCollider->rect.h = 108;

	if (jumping == JUMP_NOT) {
		speed.x = 0.0f;
	//	speed.y = 0.0f;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP) { 
		keyup = true; 
	}

	if (current_animation->Finished() || current_animation->lock == false)
	{
		if (current_animation->Finished()) {
			current_animation->Reset();
			if (melee != nullptr) {
				melee->to_delete = true;
			}
		}
		bool leaveif = false;

		current_animation = &idle;
		
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
			speed.x = 2.0f;
		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
			speed.x = -2.0f;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &crouchidle;
			playerCollider->rect.h = 50;
			playerCollider->SetPos(position.x, position.y + 68);
		}


		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &forward;
			speed.x = 2.0f;
			if (keyup) { 
				StoreInput(SDL_SCANCODE_D);
				App->audio->PlayChunk(App->audio->koukenFx);
				keyup = false; }
		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &forward;
			speed.x = -1.5f;
		}


		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
		}

		if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN) {
			current_animation = &punch;
			melee = App->collision->AddCollider({ position.x + 50, position.y + 15, 40, 20 }, COLLIDER_PLAYER1_ATTACK, this);
			leaveif = true;
		}

		if ((App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN) && !leaveif)
		{
			current_animation = &kick;
			melee = App->collision->AddCollider({ position.x + 50, position.y, 60, 40 }, COLLIDER_PLAYER1_ATTACK, this);
			/*keyup = false;*/
		}
		//if ((App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_UP))
		//{
		//	keyup = true;
		//}


		if (App->input->keyboard[SDL_SCANCODE_F] == KEY_STATE::KEY_DOWN && !leaveif) {
			current_animation = &koukenR;
			App->particles->AddParticle(App->particles->kouken, position.x, position.y, COLLIDER_PLAYER1_ATTACK);
			App->audio->PlayChunk(App->audio->koukenFx);
		}
	}

	if (jumping != JUMP_NOT)
	{
		speed.y = (-1)*(10 + -0.5 * clock_parabolla);
		clock_parabolla++;

		if (jumping == JUMP_DOWN)
		{
			//speed.y = 3;

			if (position.y >= 112) {
				jumping = JUMP_NOT;
				position.y = 112;
				speed.y = 0;
				clock_parabolla = 0;
			}
		}
		if (jumping == JUMP_UP)
		{
			//speed.y = -3;

			if (current_animation->current_frame >= 2.5f) {
				jumping = JUMP_DOWN;
			}
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	
	position.x += speed.x;
	position.y += speed.y;
	if (position.x <=  0) {
		position.x = 0;
	}
	if (position.x + playerCollider->rect.w >= 538) {
		position.x = 538 - playerCollider->rect.w;
	}

	App->render->Blit(graphics, position.x + current_animation->GetOffset().x, position.y + current_animation->GetOffset().y, &r, 1.0f, flip);
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* A, Collider* B) {
	if (A->type == COLLIDER_PLAYER1_ATTACK && B->type == COLLIDER_PLAYER2)
	{
		A->to_delete == true;
		App->player2->hp -= 25;
		//App->audio->PlayChunk(App->audio->koukenFx);
	} 
	if (A->type == COLLIDER_PLAYER1 && B->type == COLLIDER_PLAYER2)
	{
		App->player->speed.x = 1.0f;
		App->player2->position.x += speed.x;
	}
}

bool ModulePlayer::TestSpecial(SDL_Scancode A, SDL_Scancode B, SDL_Scancode C, SDL_Scancode D)
{
	int interval = 500;
	for (int i = inputCount; i != inputCount - 1; i++) {
		
		if (i == MAX_INPUTS) i % MAX_INPUTS;
		if (input[i] == A	&& input[i-1] == B && 
			input[i-2] == C && input[i-3] == D) {

				if((timeInput[i] - timeInput[i - 1]) < interval &&
				   (timeInput[i - 1] - timeInput[i - 2]) < interval &&
					(timeInput[i - 2] - timeInput[i - 3]) < interval)
				{
					return true;
				}

		}
	}
	return false;
}


bool ModulePlayer::CleanUp() {

	SDL_DestroyTexture(graphics);

	if (playerCollider != nullptr) playerCollider->to_delete = true;

	return true;

}