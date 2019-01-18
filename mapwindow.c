#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include "mapwindow.h"
#include "vid.h"
#include "frame.h"
#include "sprite.h"
#include "map.h"

mapwindow_t		mapwindow;

void MAPWIN_InitMapWindow (void)
{
	mapwindow.x				= 0;
	mapwindow.y				= 0;
	mapwindow.width			= frame.middle.x0 - 1;
	mapwindow.height		= frame.lefthor.y0 - 1;
	mapwindow.offset_x		= 0;
	mapwindow.offset_y		= 0;
	mapwindow.borderwidthX	= DEFAULT_BORDER_WIDTH_X;
	mapwindow.borderwidthY	= DEFAULT_BORDER_WIDTH_Y;
}

void MAPWIN_DrawMapWindow (void)
{
	int		vidX, vidY, vidStartX, vidStartY;
	int		mapX, mapY, mapStartX, mapStartY;
	int		tileindex;

	//FIXME: for testing
	char	buffer[256];

	if (mapwindow.offset_x >= 0)
	{
		mapStartX = floor ((double)mapwindow.offset_x / (double)map.tilewidth);
		vidStartX = 0 - (mapwindow.offset_x % map.tilewidth);
	}
	else
	{
		mapStartX = 0;
		vidStartX = 0 - mapwindow.offset_x;
	}

	if (mapwindow.offset_y >= 0)
	{
		mapStartY = floor ((double)mapwindow.offset_y / (double)map.tileheight);
		vidStartY = 0 - (mapwindow.offset_y % map.tileheight);
	}
	else
	{
		mapStartY = 0;
		vidStartY = 0 - mapwindow.offset_y;
	}


	//sprintf (buffer, "Map Start X: %d\nMap Start Y: %d\nVid Start X: %d\nVid Start Y: %d\n", mapStartX, mapStartY, vidStartX, vidStartY);
	//MessageBox (NULL, buffer, "Drawing Map", MB_OK);

	for (vidY=vidStartY, mapY=mapStartY; vidY<mapwindow.height && mapY<map.height; vidY+=map.tileheight+mapwindow.borderwidthY, mapY++)
	{
		for (vidX=vidStartX, mapX=mapStartX; vidX<mapwindow.width && mapX<map.width; vidX+=map.tilewidth+mapwindow.borderwidthX, mapX++)
		{
			tileindex = map.tileindexes[(mapY * map.width) + mapX];
			DrawSprite (vidX, vidY, mapwindow.width, mapwindow.height, map.tiles[tileindex]);
		}
	}
}

void MAPWIN_HighlightTile (int vidx, int vidy)
{

}

void MAPWIN_Shutdown (void)
{

}