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
#define  PANEL_FILENAME                   2       /* control type: string, callback function: File */
#define  PANEL_cmdLOAD                    3       /* control type: command, callback function: Load */
#define  PANEL_THRESHOLD                  4       /* control type: numeric, callback function: ThresholdValue */
#define  PANEL_cmdDISPLAY                 5       /* control type: command, callback function: Display */
#define  PANEL_cmdSAVE                    6       /* control type: command, callback function: Save */
#define  PANEL_THRESHOLD_MIN              7       /* control type: numeric, callback function: ThresholdValue */
#define  PANEL_THRESHOLD_MAX              8       /* control type: numeric, callback function: ThresholdValue */
#define  PANEL_cmdDISPLAY_2               9       /* control type: command, callback function: Display2 */
#define  PANEL_cmdSAVE_2                  10      /* control type: command, callback function: Save2 */
#define  PANEL_cmdQUIT                    11      /* control type: command, callback function: QuitProgram */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Display(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Display2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK File(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitProgram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ThresholdValue(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
