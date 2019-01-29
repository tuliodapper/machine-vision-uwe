#include <userint.h>
#include "Display.h"

# include <userint.h>
# include <utility.h>
# include <nivision.h>
# include "Display.h"  

static int panelHandle;
Image* myImage1 = NULL; 
int ArrayRead[300][300];   // 2D array large enough for image read in  
int ArrayWrite[300][300]; // 2D array large enough for image write out	



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

int conv (int i, int j, int mask[3][3])
{
	int result,m,n;
	result = 0;
	for(m=-1; m<=1; m++)
	{
		for(n=-1; n<=1; n++)
		{
			result = result + mask[m+1][n+1]*ArrayRead[i+m][j+n];
		}
	}
	return result;
}

void ProcessImage(int inOperation) 	/* 	"inOperation" Options:
											1 - Display Image
											2 - Horizontal
								 	 		3 - Vertical
											4 - 1st Diagonal
											5 - 2nd Diagonal
											6 - General Kirsch
											7 - General Laplacian
											8 - General Sobel
									*/
{
	char pathname[MAX_PATHNAME_LEN];
	unsigned char *imageArray;
	int rows, cols,i,j,k;
	int rmax,rmin;
	
	int mask_vertical[3][3] = {	{-1, 0, 1},
								{-1, 0, 1},
								{-1, 0, 1}};
								
	int mask_horizontal[3][3] = {	{1, 1, 1},
									{0, 0, 0},
									{-1, -1, -1}};
								
	int mask_diagonal1[3][3] = {	{0, 1, 1},
									{-1, 0, 1},
									{-1, -1, 0}};
									
	int mask_diagonal2[3][3] = {	{1, 1, 0},
									{1, 0, -1},
									{0, -1, -1}};
									
	int mask_laplacian[3][3] = {	{0, 1, 0},
									{1, -4, 1},
									{0, 1, 0}};
									
	int mask_sobel1[3][3] = {	{-1, 0, 1},
								{-2, 0, 2},
								{-1, 0, 1}};
								
	int mask_sobel2[3][3] = {	{-1, -2, -1},
								{0, 0, 0},
								{1, 2, 1}};
									
	float range,sx,sy;



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
			
		case 2: // Vertical
		case 3: // Horizontal
		case 4: // 1st Diagonal
		case 5: // 2nd Diagonal
		case 6: // General Kirsch
		case 7: // General Laplacian
		case 8: // General Sobel
			
			// ##### Convert 1D array to a 2D array #####
			k = 0;
			for(i=0; i<rows; i++) // look through all lines  
			{
				for(j=0; j<cols; j++) // look through all columns
				{
					ArrayRead[i][j]=imageArray[k];
					k = k+1;
				}
			}
			
			// Find range of resultant grey values - needed for rescaling later
			rmax = ArrayRead[0][0];
			rmin = ArrayRead[0][0];  
			
			for(i=1; i<(rows-1); i++) // (rows-1) to avoid pixel outside image
			{
				for(j=1; j<(cols-1); j++)
				{
					switch (inOperation)
					{
						case 2: k = conv(i,j, mask_vertical);
								break;
						case 3:	k = conv(i,j, mask_horizontal); 
								break;
						case 4:	k = conv(i,j, mask_diagonal1);          
								break;
						case 5: k = conv(i,j, mask_diagonal2);       
								break;
						case 6: k = conv(i,j, mask_vertical) + conv(i,j, mask_horizontal) + conv(i,j, mask_diagonal1) + conv(i,j, mask_diagonal2);       
								break;
						case 7: k = conv(i,j, mask_laplacian);
								break;
						case 8: sx= conv(i,j, mask_sobel1);  
							 	sy= conv(i,j, mask_sobel2);   
								k=sqrt(sx*sx+sy*sy);
								break;
					}
					ArrayWrite[i][j]=k;	
					if (rmax < k) rmax=k;
					if (rmin > k) rmin=k;
				}
			}
			range = (float)(rmax-rmin);	
			
			//Rescale resulting grey values to 0-255
			for(i=1; i<(rows-1); i++)
			{
				for(j=1; j<(cols-1); j++)
				{
					ArrayWrite[i][j]=(int)(((float)(ArrayWrite[i][j]-rmin)/range)*255.0); 
				}
			}

			
			// ##### Convert 2D array to a 1D array #####
			k = 0;
			for(i=0; i<rows; i++) // look through all lines     
			{
				for(j=0; j<cols; j++) // look through all columns
				{
					imageArray[k] = ArrayWrite[i][j];
					k = k+1;
				}
			}			 
			// #####
					
			imaqArrayToImage(myImage1,imageArray, cols, rows);
			imaqDisplayImage(myImage1,0,1);
			imaqWriteBMPFile(myImage1, "C:\\Result.bmp", FALSE, NULL);
			
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

int CVICALLBACK Vertical (int panel, int control, int event,
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


int CVICALLBACK Horizontal (int panel, int control, int event,
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

int CVICALLBACK Diagonal1 (int panel, int control, int event,
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

int CVICALLBACK Diagonal2 (int panel, int control, int event,
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

int CVICALLBACK KirschOperators (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(6);
			break;
	}
	return 0;
}

int CVICALLBACK GeneralLaplacian (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(7);
			break;
	}
	return 0;
}

int CVICALLBACK GeneralSobel (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ProcessImage(8);
			break;
	}
	return 0;
}
