#include <userint.h>
#include "Display.h"

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
											3 - Calculate
									*/
{
	char pathname[MAX_PATHNAME_LEN];
	unsigned char *imageArray; 
	int rows, cols, i, k;
	unsigned int histo[256] = { 0 }; // Inicializate histogram values with 0
   	char output[50];
	
	float 	zm,fmx,fmy,smx,smy,smxy,cx,cy;
	float 	theta,smxc,smyc,smxcyc,smp1,smp2,shape,temp,width_b,n_theta,n_theta90;
	int 	j,c;

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
			
		case 3: // Calculate
			
			// Zeroth Moment - Area for a Binary Image
			zm		= 0.0; // (A) 
			
			// First Order Moments
			fmx		= 0.0; // (Mx)
			fmy		= 0.0; // (My)
			
			// Second Order Moments
			smx		= 0.0; // (Nx)
			smy		= 0.0; // (Ny)
			smxy	= 0.0; // (Nxy)

			c = 0; // The counter c is used to access the one dimensional array elements
							
			for (i=0; i<(rows); i++)
			{
				for (j=0; j<(cols); j++)
				{
					temp=imageArray[c];
					if (temp == 0.0)
					{
						zm		= zm + 1;
						fmx		= fmx + i;
						fmy		= fmy + j;
						smx		= smx + (i*i);
						smy		= smy + (j*j);
						smxy	= smxy + (i*j);
					}
					c++;
				}
			}

			//Calculate position of centroid
			cx = fmy/zm;
			cy = fmx/zm;
		
			//Express second order moments about centroid
			smxc = smx - (zm*(cy*cy));
			smyc = smy - (zm*(cx*cx));
			smxcyc = smxy - (zm*(cy*cx));

			//Calculate theta and shape
			if(smxc==smyc)theta=0.0;
			else theta=(atan(2.0*smxcyc/(smxc-smyc)))/2.0;
			
			n_theta = ((smxc + smyc)/2)+(((smxc - smyc)/2)*cos(2*theta))-(smxcyc*sin(2*theta));
			n_theta90 = ((smxc + smyc)/2)+(((smxc - smyc)/2)*cos(2*(theta+1.57079635)))-(smxcyc*sin(2*(theta+1.57079635)));
			
			smp1=((smxc+smyc)/2.0)+pow(pow((smxc-smyc)/2.0,2.0)+(smxcyc*smxcyc),0.5);
			smp2=((smxc+smyc)/2.0)-pow(pow((smxc-smyc)/2.0,2.0)+(smxcyc*smxcyc),0.5);
			
			if(smp2==0.0)shape=0.0;
			else shape=smp1/smp2;
		
			// Finally Display the calculated values
			
			//printf("Area of blob = %f\n",zm);
			snprintf(output,50,"%f",zm);
			SetCtrlVal(panelHandle, PANEL_strAREA, output);
			
			//printf("Centroid of blob area (x) = %f\n",cx);
			snprintf(output,50,"%f",cx);
			SetCtrlVal(panelHandle, PANEL_strCENTROIDX, output);
			
			//printf("Centroid of blob area (y) = %f\n",cy);
			snprintf(output,50,"%f",cy);
			SetCtrlVal(panelHandle, PANEL_strCENTROIDY, output);
			
			//printf("Angle of 1st principal axis(degs) = %f\n",(360.0*theta/(2.0*3.1415927 )));
			snprintf(output,50,"%f",(180*theta/3.1415927));
			SetCtrlVal(panelHandle, PANEL_strANGLE, output);

			//printf("N Theta = %f\n",n_theta);
			snprintf(output,50,"%f",n_theta);
			SetCtrlVal(panelHandle, PANEL_strANGLE_N, output);

			//printf("N Theta + 90 = %f\n",n_theta);
			snprintf(output,50,"%f",n_theta90);
			SetCtrlVal(panelHandle, PANEL_strANGLE_N90, output);
			
			// Check whether the angle is related to the major or the minor principal axis 
			if (n_theta == n_theta90) 
				SetCtrlVal(panelHandle, PANEL_TEXTMSG_AXIS, "- - -");
			else
			if (n_theta > n_theta90)
				SetCtrlVal(panelHandle, PANEL_TEXTMSG_AXIS, "with major principal axis");
			else
				SetCtrlVal(panelHandle, PANEL_TEXTMSG_AXIS, "with minor principal axis");
						
			//printf("Shape factor (binary image) = %f\n",shape);
			snprintf(output,50,"%f",shape);
			SetCtrlVal(panelHandle, PANEL_strSF, output);
			
			// Calculate Blob Width b
			width_b = sqrt(zm/sqrt(shape));
			
			snprintf(output,50,"%f",width_b);
			SetCtrlVal(panelHandle, PANEL_strBLOBWIDTHb, output);
			
			// Calculate Blob Width d
			snprintf(output,50,"%f", width_b*sqrt(shape));
			SetCtrlVal(panelHandle, PANEL_strBLOBWIDTHd, output);
			

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
			SetCtrlVal(panelHandle, PANEL_strAREA, "");
			SetCtrlVal(panelHandle, PANEL_strCENTROIDX, "");
			SetCtrlVal(panelHandle, PANEL_strCENTROIDY, "");
			SetCtrlVal(panelHandle, PANEL_strANGLE, "");
			SetCtrlVal(panelHandle, PANEL_strANGLE_N, "");
			SetCtrlVal(panelHandle, PANEL_strANGLE_N90, "");
			SetCtrlVal(panelHandle, PANEL_strSF, "");
			SetCtrlVal(panelHandle, PANEL_strBLOBWIDTHb, "");
			SetCtrlVal(panelHandle, PANEL_strBLOBWIDTHd, "");
			SetCtrlVal(panelHandle, PANEL_TEXTMSG_AXIS, "- - -");
			
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

int CVICALLBACK Calculate	(int panel, int control, int event,
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

