#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include <nivision.h>
#include "Display.h"

static int panelHandle;
Image* myImage1 = NULL; 

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

void ProcessImage(int DisplayorSave, int SingleOrMinMax)

// ###############
// -> DisplayorSave:
// 0 - Display
// 1 - Save
// ###############
// -> SingleOrMinMax
// 0 - Threshold is a single value
// 1 - There are minimum and maximum threshold values
// ###############

{
	char pathname[MAX_PATHNAME_LEN];
	unsigned char *imageArray; 
	int rows, cols, rr;
	int thresh = 0;
	int threshMin = 0;
	int threshMax = 0;
		
	myImage1 = imaqCreateImage(IMAQ_IMAGE_U8,0);
	
	GetCtrlVal(panelHandle, PANEL_FILENAME, pathname);
	GetCtrlVal(panelHandle, PANEL_THRESHOLD, &thresh);   
	GetCtrlVal(panelHandle, PANEL_THRESHOLD_MIN, &threshMin);   
	GetCtrlVal(panelHandle, PANEL_THRESHOLD_MAX, &threshMax);
	
	imaqReadFile(myImage1,pathname, NULL, NULL);	
	imageArray = imaqImageToArray (myImage1, IMAQ_NO_RECT, &cols, &rows);
	
	switch (SingleOrMinMax)
	{
		case 0: 
	
			for (rr=0; rr<(rows*cols); rr+=1)
			{   
				if (imageArray[rr] > thresh) {imageArray[rr] = 255;}
				if (imageArray[rr] < thresh) {imageArray[rr] = 0;} 
			}
			break;
	
		case 1: 			
			
			for (rr=0; rr<(rows*cols); rr+=1)
			{   
				if ((imageArray[rr] > threshMin) && (imageArray[rr] < threshMax)) {imageArray[rr] = 255;}
				else { imageArray[rr]=0; } 
			}
			break;
	}			
	
	imaqArrayToImage(myImage1,imageArray, cols, rows);	
	
	switch (DisplayorSave)
	{
		case 0: imaqDisplayImage(myImage1,0,1);
			break;
		case 1: imaqWriteBMPFile(myImage1, "C:\\IMAGEM.bmp", FALSE, NULL);
			break;
	}		
	
	imaqDispose(imageArray);										  
	imaqDispose(myImage1);
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
			SetCtrlVal(panelHandle, PANEL_FILENAME, pathname);
	}
	return 0;
}

int CVICALLBACK ThresholdValue (int panel, int control, int event,
					 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:			   
			
			break;
	}
	return 0;
}

int CVICALLBACK File (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK Display (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(0, 0);
			break;
	}
	return 0;
}

int CVICALLBACK Save (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(1, 0);
			break;
	}
	return 0;
}


int CVICALLBACK Display2 (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:  
			ProcessImage(0, 1);
			break;
	}
	return 0;
}

int CVICALLBACK Save2 (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(1, 1);
			break;
	}
	return 0;
}
