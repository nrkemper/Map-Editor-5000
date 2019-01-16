#include <Windows.h>
#include "mapwindow.h"
#include "vid.h"
#include "frame.h"
#include "sprite.h"

mapwindow_t		mapwindow;
//FIXME: for testing only
sprite_t*		blank;

void MAP_InitMapWindow (void)
{
	mapwindow.x = 0;
	mapwindow.y = 0;
	mapwindow.width = frame.middle.x0 - 1;
	mapwindow.height = frame.lefthor.y0 - 1;

	blank = LoadSpriteFile ("..\\..\\resources\\blanktile.spt");

	if (blank==NULL)
		MessageBox (NULL, "Unable to load blank sprite", "ERROR", MB_OK);
}

void MAP_DrawMapWindow (void)
{
	int		x, y;


	//FIXME: only dealing with 16 width tiles
	for (x=16 ; x<mapwindow.width ; x+=16)
	{
		for (y=0 ; y<mapwindow.height ; y++)
		{
			*(vid.buffer + (y * vid.width) + x) = RGBTOPIXEL (0, 0, 0, 0);
		}
		x++;
	}

	//FIXME: only dealing with 16 width tiles
	for (y=16 ; y<mapwindow.height ; y+=16)
	{
		for (x=0 ; x<mapwindow.width ; x++)
		{
			*(vid.buffer + (y * vid.width) + x) = RGBTOPIXEL (0, 0, 0, 0);
		}
		y++;
	}

	for (y=0 ; y<frame.lefthor.y0; y+=blank->height)
	{
		for (x=0 ; x<frame.middle.x0; x+= blank->width)
		{
			DrawSprite (x, y, mapwindow.width, mapwindow.height, blank);
			x++;
		}
		y++;
	}
}

void MAP_Shutdown (void)
{
	FreeSprite (blank);
}