#ifndef __ModuleFonts_H__
#define __ModuleFonts_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_FONTS 100
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font
{
	char table[MAX_FONT_CHARS];
	SDL_Texture* graphic = nullptr;
	uint rows, len, char_w, char_h, row_chars;
};

class ModuleFonts : public Module
{
public:

	ModuleFonts();
	~ModuleFonts();
	int Load(const char* texture_path, const char* characters, SDL_Rect &P, uint rows = 1);
	void UnLoad(int font_id);
	void BlitText(int x, int y, int bmp_font_id, const char* text, SDL_Rect &P) const;

private:

	Font	 fonts[MAX_FONTS];
};


#endif // __ModuleFonts_H__
