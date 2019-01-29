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
#define  PANEL_cmdEROSION8                4       /* control type: command, callback function: Erosion8 */
#define  PANEL_cmdBOUNDARY4               5       /* control type: command, callback function: Boundary4 */
#define  PANEL_cmdEROSION4                6       /* control type: command, callback function: Erosion4 */
#define  PANEL_cmdDISPLAY                 7       /* control type: command, callback function: DisplayImage */
#define  PANEL_btnQUIT                    8       /* control type: command, callback function: QuitProgram */
#define  PANEL_strTIMES                   9       /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Boundary4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisplayImage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Erosion4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Erosion8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitProgram(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
