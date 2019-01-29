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
#define  PANEL_strFILENAME                2       /* control type: string, callback function: (none) */
#define  PANEL_cmdLOAD                    3       /* control type: command, callback function: Load */
#define  PANEL_strAREA                    4       /* control type: string, callback function: (none) */
#define  PANEL_cmdCALCULATE               5       /* control type: command, callback function: Calculate */
#define  PANEL_strBLOBWIDTHd              6       /* control type: string, callback function: (none) */
#define  PANEL_strBLOBWIDTHb              7       /* control type: string, callback function: (none) */
#define  PANEL_strSF                      8       /* control type: string, callback function: (none) */
#define  PANEL_strANGLE_N90               9       /* control type: string, callback function: (none) */
#define  PANEL_strANGLE_N                 10      /* control type: string, callback function: (none) */
#define  PANEL_strANGLE                   11      /* control type: string, callback function: (none) */
#define  PANEL_strCENTROIDY               12      /* control type: string, callback function: (none) */
#define  PANEL_strCENTROIDX               13      /* control type: string, callback function: (none) */
#define  PANEL_cmdDISPLAY                 14      /* control type: command, callback function: DisplayImage */
#define  PANEL_cmdDISPLAYFREQHIST         15      /* control type: command, callback function: DisplayFreqHist */
#define  PANEL_btnQUIT                    16      /* control type: command, callback function: QuitProgram */
#define  PANEL_TEXTMSG                    17      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_AXIS               18      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  19      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Calculate(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayFreqHist(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayImage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitProgram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
