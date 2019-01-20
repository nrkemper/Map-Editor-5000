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
	int		i, j, width, height;
	int		highlightX, highlightY, shiftX, shiftY;

	if (mapwindow.offset_x >= 0)
	{
		highlightX = (((x + (mapwindow.offset_x % map.tilewidth)) / (map.tilewidth + mapwindow.borderwidthX)) * (map.tilewidth + mapwindow.borderwidthX)) - (mapwindow.offset_x % map.tilewidth);
	}
	else
	{
		highlightX = (((x + mapwindow.offset_x) / (map.tilewidth + mapwindow.borderwidthX)) * (map.tilewidth + mapwindow.borderwidthX)) - mapwindow.offset_x;
	}

	if (mapwindow.offset_y >= 0)
	{
		highlightY = (((y + (mapwindow.offset_y % map.tileheight)) / (map.tileheight + mapwindow.borderwidthY)) * (map.tileheight + mapwindow.borderwidthY)) - (mapwindow.offset_y % map.tileheight);
	}
	else
	{
		highlightY = (((y + mapwindow.offset_y) / (map.tileheight + mapwindow.borderwidthY)) * (map.tileheight + mapwindow.borderwidthY)) - mapwindow.offset_y;
	}

	if (highlightX < 0)
	{
		width		= map.tilewidth + highlightX;
		highlightX	= 0;
	}
	else
	{
		width = map.tilewidth;
	}

	if (highlightY < 0)
	{
		height		= map.tileheight + highlightY;
		highlightY	= 0;
	}
	else
	{
		height = map.tileheight;
	}

	MAPW_DrawMapWindow ();

	for (i=highlightY; i<highlightY+height; i++)
	{
		for (j=highlightX; j<highlightX+width; j++)
			*(vid.buffer + (i * vid.width) + j) |= RGBTOPIXEL (0xff, 0, 0, 0);
	}

}

int	MAPW_GetTile (int x, int y)
{
	int		tileX, tileY;
	char	buffer[256];

	if (mapwindow.offset_x < 0)
	{
		if (x < (mapwindow.offset_x * -1))
			return -1;
		
		if (x > ((mapwindow.offset_x * -1) + (map.width * map.tilewidth)))
			return -1;
		
		tileX = (x + mapwindow.offset_x) / (map.tilewidth + mapwindow.borderwidthX);
		tileY = (y + mapwindow.offset_y) / (map.tileheight + mapwindow.borderwidthY);
	}
	else
	{
		if (x > ((map.width * map.tilewidth) - mapwindow.offset_x))
			return -1;
		
		tileX = (mapwindow.offset_x / map.tilewidth) + (x / (map.tilewidth + mapwindow.borderwidthX));
		tileY = (mapwindow.offset_y / map.tileheight) + (y / (map.tileheight + mapwindow.borderwidthY));
	}

	//tileX = (x + mapwindow.offset_x) / (map.tilewidth + mapwindow.borderwidthX);
	//tileY = (y + mapwindow.offset_y) / (map.tileheight + mapwindow.borderwidthY);

	sprintf (buffer, "TileX: %d\nTileY: %d\n", tileX, tileY);
	MessageBox (NULL, buffer, "Tile Position", MB_OK);
	return 0;
}

void MAPW_Shutdown (void)
{

}