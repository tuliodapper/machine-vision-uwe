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
#define  PANEL_strMEANGREYLEVEL           4       /* control type: string, callback function: (none) */
#define  PANEL_cmdCALCULATEMEAN           5       /* control type: command, callback function: CalculateMean */
#define  PANEL_strMEDIANGREYLEVEL         6       /* control type: string, callback function: (none) */
#define  PANEL_cmdCALCULATEMEDIAN         7       /* control type: command, callback function: CalculateMedian */
#define  PANEL_cmdDISPLAY                 8       /* control type: command, callback function: DisplayImage */
#define  PANEL_cmdDISPLAYFREQHIST         9       /* control type: command, callback function: DisplayFreqHist */
#define  PANEL_btnQUIT                    10      /* control type: command, callback function: QuitProgram */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CalculateMean(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CalculateMedian(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayFreqHist(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayImage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitProgram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
