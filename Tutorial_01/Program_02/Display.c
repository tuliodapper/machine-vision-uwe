#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include <nivision.h>
#include "Display.h"

static int panelHandle;
Image* myImage1 = NULL; 
int thresh = 0;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Display.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK QuitProgram (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK Load (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	char pathname[MAX_PATHNAME_LEN],dirname[MAX_PATHNAME_LEN];
	int status;
	switch (event)
	{
		case EVENT_COMMIT:
			GetProjectDir(dirname);
			status = FileSelectPopup("","","","Select Image",VAL_OK_BUTTON,0,1,1,0,pathname);
			if(status==0){break;}
			SetCtrlVal(panelHandle, PANEL_STRING, pathname);
	}
	return 0;
}

int CVICALLBACK Display (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	char pathname[MAX_PATHNAME_LEN];
	unsigned char *imageArray; 
	int rows, cols, rr;
	switch (event)
	{
		case EVENT_COMMIT:
			myImage1 = imaqCreateImage(IMAQ_IMAGE_U8,0);
			GetCtrlVal(panelHandle, PANEL_STRING, pathname);
			imaqReadFile(myImage1,pathname, NULL, NULL);	
			imageArray = imaqImageToArray (myImage1, IMAQ_NO_RECT, &cols, &rows);
			GetCtrlVal(panelHandle, PANEL_NUMERIC, &thresh);
			for (rr=0; rr<(rows*cols); rr+=1)
			{   
			 if (imageArray[rr] > thresh) {imageArray[rr] = 255;}
			 if (imageArray[rr] < thresh) {imageArray[rr] = 0;} 
			}
			imaqArrayToImage(myImage1,imageArray, cols, rows);		  		 
			imaqDisplayImage(myImage1,0,1);													    
			imaqDispose(imageArray);										  
			imaqDispose(myImage1);
			break;
	}
	return 0;
}

int CVICALLBACK Save (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	char pathname[MAX_PATHNAME_LEN];
	unsigned char *imageArray; 
	int rows, cols, rr;
	switch (event)
	{
		case EVENT_COMMIT:
			myImage1 = imaqCreateImage(IMAQ_IMAGE_U8,0);
			GetCtrlVal(panelHandle, PANEL_STRING, pathname);
			imaqReadFile(myImage1,pathname, NULL, NULL);	
			imageArray = imaqImageToArray (myImage1, IMAQ_NO_RECT, &cols, &rows);
			GetCtrlVal(panelHandle, PANEL_NUMERIC, &thresh);
			for (rr=0; rr<(rows*cols); rr+=1)
			{   
			 if (imageArray[rr] > thresh) {imageArray[rr] = 255;}
			 if (imageArray[rr] < thresh) {imageArray[rr] = 0;} 
			}
			imaqArrayToImage(myImage1,imageArray, cols, rows);		
			imaqWriteBMPFile(myImage1, "C:\\IMAGEM.bmp", FALSE, NULL);  					    
			imaqDispose(imageArray);										  
			imaqDispose(myImage1);
			break;
	}
	return 0;
}
