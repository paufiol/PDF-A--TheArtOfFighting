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
	forward.PushBack({ 691, 348, 56, 109 });
	forward.PushBack({ 749, 350, 65, 107 },-10,0);
	forward.PushBack({ 818, 348, 58, 109 });
	forward.PushBack({ 876, 350, 65, 107 },-9,0);
	/*forward.PushBack({ 874, 348, 67, 108 });*/
	forward.speed = 0.1f;
	

	back.PushBack({ 577, 479, 57, 109},-5,0);
	back.PushBack({ 638, 477, 52, 111});
	back.PushBack({ 692, 479, 57, 109},-5,0);
	back.PushBack({ 638, 477, 52, 111 });
	back.PushBack({ 577, 479, 57, 109 },-5,0);
	back.speed = 0.1f;

	

	doubleback.PushBack({275, 595, 59, 107});
	doubleback.PushBack({334, 596, 89, 106},-80, -10);
	doubleback.PushBack({ 334, 596, 89, 106 }, 0, 0);
	doubleback.PushBack({423, 596, 73, 106}, -80, 10);
	doubleback.speed = 0.2f;
	doubleback.lock = true;


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
	punch.speed = 0.03f;
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

	crouchidle.PushBack({ 576, 42, 67, 75 }, 0, 34);
	crouchidle.speed = 0.1f;

	crouchpunch.PushBack({ 414, 42, 53, 76}, 0, 34);
	crouchpunch.PushBack({ 469, 41, 106, 77 },-15,34);
	crouchpunch.speed = 0.15f;
	crouchpunch.lock = true;

	crouchkick.PushBack({ 866, 169, 55, 66 }, 0, 40);
	crouchkick.PushBack({ 0, 280, 127, 68 }, -15, 40);
	crouchkick.speed = 0.125f;
	crouchkick.lock = true;

	damaged.PushBack({ 866, 754, 59, 99 });
	damaged.PushBack({ 925, 754, 59, 63 });
	damaged.PushBack({ 866, 754, 59, 99 });
	damaged.speed = 0.1f;
	damaged.lock = true;


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
	if (flip) playerCollider->SetPos(position.x + (current_animation->GetCurrentFrame().w) - playerCollider->rect.w, position.y);

	playerCollider->rect.h = 108;
	if (block != nullptr) 
	{ 
		if(!flip)	block->SetPos(position.x + 55, position.y + 5); 
		if(flip)	block->SetPos(position.x - 15, position.y + 5);
	}

	if (current_animation == &crouchidle || current_animation == &crouchpunch || current_animation == &crouchkick)
	{
		playerCollider->SetPos(position.x, position.y + 33);
		playerCollider->rect.h = 75;
	}


	if (jumping == JUMP_NOT) {
		speed.x = 0.0f;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_UP) { 
		//keyup[SDL_SCANCODE_D] = true;
		if (block != nullptr && flip) block->to_delete = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) {
		//keyup[SDL_SCANCODE_A] = true;
		if (block != nullptr && !flip) block->to_delete = true;
	}


	for (int i = 0; i < 69; i++) {
		if (App->input->keyboard[i] == KEY_STATE::KEY_UP) {
			keyup[i] = true;
		}
	}

	if (current_animation->Finished() || current_animation->lock == false)
	{
		if (current_animation->Finished()) {
			current_animation->Reset();
			if (melee != nullptr) melee->to_delete = true;
			
		}
		bool leaveif = false;

		current_animation = &idle;
		
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
			speed.x = 4.5f;
		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
			speed.x = -4.5f;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &crouchidle;
			playerCollider->rect.h = 75;
			
			if (keyup[SDL_SCANCODE_S]) {
				StoreInput(SDL_SCANCODE_S);
				keyup[SDL_SCANCODE_S] = false;
			}
		}

		if (!keyup[SDL_SCANCODE_S] && (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN)
			&& keyup[SDL_SCANCODE_Q] && !leaveif)
		{
			current_animation = &crouchpunch;
			melee = App->collision->AddCollider({ position.x + 50, position.y + 40, 63, 20 }, COLLIDER_PLAYER1_ATTACK, this);
			leaveif = true;

			if (keyup[SDL_SCANCODE_Q]) {
				StoreInput(SDL_SCANCODE_Q);
				keyup[SDL_SCANCODE_Q] = false;
			}
		}

		if (!keyup[SDL_SCANCODE_S] && (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
			&& keyup[SDL_SCANCODE_E] && !leaveif)
		{
			current_animation = &crouchkick;
			melee = App->collision->AddCollider({ position.x + 50, position.y + 60, 70, 20 }, COLLIDER_PLAYER1_ATTACK, this);
			leaveif = true;

			if (keyup[SDL_SCANCODE_E]) {
				StoreInput(SDL_SCANCODE_E);
				keyup[SDL_SCANCODE_E] = false;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
		{
			if(!flip) current_animation = &forward;
			if (flip) current_animation = &back;
			speed.x = 2.5f;
			playerCollider->rect.h = 108;
			if (keyup[SDL_SCANCODE_D]) {
				StoreInput(SDL_SCANCODE_D);
				if (flip) { block = App->collision->AddCollider({ position.x - 15, position.y + 5, 15, 35 }, COLLIDER_WALL, this); }
				keyup[SDL_SCANCODE_D] = false; 
			}
		}
		//cambiar//
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN)
		{
			if(!flip) current_animation = &back;
			if(flip) current_animation = &forward;
			speed.x = -1.5f;
			playerCollider->rect.h = 108;
			if (keyup[SDL_SCANCODE_A]) {
				StoreInput(SDL_SCANCODE_A);
				if (!flip) { block = App->collision->AddCollider({ position.x + 55, position.y + 5, 10, 30 }, COLLIDER_WALL, this); }
				keyup[SDL_SCANCODE_A] = false;
			}
		}

		/*if (App->input->keyboard[SDL_SCANCODE_A] && App->input->keyboard[SDL_SCANCODE_A])
		{
			current_animation = &doubleback;
			speed.x = -1.5f;
			playerCollider->rect.h = 108;
			if (keyup[SDL_SCANCODE_A]) {
				StoreInput(SDL_SCANCODE_A);
				if (!flip) { block = App->collision->AddCollider({ position.x + 50, position.y + 5, 10, 30 }, COLLIDER_WALL, this); }
				keyup[SDL_SCANCODE_A] = false;
			}
		}*/

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
		}

		if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN && !leaveif && keyup[SDL_SCANCODE_Q]) {
			current_animation = &punch;
			
			if(!flip) melee = App->collision->AddCollider({ position.x + 50, position.y + 15, 40, 20 }, COLLIDER_PLAYER1_ATTACK, this, 10);
			if(flip)  melee = App->collision->AddCollider({ position.x - 15, position.y + 15, 40, 20 }, COLLIDER_PLAYER1_ATTACK, this, 10);
			
			leaveif = true;
			if (keyup[SDL_SCANCODE_Q]) {
				StoreInput(SDL_SCANCODE_Q);
				keyup[SDL_SCANCODE_Q] = false;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN && !leaveif && keyup[SDL_SCANCODE_E])
		{
			current_animation = &kick;
			melee = App->collision->AddCollider({ position.x + 50, position.y, 60, 40 }, COLLIDER_PLAYER1_ATTACK, this, 20);
			if (keyup[SDL_SCANCODE_E]) {
				StoreInput(SDL_SCANCODE_E);
				keyup[SDL_SCANCODE_E] = false;
			}
		}

		if ((TestSpecial(SDL_SCANCODE_E, SDL_SCANCODE_Q, SDL_SCANCODE_D, SDL_SCANCODE_S) || App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN)&& !leaveif) {
			current_animation = &koukenR;
			App->particles->AddParticle(App->particles->kouken, position.x, position.y, COLLIDER_PLAYER1_ATTACK);
			App->audio->PlayChunk(App->audio->koukenFx);
		}

		
	}
	
	if (hp <= 0)
	{
		hp = 0;
		App->player2->p2Won = true;
		//current_animation = &death;
		playerCollider->to_delete = true;
	}


//Debug functionality-----------------------------------------

	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN && keyup[SDL_SCANCODE_F2])
	{
		p1Won = !p1Won;
		if (keyup[SDL_SCANCODE_F2])
		{
			keyup[SDL_SCANCODE_F2] = false;
		}
	}
	

//Jumping movement--------------------------------------------
	if (jumping != JUMP_NOT)
	{
		speed.y = (-1)*(12 + -0.5 * clock_parabolla);
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

	
	
	//Keep character within limits-----------------------------
	position.x += speed.x;
	position.y += speed.y;
	if (position.x <=  0) {
		position.x = 0;
	}
	if (position.x + playerCollider->rect.w >= 538) {
		position.x = 538 - playerCollider->rect.w;
	}
	if (position.x <= (App->player->position.x + (App->player2->playerCollider->rect.w / 2) + App->player2->position.x + (App->player->playerCollider->rect.w / 2)) / 2 - SCREEN_WIDTH / 2) {
		position.x = (App->player->position.x + (App->player2->playerCollider->rect.w / 2) + App->player2->position.x + (App->player->playerCollider->rect.w / 2)) / 2 - SCREEN_WIDTH / 2; }
	if (position.x + playerCollider->rect.w >= (App->player->position.x + (App->player2->playerCollider->rect.w / 2) + App->player2->position.x + (App->player->playerCollider->rect.w / 2)) / 2 + SCREEN_WIDTH / 2) {
		position.x = (App->player->position.x + (App->player2->playerCollider->rect.w / 2) + App->player2->position.x + (App->player->playerCollider->rect.w / 2)) / 2 + SCREEN_WIDTH / 2 - playerCollider->rect.w;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x + current_animation->GetOffset().x, position.y + current_animation->GetOffset().y, &r, 1.0f, flip);
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* A, Collider* B) {
	if (A->type == COLLIDER_PLAYER1_ATTACK && B->type == COLLIDER_PLAYER2)//Player1 lands hit on Player2
	{
		A->to_delete = true;
		
		if (current_animation != &damaged)
		{
			App->player2->hp -= A->damage;
			if(!flip) App->player2->position.x += 15;
			if (flip) App->player2->position.x -= 15;
			App->player2->current_animation = &damaged;
		}
		
	} 
	if (A->type == COLLIDER_PLAYER1 && B->type == COLLIDER_PLAYER2)
	{
		//App->player->speed.x = 1.0f;
		if (jumping == JUMP_DOWN && ((position.x > App->player2->position.x && flip) || (position.x < App->player2->position.x && !flip))) {
			if (flip) position.x += 5;
			if (!flip)position.x -= 5;
		}
		else if ( jumping == JUMP_UP ) ;
		else { 
			if (flip) App->player->position.x = App->player2->position.x + App->player2->playerCollider->rect.w; 
			if (!flip)App->player->position.x = App->player2->position.x - playerCollider->rect.w;
		}
		if(!flip)App->player2->position.x += 1.0f;
		if(flip) App->player2->position.x -= 1.0f;
	}
	if (A->type == COLLIDER_WALL && B->type == COLLIDER_PLAYER2_ATTACK)
	{
		position.x -= 15;
		B->to_delete = true;
	}

}

bool ModulePlayer::TestSpecial(SDL_Scancode A, SDL_Scancode B, SDL_Scancode C, SDL_Scancode D)
{
	int interval = 500;
	int d = inputCount - 1;
	if (inputCount == 0) d = MAX_INPUTS - 1;
	for (int i = inputCount; 1; i++) {
		
		if (i == (MAX_INPUTS)) i = 0;
		int j = i - 1; int k = i - 2; int l = i - 3;
		if (i == 2) { l = MAX_INPUTS - 1; }
		if (i == 1) { l = MAX_INPUTS - 2; k = MAX_INPUTS - 1;}
		if (i == 0) { l = MAX_INPUTS - 3; k = MAX_INPUTS - 2; j = MAX_INPUTS - 1;}
		if (input[i] == A	&& input[j] == B && 
			input[k] == C	&& input[l] == D) {

			if((timeInput[i] - timeInput[j]) < interval &&
			   (timeInput[j] - timeInput[k]) < interval &&
			   (timeInput[k] - timeInput[l]) < interval){				
					
					for (int p = 0; p < MAX_INPUTS; p++) {
						input[p] = 0;
						timeInput[p] = 0;
					}
					inputCount = 0;
					return true;

			}
		}
		if (i == d) break;
	}

	return false;
}


bool ModulePlayer::CleanUp() {

	SDL_DestroyTexture(graphics);

	if (playerCollider != nullptr) playerCollider->to_delete = true;

	return true;

}