#ifndef __MAPWINDOW_H__
#define __MAPWINDOW_H__

typedef struct map_s
{
	int			width;
	int			height;
	//sprite_t*	tiles;
} map_t;

typedef struct mapwindow_s
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			tilewidth;
	int			tileheight;
	map_t		map;
} mapwindow_t;

extern mapwindow_t		mapwindow;

void MAP_InitMapWindow (void);
void MAP_DrawMapWindow (void);
void MAP_Shutdown (void);

#endif