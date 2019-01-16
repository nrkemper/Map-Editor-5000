#ifndef __VID_H__
#define __VID_H__

#define RGBTOPIXEL(r, g, b, a)	(pixel)(((r << vid.pfrmt.redshift) & vid.pfrmt.redmask) |\
										((g << vid.pfrmt.greenshift) & vid.pfrmt.greenmask) |\
										((b << vid.pfrmt.blueshift) & vid.pfrmt.bluemask) |\
										((a << vid.pfrmt.alphashift) & vid.pfrmt.alphamask))

#include <stdint.h>

typedef	uint32_t	pixel;

typedef struct pixelformat_s
{
	int			bitspixel;
	uint32_t	redmask;
	uint8_t		redshift;
	uint32_t	greenmask;
	uint8_t		greenshift;
	uint32_t	bluemask;
	uint8_t		blueshift;
	uint32_t	alphamask;
	uint8_t		alphashift;
} pixelformat_t;

typedef struct vid_s
{
	int				width;
	int				height;
	pixelformat_t	pfrmt;
	pixel*			buffer;
} vid_t;

extern vid_t	vid;

void VID_InitVGA (void);
void VID_CreateBuffer (void);
void VID_Resize (int width, int height);
void VID_DestroyVGA (void);
void VID_UpdateScreen (void);
void VID_Shutdown (void);

#endif