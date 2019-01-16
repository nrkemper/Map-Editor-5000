#ifndef __MAPWINDOW_H__
#define __MAPWINDOW_H__

typedef struct map_s
{
	unsigned int	width;//in tiles
	unsigned int	height;
	unsigned int	nTiles;
	unsigned int*	tileindexes;
	//sprite_t*	tiles;
} map_t;

typedef struct mapwindow_s
{
	unsigned int		x;
	unsigned int		y;
	unsigned int		width;
	unsigned int		height;
	unsigned short int	tilewidth;
	unsigned short int	tileheight;
	map_t				map;
} mapwindow_t;

extern mapwindow_t		mapwindow;

void MAP_InitMapWindow (void);
void MAP_DrawMapWindow (void);
void MAP_Shutdown (void);

#endif