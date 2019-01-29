/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2014. All Rights Reserved.          */
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
#define  PANEL_strFILENAME                2       /* control type: string, callback function: (none) */
#define  PANEL_cmdLOAD                    3       /* control type: command, callback function: Load */
#define  PANEL_cmdSEGMENTATION8           4       /* control type: command, callback function: Segmentation8 */
#define  PANEL_cmdSEGMENTATION4           5       /* control type: command, callback function: Segmentation4 */
#define  PANEL_cmdDISPLAY                 6       /* control type: command, callback function: DisplayImage */
#define  PANEL_btnQUIT                    7       /* control type: command, callback function: QuitProgram */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK DisplayImage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitProgram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Segmentation4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Segmentation8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
