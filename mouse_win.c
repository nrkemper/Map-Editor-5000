#include <Windows.h>
#include "mouse.h"
#include "frame.h"

HCURSOR		hcurDefault;
HCURSOR		hcurSizeWE;
HCURSOR		hcurSizeNS;

void M_InitMouse (void)
{
	hcurDefault		= LoadCursor (NULL, IDC_ARROW);
	hcurSizeWE		= LoadCursor (NULL, IDC_SIZEWE);
	hcurSizeNS		= LoadCursor (NULL, IDC_SIZENS);
}

void M_ProcessInput (int msg, int wParam, int lParam);

void M_SetCursor (void)
{
	if (hoveringEastWest)
		SetCursor (hcurSizeWE);
	else if (hoveringNorthSouth)
		SetCursor (hcurSizeNS);
	else
		SetCursor (hcurDefault);
}

void M_Shutdown (void)
{
	DestroyCursor (hcurDefault);
	DestroyCursor (hcurSizeWE);
	DestroyCursor (hcurSizeNS);
}