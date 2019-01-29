#include <userint.h>
#include "Display.h"

# include <userint.h>
# include <utility.h>
# include <nivision.h>
# include "Display.h"  

static int panelHandle;
Image* myImage1 = NULL; 
int Array[100][100];   // 2D array



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
								 	 		2 - Erosion 4-Connected 
											3 - Erosion 8-Connected     
											4 - Boundary 8-Connected
									*/
{
	char pathname[MAX_PATHNAME_LEN];
	unsigned char *imageArray; 
	int rows, cols,i,j,c,k;
	unsigned int times, connected; 
	int matrix[8][2] = {{-1, 0},
						{ 0, 1},
						{ 1, 0},
						{ 0,-1},
						{-1, 1},
						{ 1, 1},
						{ 1,-1},
						{-1,-1}};


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
			
		case 2: // Erosion 4-Connected
		case 3: // Erosion 8-Connected
		case 4: // Boundary 8-Connected
			
				// ##### Convert 1D array to a 2D array #####
				c = 0;
				for(i=0; i<rows; i++) // look through all lines  
				{
					for(j=0; j<cols; j++) // look through all columns
					{
						Array[i][j]=imageArray[c];
						c = c+1;
					}
				}
				
				// #####
				
				if (inOperation == 4)
				{
					times = 1;					   
					SetCtrlVal(panelHandle, PANEL_strTIMES, times);
				} else
				// Get the number of times to execute the erosion
				GetCtrlVal(panelHandle, PANEL_strTIMES, &times);  
				
				if ((inOperation == 2) || (inOperation == 4))
					connected = 4;
				else
					connected = 8;
				
				// Number of erosions to be executed
				for(c=0; c<times; c++)
				{
					
					// ##### Identify black pixels that have white neighbours either 4- or 8-connected #####
					for(i=0; i<100; i++) // look through all lines
					{
						for(j=0; j<100; j++) // look through all columns
						{
							//identify blob (black pixels)
							if(Array[i][j] == 0)
								for (k= 0; k<connected; k++) // look through all positions relative to the main pixel
								{
									if (Array [i + matrix[k][0]] [j + matrix[k][1]] == 255) // if the neighbour pixel belongs to the backgroud, then change its grey-level to 2
										Array[i][j] = 2;
								}
						}
					}	
					// #####
					
					// ##### Identify marked pixels and remove them ##### 
					for(i=0; i<100; i++) // look through all lines
					{
						for(j=0; j<100; j++) //	 look through all columns 
						{
							if (inOperation == 4){ // inOperation: 2 -> Erosion, 4 -> 4-Connected, 3 -> 8-Connected, 4 -> Boundary 8-Connected
								if(Array[i][j] == 2) // if the pixel is marked, then change it to white
									Array[i][j] = 0;
								else
									Array[i][j] = 255;
							} else
							{
								if(Array[i][j] == 2) // if the pixel is marked, then change it to white
									Array[i][j] = 255;
							}
						}
					}
					// #####
	
				}

				// ##### Convert 2D array to a 1D array #####
				c = 0;
				for(i=0; i<rows; i++) // look through all lines     
				{
					for(j=0; j<cols; j++) // look through all columns
					{
						imageArray[c] = Array[i][j];
						c = c+1;
					}
				}			 
				// #####
					
				imaqArrayToImage(myImage1,imageArray, cols, rows);
				imaqDisplayImage(myImage1,0,1);
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

int CVICALLBACK Erosion4 (int panel, int control, int event,
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


int CVICALLBACK Erosion8 (int panel, int control, int event,
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

int CVICALLBACK Boundary4 (int panel, int control, int event,
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
