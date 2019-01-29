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
#define  PANEL_cmdHORIZONTAL              4       /* control type: command, callback function: Horizontal */
#define  PANEL_cmdGENERALSOBEL            5       /* control type: command, callback function: GeneralSobel */
#define  PANEL_cmdGENERALLAPLACIAN        6       /* control type: command, callback function: GeneralLaplacian */
#define  PANEL_cmd4KIRSCHOPERATORS        7       /* control type: command, callback function: KirschOperators */
#define  PANEL_cmdDIAGONAL2               8       /* control type: command, callback function: Diagonal2 */
#define  PANEL_cmdDIAGONAL1               9       /* control type: command, callback function: Diagonal1 */
#define  PANEL_cmdVERTICAL                10      /* control type: command, callback function: Vertical */
#define  PANEL_cmdDISPLAY                 11      /* control type: command, callback function: DisplayImage */
#define  PANEL_btnQUIT                    12      /* control type: command, callback function: QuitProgram */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Diagonal1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Diagonal2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayImage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GeneralLaplacian(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GeneralSobel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Horizontal(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK KirschOperators(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitProgram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Vertical(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
