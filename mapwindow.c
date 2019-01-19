#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include "mapwindow.h"
#include "vid.h"
#include "frame.h"
#include "sprite.h"
#include "map.h"

mapwindow_t		mapwindow;

void MAPW_InitMapWindow (void)
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

void MAPW_DrawMapWindow (void)
{
	int		vidX, vidY, vidStartX, vidStartY;
	int		mapX, mapY, mapStartX, mapStartY;
	int		tileindex;

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

	for (vidY=vidStartY, mapY=mapStartY; vidY<mapwindow.height && mapY<map.height; vidY+=map.tileheight+mapwindow.borderwidthY, mapY++)
	{
		for (vidX=vidStartX, mapX=mapStartX; vidX<mapwindow.width && mapX<map.width; vidX+=map.tilewidth+mapwindow.borderwidthX, mapX++)
		{
			tileindex = map.tileindexes[(mapY * map.width) + mapX];
			DrawSprite (vidX, vidY, mapwindow.width, mapwindow.height, map.tiles[tileindex]);
		}
	}
}

void MAPW_HighlightTile (int x, int y)
{
	int		i, j;
	int		highlightX, highlightY, shiftX, shiftY;
	char buffer[256];

	//if (mapwindow.offset_x < 0)
	//	shiftX = (mapwindow.offset_x * -1) % map.tilewidth;
	//else
	//	shiftX = mapwindow.offset_x % map.tilewidth;

	//if (mapwindow.offset_y < 0)
	//	shiftY = (mapwindow.offset_y * -1) % map.tileheight;
	//else
	//	shiftY = mapwindow.offset_y % map.tileheight;

	//highlightX = x - (x % (map.tilewidth + mapwindow.borderwidthX + shiftX));
	//highlightY = y - (y % (map.tileheight + mapwindow.borderwidthY + shiftY));

	if (mapwindow.offset_x < 0)
		shiftX = mapwindow.offset_x * -1;
	else
		shiftX = mapwindow.offset_x % map.tilewidth;

	if (mapwindow.offset_y < 0)
		shiftY = mapwindow.offset_y * -1;
	else
		shiftY = mapwindow.offset_y % map.tileheight;

	highlightX = ((x - shiftX) / (map.tilewidth + mapwindow.borderwidthX) * (map.tilewidth + mapwindow.borderwidthX)) + shiftX;
	highlightY = ((y - shiftY) / (map.tileheight + mapwindow.borderwidthY) * (map.tileheight + mapwindow.borderwidthY)) + shiftY;

	MAPW_DrawMapWindow ();

	for (i=highlightY; i<highlightY+map.tileheight; i++)
	{
		for (j=highlightX; j<highlightX+map.tilewidth; j++)
			*(vid.buffer + (i * vid.width) + j) |= RGBTOPIXEL (0xff, 0, 0, 0);
	}

}

int	MAPW_GetTileNum (int x, int y)
{
	return 0;
}

void MAPW_Shutdown (void)
{

}