#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"

#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#define MAX_CHUNKS 50
#define DEFAULT_VOLUME 50

class ModuleAudio : public Module
{
public:

	ModuleAudio();
	~ModuleAudio();

	bool Init();
	update_status Update();
	bool CleanUp() ;
	Mix_Chunk * LoadChunk(const char* path);
	bool PlayMusic(const char* path, int loops);
	bool PlayChunk(Mix_Chunk * sound);
	void StopMusic();

public:
	Mix_Chunk * chunks[MAX_CHUNKS];
	Mix_Music * music; 

	int chunk_number = 0;

//<<<<<<< HEAD
   /* Mix_Chunk* koukenFx; 
	Mix_Chunk* PunchAttack;*/ //-> DONE
	//-> Idealmente esto solo es como nombre de comodidad, solo un puntero, lo importante es chunks, para luego limpiar todos los chunks y evitar M. Leaks
//=======
    Mix_Chunk* koukenFx; // Idealmente esto solo es como nombre de comodidad, solo un puntero, lo importante es chunks, para luego limpiar todos los chunks y evitar M. Leaks

//>>>>>>> 2433479078b1082cdc5f9a3c0fc665b00183240a
};

#endif // __ModuleAudio_H__