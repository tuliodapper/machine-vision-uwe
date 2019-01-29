# include <userint.h>
# include <utility.h>
# include <nivision.h>
# include "Display.h"  

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
											5 - Automatic Threshold
									*/
{
	char pathname[MAX_PATHNAME_LEN];
	unsigned char *imageArray; 
	int rows, cols, i, k, l;
	unsigned int histo[256] = { 0 }; // Inicializate histogram values with 0
	unsigned long sum = 0; // Inicializate sum values with 0
   	char output[50];
	float mean, new_mean;
	float sum_above, sum_below;
	long result, num_above, num_below;

		
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
			
		case 5: // Automatic Threshold
			
			// Clear the list which contains the calculated threshold values
			ClearListCtrl(panelHandle, PANEL_listTHRESHOLD);
			
			// Summing all grey level values 
			for (i=0; i<(rows*cols); i++)
			{
				sum = sum + imageArray[i];
			}
			
			// Calculate the initial mean grey level value (first guess)
			mean = (float) sum / (rows*cols);
			
			// Insert the initial mean greu level value in the list
			snprintf(output,50,"%f",mean);
			InsertListItem (panelHandle, PANEL_listTHRESHOLD, -1, output, -1);
			
			// Try 200 times at maximum
			result = 200;
			
			while (result)
			{
				// Initialise variables
				sum_above = 0; sum_below = 0; num_above = 0.0; num_below = 0.0;
				
				// Loop through the imageArray
				for (i=0; i<(rows*cols); i++)  
				{
					// If the grey level value of the pixel is above the mean grey level value, so...
					if ((float) (imageArray[i]) >= mean)
					{
						sum_above = sum_above + (float)(imageArray[i]);
						num_above++;
					}
					else
					{
						sum_below = sum_below + (float)(imageArray[i]);
						num_below++;
					}
				}
				
				// Avoiding division by zero
				if (num_above == 0) num_above = 1; 
				if (num_below == 0) num_below = 1;
				
				// Calculating the new mean grey level value
				new_mean = (sum_above / (float) num_above + sum_below / (float) num_below) / 2.0;
				
				// Finish the while if the mean grey level value is equal to the previous one...
				if (new_mean == mean)
					result = 0;
				else  // .. else, decrease the number of iterations in the while-loop
					result --;
				
				// Define new mean grey level value and, consequently, the new threshold
				mean = new_mean;
				
				// Insert the new threshold value in the list
				snprintf(output,50,"%f",mean);
				InsertListItem (panelHandle, PANEL_listTHRESHOLD, -1, output, -1);
			}

			// Set textbox strTHRESHOLD with the final result
			snprintf(output,50,"%f",mean);
			SetCtrlVal(panelHandle, PANEL_strTHRESHOLD, output);
			
			// Threshold the image using 'mean'
			for (i=0; i<(rows*cols); i++)
			{   
			 	if (imageArray[i] > (int) mean) {imageArray[i] = 255;} 
			 	else {imageArray[i] = 0;}  
			}

			imaqArrayToImage (myImage1,imageArray, cols, rows); // convert array to image and display
			imaqDisplayImage (myImage1, 0, 1);

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
			SetCtrlVal(panelHandle, PANEL_strTHRESHOLD, "");
			ClearListCtrl(panelHandle, PANEL_listTHRESHOLD);
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

int CVICALLBACK CalculateThreshold (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(5);
			break;
	}
	return 0;
}
