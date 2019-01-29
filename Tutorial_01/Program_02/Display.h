/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_cmdQUIT                    2       /* control type: command, callback function: QuitProgram */
#define  PANEL_cmdLOAD                    3       /* control type: command, callback function: Load */
#define  PANEL_NUMERIC                    4       /* control type: numeric, callback function: (none) */
#define  PANEL_STRING                     5       /* control type: string, callback function: (none) */
#define  PANEL_cmdSAVE                    6       /* control type: command, callback function: Save */
#define  PANEL_cmdDISPLAY                 7       /* control type: command, callback function: Display */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Display(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitProgram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
