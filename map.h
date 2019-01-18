#ifndef __MAP_H__
#define __MAP_H__

#include "sprite.h"

#define DEFAULT_MAP_WIDTH		100  //tiles
#define DEFAULT_MAP_HEIGHT		20	
#define DEFAULT_TILEWIDTH		16
#define DEFAULT_TILEHEIGHT		16

#define MAX_TILE_INCREASE		10

typedef struct map_s
{
	int				width;		//in tiles
	int				height;
	char			tilewidth;
	char			tileheight;
	int				nTiles;			//number of tiles in tile palette
	int				nMaxTiles;		//number of allocated tiles in memory
	sprite_t**		tiles;			//tile palette
	unsigned int*	tileindexes;	//the map
} map_t;

extern map_t	map;			//the map that the user is working on

void MAP_InitMap (void);
int MAP_LoadMap (const char* file);
void MAP_SaveMap (const char* desfile);
void MAP_AddTile (const char* file);
void MAP_Shutdown (void);
#endif