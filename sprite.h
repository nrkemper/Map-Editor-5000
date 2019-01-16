#ifndef __SPRITE_H__
#define __SPRITE_H__
#include "vid.h"

typedef struct sprite_s
{
	int		width;
	int		height;
	int		bitdepth;
	pixel*	data;
	pixel*	mask;
	pixel*	background;
} sprite_t;

sprite_t* LoadSpriteFile (const char* file);
void DrawSprite (int x, int y, int x_clip, int y_clip, sprite_t* sprite);
void FreeSprite (sprite_t* sprite);

#endif