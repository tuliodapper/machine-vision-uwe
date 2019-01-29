#include <userint.h>
#include "Display.h"

# include <userint.h>
# include <utility.h>
# include <nivision.h>
# include "Display.h"  

static int panelHandle;
Image* myImage1 = NULL; 
int Array[100][100];
static const RGBValue IMAQ_RGB_PINK = {100, 100, 255, 0 };


void mark4 (int value, int iseed, int jseed)
{

	int i, n, m;
	int matrix[4][2] = {{-1, 0},
						{ 0, 1},
						{ 1, 0},
						{ 0,-1}};

	//This is not a black pixel! Stop.
	if (Array[iseed][jseed] !=0) return;
	//Set this pixel to the mark value
	Array[iseed][jseed] = value;
	//Now look for the four neighbours of the current pixel
	//The neighbours are related with each line of matrix[][]
	for (i=0; i<4; i++)
	{
		n = iseed + matrix[i][0];
		m = jseed + matrix[i][1];
		//Make sure that the pixel (n,m) belongs to the image
		if(n<0 || n>99) continue;
		if(m<0 || m>99) continue;
		//Found a black neighbour
		if(Array[n][m] == 0)
			mark4(value, n, m);
	}
}

void mark8 (int value, int iseed, int jseed)
{

	int i, n, m;
	int matrix[8][2] = {{-1, 0},
						{-1, 1},
						{ 0, 1},
						{ 1, 1},
						{ 1, 0},
						{ 1,-1},
						{ 0,-1},
						{-1,-1}};

	//This is not a black pixel! Stop.
	if (Array[iseed][jseed] !=0) return;
	//Set this pixel to the mark value
	Array[iseed][jseed] = value;
	//Now look for the four neighbours of the current pixel
	//The neighbours are related with each line of matrix[][]
	for (i=0; i<8; i++)
	{
		n = iseed + matrix[i][0];
		m = jseed + matrix[i][1];
		//Make sure that the pixel (n,m) belongs to the image
		if(n<0 || n>99) continue;
		if(m<0 || m>99) continue;
		//Found a black neighbour
		if(Array[n][m] == 0)
			mark8(value, n, m);
	}
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
								 	 		2 - Segmentation 4-Connected
											3 - Segmentation 8-Connected  
									*/
{
	char pathname[MAX_PATHNAME_LEN];
	unsigned char *imageArray; 
	int rows, cols,i,j,c,value;
	RGBValue *imageArrayDisplay; 


	myImage1 = imaqCreateImage(IMAQ_IMAGE_U8,0);
	
	// Get pathfile from textbox "strFILENAME"
	GetCtrlVal(panelHandle, PANEL_strFILENAME, pathname);
	
	imaqReadFile(myImage1,pathname, NULL, NULL);
	imageArray = imaqImageToArray (myImage1, IMAQ_NO_RECT, &cols, &rows);
	
	switch (inOperation)
	{
		case 1: // Display Image
			imaqArrayToImage(myImage1,imageArray, cols, rows);
			imaqDisplayImage(myImage1,0,1);
			break;
			
		case 2: // Segmentation 4-Connected
		case 3: // Segmentation 8-Connected
			
			
				// ##### Convert 1D array to a 2D array #####
				c = 0;
				for(i=0; i<rows; i++) //repeats for n lines
					{
					for(j=0; j<cols; j++)
						{
						Array[i][j]=imageArray[c];
						c = c+1;
						}
					}
				// #####
				

				// ##### Search for a seed pixel in a black region and call the mark funcion #####
				value = 0;
				for(i=0; i<100; i++) // look through all the lines
				{
					for(j=0; j<100; j++) // look through all the columns
					{
						if(Array[i][j] == 0)
						{
							value = value + 1; // value to label the new region
							
							if (inOperation == 2) // call mark4 or mark8 function, depending on the requested operation 
								mark4(value, i, j);
							else
								mark8(value, i, j);
						}
							
					}
				}
				// #####
				
				
				// ##### Convert 2D array to a 1D array #####
				c = 0;
				for(i=0; i<rows; i++) //repeats for n lines
				{
					for(j=0; j<cols; j++)
					{
						imageArray[c] = Array[i][j];
						c = c+1;
					}
				}			 
				// #####
				
					
				// ##### Display segmented regions using different colours #####
				imaqArrayToImage(myImage1,imageArray, cols, rows);
				imaqWriteBMPFile(myImage1, "C:\\IMAGEM.bmp", FALSE, NULL);

				myImage1 = imaqCreateImage (IMAQ_IMAGE_RGB, 0);//RGB image
				imaqReadFile(myImage1, "C:\\IMAGEM.bmp", NULL, NULL ); // Read image file
				imageArrayDisplay = imaqImageToArray (myImage1, IMAQ_NO_RECT, &cols,&rows);
				for (i=0; i<(rows*cols); i+=1)
				{
					if (imageArrayDisplay[i].R == 1){imageArrayDisplay[i] = IMAQ_RGB_RED;}
					if (imageArrayDisplay[i].R == 2){imageArrayDisplay[i] = IMAQ_RGB_BLUE;} 
					if (imageArrayDisplay[i].R == 3){imageArrayDisplay[i] = IMAQ_RGB_PINK;}  
					if (imageArrayDisplay[i].R == 4){imageArrayDisplay[i] = IMAQ_RGB_GREEN;} 
					if (imageArrayDisplay[i].R == 5){imageArrayDisplay[i] = IMAQ_RGB_YELLOW;} 
				}
					
				imaqArrayToImage (myImage1, imageArrayDisplay, cols, rows);
				imaqDisplayImage (myImage1, 0, TRUE);	
				// #####
				
				
				// Save the coloured image
				imaqWriteBMPFile(myImage1, "C:\\IMAGEM.bmp", FALSE, NULL);
				

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

int CVICALLBACK Segmentation4 (int panel, int control, int event,
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

int CVICALLBACK Segmentation8 (int panel, int control, int event,
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
