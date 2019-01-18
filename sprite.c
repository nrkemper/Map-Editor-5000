#include <Windows.h>
#include "sprite.h"
#include "vid.h"
#include "typedefs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

sprite_t* LoadSpriteFile (const char* file)
{
	uint32_t	width, height, bpp, offset;
	int			numPixels, cnt=0;
	sprite_t*	ret=NULL;
	rgb_t		tmp;
	pixel		white = RGBTOPIXEL (255, 255, 255, 0), black=RGBTOPIXEL (0, 0, 0, 0);
	FILE*		fp = fopen (file, "r");

	if (fp == NULL)
	{
		printf ("ERROR: unable to open %s\n", file);
		return NULL;
	}

	ret = (sprite_t*)malloc (sizeof (sprite_t));
	if (ret == NULL)
	{
		printf ("ERROR: unable to allocate memory for %s\n", file);
		return NULL;
	}

	fread (&width, sizeof (uint32_t), 1, fp);
	fread (&height, sizeof (uint32_t), 1, fp);
	fread (&bpp, sizeof (uint32_t), 1, fp);
	fread (&offset, sizeof (uint32_t), 1, fp);

	ret->width		= ntohl (width);
	ret->height		= ntohl (height);
	ret->bitdepth	= ntohl (bpp);
	offset			= ntohl (offset);

	numPixels = ret->width * ret->height;

	ret->data = (pixel*)malloc (numPixels * sizeof (pixel));
	ret->mask = (pixel*)malloc (numPixels * sizeof (pixel));
	ret->background = (pixel*)malloc (numPixels * sizeof (pixel));

	memset (ret->data, 0, numPixels * sizeof(pixel));
	memset (ret->mask, 0, numPixels * sizeof(pixel));
	memset (ret->background, 0, numPixels * sizeof(pixel));

	while (cnt < numPixels)
	{
		fread (&tmp.r, sizeof (uint8_t), 1, fp);
		fread (&tmp.g, sizeof (uint8_t), 1, fp);
		fread (&tmp.b, sizeof (uint8_t), 1, fp);
		fread (&tmp.alpha, sizeof (uint8_t), 1, fp);

		if (tmp.r == 0 && tmp.b == 255 && tmp.g == 255)
		{
			ret->data[cnt] = black;
			ret->mask[cnt] = white;
		}
		else
		{
			ret->data[cnt] = RGBTOPIXEL (tmp.r, tmp.g, tmp.b, tmp.alpha);
			ret->mask[cnt] = black;
		}
		cnt++;
	}

	printf ("Loaded sprite: %s\n", file);
	fclose (fp);
	return ret;
}

void DrawSprite (int x, int y, int x_clip, int y_clip, sprite_t* sprite)
{
	int		i, j, width, height, indexVid, indexBM;

	if (x > x_clip)
		return;

	if (y > y_clip)
		return;

	if (x < 0)
	{
		if (x + sprite->width > 0)
		{
			width = x + sprite->width;
			x = 0;
		}
		else
			return;
	}
	else
	{		
		if (x + sprite->width > x_clip)
			width = x_clip - x;
		else
			width = sprite->width;
	}

	if (y < 0)
	{
		if (y + sprite->height > 0)
		{
			height = y + sprite->height;
			y = 0;
		}
		else
			return;
	}
	else
	{
		if (y + sprite->height > y_clip)
			height = y_clip - y;
		else
			height = sprite->height;
	}

	for (i=0 ; i<height ; i++)
	{
		for (j=0 ; j<width ; j++)
		{
			indexVid = ((i + y) * vid.width) + x + j;
			indexBM = (i * sprite->width) + j;

			*(sprite->background + indexBM) = *(vid.buffer + indexVid);
			*(vid.buffer + indexVid) &= *(sprite->mask + indexBM);
			*(vid.buffer + indexVid) |= *(sprite->data + indexBM);
		}
	}

}

void FreeSprite (sprite_t* sprite)
{
	free (sprite->data);
	free (sprite->mask);
	free (sprite->background);
	free (sprite);
}