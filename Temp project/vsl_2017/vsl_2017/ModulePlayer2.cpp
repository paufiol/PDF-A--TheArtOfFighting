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
	forward.PushBack({ 691, 348, 56, 109 });
	forward.PushBack({ 749, 350, 65, 107 }, 10, 0);
	forward.PushBack({ 818, 348, 58, 109 });
	forward.PushBack({ 876, 350, 65, 107 }, 9, 0);
	/*forward.PushBack({ 874, 348, 67, 108 });*/
	forward.speed = 0.1f;

	back.PushBack({ 577, 479, 57, 109 }, 5, 0);
	back.PushBack({ 638, 477, 52, 111 });
	back.PushBack({ 692, 479, 57, 109 }, 5, 0);
	back.PushBack({ 638, 477, 52, 111 });
	back.PushBack({ 577, 479, 57, 109 }, 5, 0);
	back.speed = 0.1f;

	flipback.PushBack({ 577, 479, 57, 109 }, 5, 0);
	flipback.PushBack({ 638, 477, 52, 111 });
	flipback.PushBack({ 692, 479, 57, 109 }, 5, 0);
	flipback.PushBack({ 638, 477, 52, 111 });
	flipback.PushBack({ 577, 479, 57, 109 }, 5, 0);
	flipback.speed = 0.1f;

	doubleback.PushBack({ 275, 595, 59, 107 });
	doubleback.PushBack({ 334, 596, 89, 106 }, -80, -10);
	doubleback.PushBack({ 334, 596, 89, 106 }, 0, 0);
	doubleback.PushBack({ 423, 596, 73, 106 }, -80, 10);
	doubleback.speed = 0.1f;
	doubleback.lock = true;

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
	kick.speed = 0.1f;
	kick.lock = true;

	damaged.PushBack({ 866, 754, 59, 99 });
	damaged.PushBack({ 925, 754, 59, 63 });
	damaged.PushBack({ 866, 754, 59, 99 });
	damaged.speed = 0.1f;
	damaged.lock = true;

	crouchidle.PushBack({ 576, 42, 67, 75 }, 0, 34);
	crouchidle.speed = 0.1f;

	crouchpunch.PushBack({ 414, 42, 53, 76 }, 0, 34);
	crouchpunch.PushBack({ 469, 41, 106, 77 }, -15, 34);
	crouchpunch.speed = 0.15f;
	crouchpunch.lock = true;

	crouchkick.PushBack({ 866, 169, 55, 66 }, 0, 40);
	crouchkick.PushBack({ 0, 280, 127, 68 }, -15, 40);
	crouchkick.speed = 0.125f;
	crouchkick.lock = true;

	damaged.PushBack({ 0,135,66,107 });
	damaged.PushBack({ 66,134,708,108 });
	damaged.PushBack({ 144,135,66,107 });
	damaged.speed = 0.1f;
	damaged.lock = true;

	victory.PushBack({ 0, 256, 53, 116 });
	victory.PushBack({ 65, 266, 69, 106 });
	victory.speed = 0.1f;
	victory.lock = true;

	defeat.PushBack({ 0, 0, 66, 115 });
	defeat.PushBack({ 66, 0, 73, 115 });
	defeat.PushBack({ 144, 8, 64, 107 });
	defeat.PushBack({ 208, 29, 62, 86 });
	defeat.PushBack({ 270, 53, 58, 62 });
	defeat.lock = true;
	defeat.speed = 0.1f;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryo.png");
	playerCollider = App->collision->AddCollider({ position.x, position.y, 57, 108 }, COLLIDER_PLAYER2, this);


	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{


	int speed = 2;
	float speed_y = 6.5f;

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
			current_animation = &back;
			position.x += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &forward;
			position.x -= speed;
			
		}

		if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &crouchidle;
			playerCollider->rect.h = 75;
			
		}
		

		if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
		}

		if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN) {
			current_animation = &punch;
			melee = App->collision->AddCollider({ position.x - 30, position.y + 15, 40, 20 }, COLLIDER_PLAYER2_ATTACK, this);
			App->audio->PlayChunk(App->audio->LoadChunk("MUSIC_FXS/FXS/RYO/FIGHT/Punch_Attack.wav"));
			App->audio->PlayChunk(App->audio->LoadChunk("MUSIC_FXS/FXS/RYO/RYO_VOICE_FXS/Ryo_Punch.wav"));
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

	playerCollider->SetPos(position.x, position.y);
	/*
	if (current_animation == &victory || current_animation == &defeat || current_animation == &damaged) {
		App->render->Blit(graphics2, position.x + current_animation->GetOffset().x, position.y + current_animation->GetOffset().y, &r, 1.0f, flip);
	}*/
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

	if (playerCollider != nullptr) playerCollider->to_delete = true;

	return true;

}