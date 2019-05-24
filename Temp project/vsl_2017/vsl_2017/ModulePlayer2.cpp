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
#include "ModuleUI.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	position.x = 300;
	position.y = 112;


	// idle animation (arcade sprite sheet)
	/*idle.PushBack({ 0, 8, 66, 108 });
	idle.PushBack({ 66, 8, 67 , 108 });
	idle.PushBack({ 133, 8, 69, 108 });
	if (!flip) idle.speed = 0.05f;
	if (flip) idle.speed = 0.1f;*/

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	//forward.PushBack({ 691, 348, 56, 109 });
	//forward.PushBack({ 749, 350, 65, 107 }, -10, 0);
	//forward.PushBack({ 818, 348, 58, 109 });
	//forward.PushBack({ 876, 350, 65, 107 }, -9, 0);
	///*forward.PushBack({ 874, 348, 67, 108 });*/
	//if (!flip) forward.speed = 0.05f;
	//if (flip) forward.speed = 0.1f;

	flipforward.PushBack({ 691, 348, 56, 109 }, 0, 0);
	flipforward.PushBack({ 749, 350, 65, 107 }, 10, 0);
	flipforward.PushBack({ 818, 348, 58, 109 }, 0, 0);
	flipforward.PushBack({ 876, 350, 65, 107 }, 9, 0);
	/*forward.PushBack({ 874, 348, 67, 108 });*/
	if (!flip) flipforward.speed = 0.05f;
	if (flip) flipforward.speed = 0.1f;


	/*back.PushBack({ 577, 479, 57, 109 }, -5, 0);
	back.PushBack({ 638, 477, 52, 111 });
	back.PushBack({ 692, 479, 57, 109 }, -5, 0);
	back.PushBack({ 638, 477, 52, 111 });
	back.PushBack({ 577, 479, 57, 109 }, -5, 0);
	if (!flip) back.speed = 0.05f;
	if (flip) back.speed = 0.1f;*/

	flipback.PushBack({ 577, 479, 57, 109 }, 5, 0);
	flipback.PushBack({ 638, 477, 52, 111 });
	flipback.PushBack({ 692, 479, 57, 109 }, 5, 0);
	flipback.PushBack({ 638, 477, 52, 111 });
	flipback.PushBack({ 577, 479, 57, 109 }, 5, 0);
	if (!flip) flipback.speed = 0.05f;
	if (flip) back.speed = 0.1f;

	doubleback.PushBack({ 275, 595, 59, 107 });
	doubleback.PushBack({ 334, 596, 89, 106 }, -80, -10);
	doubleback.PushBack({ 334, 596, 89, 106 }, 0, 0);
	doubleback.PushBack({ 423, 596, 73, 106 }, -80, 10);
	if (flip) doubleback.speed = 0.1f;
	if (!flip) doubleback.speed = 0.1f;
	doubleback.lock = true;


	/*jump.PushBack({ 0,  456, 60, 130 }, 0, -20);
	jump.PushBack({ 60, 456, 66, 130 }, 0, -20);
	jump.PushBack({ 126, 456, 62, 130 }, 0, -20);
	jump.PushBack({ 188, 456, 57 , 130 }, 0, -20);
	jump.PushBack({ 245, 495, 54, 91 }, 0, -20);
	jump.PushBack({ 0, 456, 56, 130 }, 0, -20);
	jump.PushBack({ 299, 456, 56, 130 }, 0, -20);
	if (flip) jump.speed = 0.1f;
	if (!flip) jump.speed = 0.1f;
	jump.lock = true;*/

	//punch.PushBack({ 485, 348,  58, 108 });
	//punch.PushBack({ 543, 348,  89, 108 });
	///*punch.PushBack({ 485, 348,  58, 108 });*/
	//if (flip) punch.speed = 0.2f;
	//if (!flip) punch.speed = 0.2f;
	//punch.lock = true;


	koukenR.PushBack({ 176, 873, 66, 112 });
	koukenR.PushBack({ 242, 873, 88, 112 });
	koukenR.PushBack({ 330, 884, 85, 96 });
	koukenR.PushBack({ 415, 888, 81, 97 });
	koukenR.PushBack({ 496, 877, 102, 108 });
	if (flip) koukenR.speed = 0.2f;
	if (!flip) koukenR.speed = 0.1f;
	koukenR.lock = true;





	//AQUI haced que de patadas

	kick.PushBack({ 669, 235, 60, 109 });
	kick.PushBack({ 729, 235, 61, 113 });
	kick.PushBack({ 790, 235, 103, 113 });
	kick.PushBack({ 729, 235, 61, 113 });
	/*kick.PushBack({ 669, 235, 60, 109 });*/
	if (flip) kick.speed = 0.2f;
	if (!flip) kick.speed = 0.2f;
	kick.lock = true;

	flipkick.PushBack({ 669, 235, 60, 109 });
	flipkick.PushBack({ 729, 235, 61, 113 });
	flipkick.PushBack({ 790, 235, 103, 113 });
	flipkick.PushBack({ 729, 235, 61, 113 });
	flipkick.PushBack({ 669, 235, 60, 109 });
	if (flip) flipkick.speed = 0.2f;
	if (!flip) flipkick.speed = 0.1f;
	flipkick.lock = true;

	/*crouchidle.PushBack({ 576, 42, 67, 75 }, 0, 34);
	if (flip) crouchidle.speed = 0.1f;
	if (!flip) crouchidle.speed = 0.05f;*/

	crouchpunch.PushBack({ 414, 42, 53, 76 }, 0, 34);
	crouchpunch.PushBack({ 469, 41, 106, 77 }, -15, 34);
	if (flip) crouchpunch.speed = 0.15f;
	if (!flip) crouchpunch.speed = 0.15f;
	crouchpunch.lock = true;

	crouchkick.PushBack({ 866, 169, 55, 66 }, 0, 40);
	crouchkick.PushBack({ 0, 280, 127, 68 }, -15, 40);
	if (flip) crouchkick.speed = 0.125f;
	if (!flip) crouchkick.speed = 0.125f;
	crouchkick.lock = true;

	damaged.PushBack({ 869,751, 66 ,107 });
	damaged.PushBack({ 935,750, 78, 138 });
	damaged.PushBack({ 869, 751, 66, 107 });
	if (flip) damaged.speed = 0.1f;
	if (!flip) damaged.speed = 0.2f;
	damaged.lock = true;

	defeat.PushBack({ 0, 0, 66, 115 });
	defeat.PushBack({ 66, 0, 73, 115 });
	defeat.PushBack({ 144, 8, 64, 107 });
	defeat.PushBack({ 208, 29, 62, 86 });
	defeat.PushBack({ 270, 53, 58, 62 });
	defeat.lock = true;
	defeat.speed = 0.1f;


	//lee

	idle.PushBack({ 0,3,70,101 }, 0, 0);
	idle.PushBack({ 75,5,69,99 }, 0, 2);
	idle.PushBack({ 159,1,70,103 }, 0, -2);

	idle.speed = 0.075f;

	jump.PushBack({ 697,  6, 54, 98 }, 0, -20);
	jump.PushBack({ 759, 49, 78, 53 }, 0, -20);
	jump.PushBack({ 837, 32, 38, 70 }, 0, -20);
	jump.PushBack({ 885, 64, 68, 38 }, 0, -20);
	jump.PushBack({ 958, 34, 39, 69 }, 0, -20);
	jump.PushBack({ 0, 167, 66, 38 }, 0, -20);
	jump.PushBack({ 837, 32, 38, 70 }, 0, -20);
	jump.PushBack({ 885, 64, 68, 38 }, 0, -20);
	jump.PushBack({ 958, 34, 39, 69 }, 0, -20);
	jump.PushBack({ 0, 167, 66, 38 }, 0, -20);
	jump.PushBack({ 837, 32, 38, 70 }, 0, -20);
	jump.PushBack({ 885, 64, 68, 38 }, 0, -20);
	jump.PushBack({ 958, 34, 39, 69 }, 0, -20);
	jump.PushBack({ 0, 167, 66, 38 }, 0, -20);
	jump.PushBack({ 837, 32, 38, 70 }, 0, -20);
	jump.PushBack({ 329, 145, 68, 61 }, 0, -20);
	jump.PushBack({ 412, 112, 58, 94 }, 0, 7);
	jump.PushBack({ 485, 108, 54, 99 }, 0, -20);
	jump.PushBack({ 615, 40, 77, 62 }, 0, 35);
	jump.speed = 0.25f;

	jump.lock = true;

	crouchidle.PushBack({ 0, 482, 58, 88 }, 0, 15);
	crouchidle.PushBack({ 615, 40, 77, 62 }, 0, 41);
	/*crouchidle.PushBack({ 0, 482, 58, 88 }, 0, 15);*/
	crouchidle.speed = 0.2f;
	crouchidle.loop = false;
	
	if (flip) crouchidle.speed = 0.1f;
	if (!flip) crouchidle.speed = 0.05f;
	
	punch.PushBack({ 539, 105, 70, 103 });
	punch.PushBack({ 609, 109, 104, 99 },-15,0);
	punch.PushBack({ 713, 111, 74, 97 },-15,0);
	punch.PushBack({ 539, 105, 70, 103 });
	punch.speed = 0.15f;
	punch.lock = true;

	forward.PushBack({ 239,0,68,103 });
	forward.PushBack({ 322,0,58,103 });
	forward.PushBack({ 385,1,51,101 });
	forward.PushBack({ 447,1,48,102 });
	forward.PushBack({ 385,1,51,101 });
	forward.PushBack({ 322,0,58,103 });
	forward.speed = 0.1f;

	back.PushBack({ 322,0,58,103 });
	back.PushBack({ 385,1,51,101 });
	back.PushBack({ 447,1,48,102 });
	back.PushBack({ 385,1,51,101 });
	back.PushBack({ 322,0,58,103 });
	back.speed = 0.1f;
	//aquí van las cordenadas de las animaciones de la otra spritesheet, añadir tipo de animación cuando se solucione como añadir la otra spritesheet//

	//damaged------------> 0,135,66 ,107 // 66,134, 78, 108 // 144, 135, 66, 107
	//victory------------> 0,256,53 ,116 // 65, 266, 69, 106 
	//defeat-------------> 0, 0, 66, 115 // 66, 0, 73, 115 // 144, 8, 64, 107 // 208, 29, 62, 86 // 270, 53, 58, 62
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("RESOURCES/lee.png");
	/*graphs = App->textures->Load("ryo2.png");*/
	graphics2 = App->textures->Load("RESOURCES/ryo2.png");

	hp = 100;
	stamina = 100;
	playerCollider = App->collision->AddCollider({ position.x, position.y, 57, 108 }, COLLIDER_PLAYER2, this);
	winFrame2 = {65,266,69,106 };
	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	if (this->position.x >= App->player->position.x) flip = true;
	if (this->position.x <= App->player->position.x) flip = false;
	if (flip) flip_sign = -1;
	if (!flip) flip_sign = 1;

	playerCollider->SetPos(position.x, position.y);
	if (flip) playerCollider->SetPos(position.x + (current_animation->GetCurrentFrame().w) - playerCollider->rect.w, position.y);

	playerCollider->rect.h = 108;
	if (block != nullptr)
	{
		if (!flip)	block->SetPos(position.x + 55, position.y + 5);
		if (flip)	block->SetPos(position.x - 10, position.y + 5);
	}

	if (current_animation == &crouchidle || current_animation == &crouchpunch || current_animation == &crouchkick)
	{
		playerCollider->SetPos(position.x, position.y + 33);
		playerCollider->rect.h = 75;
	}


	if (jumping == JUMP_NOT) {
		speed.x = 0.0f;
	}

	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_UP) {
		//keyup[SDL_SCANCODE_D] = true;
		if (block != nullptr && flip) block->to_delete = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_UP) {
		//keyup[SDL_SCANCODE_A] = true;
		if (block != nullptr && !flip) block->to_delete = true;
	}

	if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN && keyup[SDL_SCANCODE_U] && current_animation->lock) {
		keyup[SDL_SCANCODE_U] = false;
		StoreInput(SDL_SCANCODE_U);
	}

	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN && keyup[SDL_SCANCODE_O] && current_animation->lock) {
		keyup[SDL_SCANCODE_O] = false;
		StoreInput(SDL_SCANCODE_O);
	}
	
	
	

	for (int i = 0; i < 69; i++) {
		if (App->input->keyboard[i] == KEY_STATE::KEY_UP) {
			keyup[i] = true;
		}
	}

	if (current_animation->Finished() || current_animation->lock == false && !App->player->p1Won && !App->player->p2Won)
	{
		if (current_animation->Finished()) {
			current_animation->Reset();
			if (melee != nullptr) melee->to_delete = true;

		}
		bool leaveif = false;

		current_animation = &idle;

		if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
			speed.x = 2.5f;
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/FIGHT/Jump.wav"));
		}

		if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN && App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
			speed.x = -2.5f;
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/FIGHT/Jump.wav"));
		}

		if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &crouchidle;
			playerCollider->rect.h = 75;

			if (keyup[SDL_SCANCODE_K]) {
				StoreInput(SDL_SCANCODE_K);
				keyup[SDL_SCANCODE_K] = false;
			}
		}

		if (!keyup[SDL_SCANCODE_K] && (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN)
			&& keyup[SDL_SCANCODE_U] && !leaveif)
		{
			current_animation = &crouchpunch;
			if (flip) melee = App->collision->AddCollider({ position.x - 50, position.y + 45, 55, 20 }, COLLIDER_PLAYER2_ATTACK, this);
			if (!flip) melee = App->collision->AddCollider({ position.x + 50, position.y + 45, 45, 20 }, COLLIDER_PLAYER2_ATTACK, this);
			leaveif = true;

			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/FIGHT/Punch_Attack.wav"));
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/RYO_VOICE_FXS/Ryo_Punch.wav"));

			if (keyup[SDL_SCANCODE_U]) {
				StoreInput(SDL_SCANCODE_U);
				keyup[SDL_SCANCODE_U] = false;
			}
		}

		if (!keyup[SDL_SCANCODE_K] && (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN)
			&& keyup[SDL_SCANCODE_O] && !leaveif)
		{
			current_animation = &crouchkick;
			if (flip) melee = App->collision->AddCollider({ position.x - 50, position.y + 75, 65, 35 }, COLLIDER_PLAYER1_ATTACK, this);
			if (!flip) melee = App->collision->AddCollider({ position.x + 50, position.y + 75, 65, 35 }, COLLIDER_PLAYER1_ATTACK, this);
			leaveif = true;

			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/FIGHT/Punch_Attack.wav"));
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/RYO_VOICE_FXS/Ryo_Kick_Groan.wav"));

			if (keyup[SDL_SCANCODE_O]) {
				StoreInput(SDL_SCANCODE_O);
				keyup[SDL_SCANCODE_O] = false;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
		{
			 current_animation = &back;
			

			speed.x = 2.5f;
			playerCollider->rect.h = 108;
			if (keyup[SDL_SCANCODE_L]) {
				StoreInput(SDL_SCANCODE_L);
				if (flip) { block = App->collision->AddCollider({ position.x - 20, position.y + 5, 15, 35 }, COLLIDER_WALL, this); }
				keyup[SDL_SCANCODE_L] = false;
			}
		}
		//cambiar//
		if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN)
		{
			current_animation = &forward;
			
			speed.x = -2.5f;
			playerCollider->rect.h = 108;
			if (keyup[SDL_SCANCODE_J]) {
				StoreInput(SDL_SCANCODE_J);
				if (!flip) { block = App->collision->AddCollider({ position.x + 60, position.y + 5, 10, 30 }, COLLIDER_WALL, this); }
				keyup[SDL_SCANCODE_J] = false;
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

		if (App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN) {
			current_animation = &jump;
			jumping = JUMP_UP;
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/FIGHT/Jump.wav"));

			if (keyup[SDL_SCANCODE_I]) {
				StoreInput(SDL_SCANCODE_I);
				keyup[SDL_SCANCODE_I] = false;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN && !leaveif && keyup[SDL_SCANCODE_U]) {
			current_animation = &punch;

			

			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/FIGHT/Punch_Attack.wav"));
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/RYO_VOICE_FXS/Ryo_Punch.wav"));


			if (!flip) melee = App->collision->AddCollider({ position.x + 50, position.y + 15, 40, 20 }, COLLIDER_PLAYER2_ATTACK, this, 10);
			if (flip) melee = App->collision->AddCollider({ position.x - 15, position.y + 15, 40, 20 }, COLLIDER_PLAYER2_ATTACK, this, 10);
			leaveif = true;
			if (keyup[SDL_SCANCODE_U]) {
				StoreInput(SDL_SCANCODE_U);
				keyup[SDL_SCANCODE_U] = false;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN && !leaveif && keyup[SDL_SCANCODE_O]) {
			current_animation = &kick;

			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/FIGHT/Punch_Attack.wav"));
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/RYO_VOICE_FXS/Ryo_Kick_Groan.wav"));

			if (!flip) melee = App->collision->AddCollider({ position.x + 50, position.y, 60, 40 }, COLLIDER_PLAYER2_ATTACK, this, 20);
			if (flip) melee = App->collision->AddCollider({ position.x + -50, position.y, 60, 40 }, COLLIDER_PLAYER2_ATTACK, this, 20);
			if (keyup[SDL_SCANCODE_O]) {
				StoreInput(SDL_SCANCODE_O);
				keyup[SDL_SCANCODE_O] = false;
			}
		}

		if ((TestSpecial(SDL_SCANCODE_O, SDL_SCANCODE_U, SDL_SCANCODE_L, SDL_SCANCODE_K) || App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) && !leaveif && (stamina >= 15)) {
			current_animation = &koukenR;
			App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/RYO_VOICE_FXS/Ryo_Kooken.wav"));
			App->particles->AddParticle(App->particles->kouken, position.x, position.y, COLLIDER_PLAYER2_ATTACK);
			App->audio->PlayChunk(App->audio->chunks[0]);
			stamina -= 15;
		}


	}

	if (hp <= 0 && App->player->p1Won != true)
	{
		hp = 0;
		/*current_animation = &defeat;*/

		App->player->p1Won = true;
		App->audio->PlayChunk(App->audio->LoadChunk("RESOURCES/MUSIC_FXS/FXS/RYO/RYO_VOICE_FXS/Ryo_Knocked.wav"));

		//current_animation = &death;
		playerCollider->to_delete = true;
	}

	if (stamina <= 0)
	{
		stamina = 0;
	}


	//Debug functionality-----------------------------------------

	/*if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN && keyup[SDL_SCANCODE_F2] || App->UI->currenthp2 <= 0)
	{
		p1Won = true;
		App->player2->hp = 0;
		App->audio->PlayChunk(App->audio->LoadChunk("MUSIC_FXS/FXS/RYO/RYO_VOICE_FXS/Ryo_Knocked.wav"));
		if (keyup[SDL_SCANCODE_F2])
		{
			keyup[SDL_SCANCODE_F2] = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN && keyup[SDL_SCANCODE_F3] || App->UI->currenthp1 <= 0)
	{
		p2Won = true;
		App->player->hp = 0;
		App->audio->PlayChunk(App->audio->LoadChunk("MUSIC_FXS/FXS/RYO/RYO_VOICE_FXS/Ryo_Knocked.wav"));
		if (keyup[SDL_SCANCODE_F3])
		{
			keyup[SDL_SCANCODE_F3] = false;
		}
	}*/

	//Jumping movement--------------------------------------------
	if (jumping != JUMP_NOT)
	{
		speed.y = (-1)*(8 + -0.5 * clock_parabolla);
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
	if (position.x <= 0) {
		position.x = 0;
	}
	if (position.x + playerCollider->rect.w >= 538) {
		position.x = 538 - playerCollider->rect.w;
	}
	if (position.x <= (App->player->position.x + (App->player2->playerCollider->rect.w / 2) + App->player2->position.x + (App->player->playerCollider->rect.w / 2)) / 2 - SCREEN_WIDTH / 2) {
		position.x = (App->player->position.x + (App->player2->playerCollider->rect.w / 2) + App->player2->position.x + (App->player->playerCollider->rect.w / 2)) / 2 - SCREEN_WIDTH / 2;
	}
	if (position.x + playerCollider->rect.w >= (App->player->position.x + (App->player2->playerCollider->rect.w / 2) + App->player2->position.x + (App->player->playerCollider->rect.w / 2)) / 2 + SCREEN_WIDTH / 2) {
		position.x = (App->player->position.x + (App->player2->playerCollider->rect.w / 2) + App->player2->position.x + (App->player->playerCollider->rect.w / 2)) / 2 + SCREEN_WIDTH / 2 - playerCollider->rect.w;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	if (!p2Won)
	{
		if ( current_animation == &victory || current_animation == &defeat) {

			App->render->Blit(graphics2, position.x + current_animation->GetOffset().x, position.y + current_animation->GetOffset().y, &r, 1.0f, flip);

		}
		else App->render->Blit(graphics, position.x + current_animation->GetOffset().x, position.y + current_animation->GetOffset().y, &r, 1.0f, flip);
	}

	if (p2Won)
	{
		if (wFrame > 0)
		{
			//current_animation = &victory;
			App->render->Blit(graphics2, position.x + current_animation->GetOffset().x, position.y + current_animation->GetOffset().y, &winFrame2, 1.0f, flip);
		}
		if (wFrame == 0)
		{
			current_animation = &victory;
			App->render->Blit(graphics2, position.x + current_animation->GetOffset().x, position.y + current_animation->GetOffset().y, &current_animation->GetCurrentFrame(), 1.0f, flip);
		}
		wFrame++;
	}
	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* A, Collider* B) {
	if (A->type == COLLIDER_PLAYER2_ATTACK && B->type == COLLIDER_PLAYER1)//Player2 lands hit on Player1
	{
		A->to_delete = true;

		if (current_animation != &damaged)
		{
			if (!App->player->godMode) { App->player->hp -= A->damage; }
			if (!flip) App->player->position.x += 15;
			if (flip) App->player->position.x -= 15;
			App->player->current_animation = &damaged;
		}

	}
	if (A->type == COLLIDER_PLAYER2 && B->type == COLLIDER_PLAYER1)
	{
		//App->player->speed.x = 1.0f;
		if (jumping == JUMP_DOWN && ((position.x > App->player->position.x && flip) || (position.x < App->player->position.x && !flip))) {
			if (flip) position.x += 5;
			if (!flip)position.x -= 5;
		}
		else if (jumping == JUMP_UP);
		else {
			if (flip) App->player2->position.x = App->player->position.x + App->player->playerCollider->rect.w;
			if (!flip)App->player2->position.x = App->player->position.x - playerCollider->rect.w;
		}
		if (!flip)App->player->position.x += 1.0f;
		if (flip) App->player->position.x -= 1.0f;
	}
	if (A->type == COLLIDER_WALL && B->type == COLLIDER_PLAYER2_ATTACK)
	{
		position.x -= 15;
		B->to_delete = true;
	}

}

bool ModulePlayer2::TestSpecial(SDL_Scancode A, SDL_Scancode B, SDL_Scancode C, SDL_Scancode D)
{
	int interval = 500;
	int d = inputCount - 1;
	if (inputCount == 0) d = MAX_INPUTS - 1;
	for (int i = inputCount; 1; i++) {

		if (i == (MAX_INPUTS)) i = 0;
		int j = i - 1; int k = i - 2; int l = i - 3;
		if (i == 2) { l = MAX_INPUTS - 1; }
		if (i == 1) { l = MAX_INPUTS - 2; k = MAX_INPUTS - 1; }
		if (i == 0) { l = MAX_INPUTS - 3; k = MAX_INPUTS - 2; j = MAX_INPUTS - 1; }
		if (input[i] == A && input[j] == B &&
			input[k] == C && input[l] == D) {

			if ((timeInput[i] - timeInput[j]) < interval &&
				(timeInput[j] - timeInput[k]) < interval &&
				(timeInput[k] - timeInput[l]) < interval) {

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


bool ModulePlayer2::CleanUp() {

	SDL_DestroyTexture(graphics);

	if (playerCollider != nullptr) playerCollider->to_delete = true;

	return true;

}
