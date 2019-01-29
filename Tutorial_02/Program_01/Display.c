#include <utility.h>
#include <nivision.h>
#include "Display.h"  

static int panelHandle;
Image* myImage1 = NULL; 

void MsgBox(char *s){
    char cmd[1024];
    sprintf(cmd, "xmessage -center \"%s\"", s);
}

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

void ProcessImage(int inOperation) 	/* 	"inOperation" Options:
											1 - Display Image
								 	 		2 - Display Frequency Histogram
											3 - Calculate Mean Grey Level
											4 - Calculate Median Grey Level
									*/
{
	char pathname[MAX_PATHNAME_LEN];
	unsigned char *imageArray; 
	int rows, cols, i, k, l;
	unsigned int histo[256] = { 0 }; // Inicializate histogram values with 0
	unsigned int sum = 0; // Inicializate sum values with 0
   	char output[50];
		
	myImage1 = imaqCreateImage(IMAQ_IMAGE_U8,0);
	
	// Get pathfile from textbox "strFILENAME"
	GetCtrlVal(panelHandle, PANEL_strFILENAME, pathname);
	
	imaqReadFile(myImage1,pathname, NULL, NULL);
	imageArray = imaqImageToArray (myImage1, IMAQ_NO_RECT, &cols, &rows);
	imaqArrayToImage(myImage1,imageArray, cols, rows);
	
	switch (inOperation)
	{
		case 1: // Display Image
			imaqDisplayImage(myImage1,0,1);
			break;
			
		case 2: // Display Frequency Histogram
			
			// Processing Histogram Values
			for (i=0; i<(rows*cols); i++)
			{
				k = imageArray[i];
				histo[k] = histo[k] + 1;
			}
			
			// Ploting Graph
			YGraphPopup("Frequency Histogram", &histo, 256, VAL_UNSIGNED_INTEGER);
			
			break;
			
		case 3: // Calculate Mean Grey Level
			
			// Summing all grey level values 
			for (i=0; i<(rows*cols); i++)
			{
				sum = sum + imageArray[i];
			}
			
			// Mean Grey Level = (Sum of grey values) / (Number of pixels)
			// Convert Float to String
			snprintf(output,50,"%f",(float) sum/(rows*cols));
			
			// Set textbox strMeanGreyLevel with Mean Grey Level (output)
			SetCtrlVal(panelHandle, PANEL_strMEANGREYLEVEL, output);
			
			break;
			
		case 4: // Calculate Median Grey Level
			
			// sum = (Number of pixels)
			sum = (rows*cols);
			
			// Processing Histogram Values
			for (i=0; i<(sum); i++)
			{
				k = imageArray[i];
				histo[k] = histo[k] + 1;
			}
			
			l = 0;
			
			// Arranging the values in a crescent order
			// Loop through the histogram diagram
			for (i=0; i<256; i++) 
			{   			
				// Placing the value 'i' for 'histo[i]' times 
				for (k=0; k<histo[i]; k++)
				{		
					imageArray[l] = i;
					l++;
				}
			}
	       	
			/*
			If the Number of Pixels is even, so the Median value is equal to (imageArray[(sum/2) - 1] + imageArray[(sum/2)])/2
				else
			If the Number of Pixels is odd, so the Median value is equal to imageArray[(sum/2)
			*/
																	 
			if(((sum%2) == 0) && sum!=0){ 	// Number of pixels is Even
				
				// Median Grey Level = (imageArray[(sum/2) - 1] + imageArray[(sum/2)])/2
				// Convert Float to String
				snprintf(output,50,"%f",(float) (imageArray[(sum/2) - 1] + imageArray[(sum/2)])/2);
				
	        } else { 						// Number of pixels is Odd
				
				// Median Grey Level = imageArray[(sum/2)
				// Convert Float to String
				snprintf(output,50,"%f",(float) imageArray[(sum/2)]);
            }		  
			
			// Set textbox strMedianGreyLevel with Median Grey Level (output)
			SetCtrlVal(panelHandle, PANEL_strMEDIANGREYLEVEL, output);
			
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
			SetCtrlVal(panelHandle, PANEL_strFILENAME, pathname);
			SetCtrlVal(panelHandle, PANEL_strMEANGREYLEVEL, "");
			SetCtrlVal(panelHandle, PANEL_strMEDIANGREYLEVEL, "");
	}
	return 0;
}

int CVICALLBACK DisplayImage (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(1);
			break;
	}
	return 0;
}

int CVICALLBACK DisplayFreqHist (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(2);
			break;
	}
	return 0;
}


int CVICALLBACK CalculateMean (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:  
			ProcessImage(3);
			break;
	}
	return 0;
}

int CVICALLBACK CalculateMedian (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(4);
			break;
	}
	return 0;
}
