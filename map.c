#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "sprite.h"

map_t		map;			//the map that the user is working on
sprite_t*	blank;

void _mapalloctilemem (void)
{
	int			i;
	sprite_t**	newtiles;
	
	//alloc new mem
	map.nMaxTiles += MAX_TILE_INCREASE;
	newtiles = (sprite_t**)malloc (map.nMaxTiles * sizeof (sprite_t*));

	//init new tiles
	for (i=0 ; i<map.nMaxTiles ; i++)
		newtiles[i] = (sprite_t*)0;

	//copy
	for (i=0 ; i<map.nTiles ; i++)
		newtiles[i] = map.tiles[i];

	free (map.tiles);
	map.tiles = newtiles;
}

void MAP_InitMap (void)
{
	int			i;

	map.width		= DEFAULT_MAP_WIDTH;
	map.height		= DEFAULT_MAP_HEIGHT;
	map.tilewidth	= DEFAULT_TILEWIDTH;
	map.tileheight	= DEFAULT_TILEHEIGHT;
	map.nTiles		= 0;
	map.nMaxTiles	= 0;
	map.tiles		= (sprite_t**)0;
	map.tileindexes	= (unsigned int*)0;

	_mapalloctilemem ();
	MAP_AddTile ("..\\..\\resources\\blanktile.spt");

	map.tileindexes = (unsigned int*)malloc (map.width * map.height * sizeof (unsigned int));
	for (i=0; i<map.width * map.height; i++)
		map.tileindexes[i] = 0; 
}

int MAP_LoadMap (const char* file)
{

}

void MAP_SaveMap (const char* desfile)
{

}

void MAP_AddTile (const char* file)
{
	char		buffer[256];
	sprite_t*	newtile = LoadSpriteFile (file);

	if (newtile == NULL)
	{
		sprintf (buffer, "Unable to load sprite file: %s", file);
		MessageBox (NULL, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	if (newtile->width != map.tilewidth)
	{
		sprintf (buffer, "Invalid width for %s", file);
		MessageBox (NULL, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		FreeSprite (newtile);
		return;
	}

	if (newtile->height != map.tileheight)
	{
		sprintf (buffer, "Invalid height for %s", file);
		MessageBox (NULL, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		FreeSprite (newtile);
		return;
	}
	//FIXME: need to split tile if it is bigger than tile width/height
	map.tiles[map.nTiles++] = newtile;
}

void MAP_Shutdown (void)
{
	int		i;

	for (i=0 ; i<map.nTiles ; i++)
		FreeSprite (map.tiles[i]);

	free (map.tiles);
	free (map.tileindexes);
}