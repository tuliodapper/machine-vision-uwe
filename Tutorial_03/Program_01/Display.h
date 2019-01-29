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
#define  PANEL_strTHRESHOLD               6       /* control type: string, callback function: (none) */
#define  PANEL_cmdCALCULATETHRESHOLD      7       /* control type: command, callback function: CalculateThreshold */
#define  PANEL_strMEDIANGREYLEVEL         8       /* control type: string, callback function: (none) */
#define  PANEL_cmdCALCULATEMEDIAN         9       /* control type: command, callback function: CalculateMedian */
#define  PANEL_cmdDISPLAY                 10      /* control type: command, callback function: DisplayImage */
#define  PANEL_cmdDISPLAYFREQHIST         11      /* control type: command, callback function: DisplayFreqHist */
#define  PANEL_btnQUIT                    12      /* control type: command, callback function: QuitProgram */
#define  PANEL_listTHRESHOLD              13      /* control type: listBox, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CalculateMean(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CalculateMedian(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CalculateThreshold(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayFreqHist(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayImage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitProgram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
