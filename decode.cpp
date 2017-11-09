//image_main.cpp

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "secret.h"

using namespace cv;
using namespace std;


//-------------------------------------------------------------------------
int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_input InputToLoadAndDisplay" << endl;
     return -1;
    }

    Mat input;
    input = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! input.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the input" << std::endl ;
        return -1;
    }

    int width  =  input.cols;
    int height =  input.rows;

    cout << "Input size is "<< width << "x" << height << endl;
    //namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    // imshow( "Display window", input );                   // Show our input inside it.


    //conver the input to Black and white (gray input): -----------------------------------------------
    // Create a new matrix to hold the gray input
    Mat gray;
 
    // convert RGB input to gray
    cvtColor(input, gray, CV_RGB2GRAY);

    //show the input
    imshow( "Gray Input", gray );
    unsigned char  * image = gray.data;

    //-------------------------------------------------------------------------------------------
   
     //Decode Steps
    int  pixel;
    int average = 0;
    int sp;// = width*250;//starting pint of first avg value
    char text[30] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
		     'o','p','q','r','s','t','u','v','w','x','y','z',' ','$'};

     input = imread("secret_image.png",CV_LOAD_IMAGE_GRAYSCALE);
     image =  input.data;

     // Step 1: get the averga eof the image
     average = image_mean(image, width, height);

     //Step 2: get the first staring point

     //get the first starting point , look for the first average value
     for(int i = 0; i < width*height; i++)
       {
  
	 pixel = image[i];
	 if(pixel == average)
	   {
	     sp = i;
	     break;
	   }
       }

     printf("secret message is: ");
     //Step 3: got hrough the rest of the image looking for pixels that equal the average 
     // and then the distance between these pixels corisponds to differnt letters in the alphabet
     for(int i = sp+1; i < width*height; i++)
       {
  
	 pixel = image[i];
	 if(pixel == average)
	   {
	     int distance = (i - sp)%30;
	     sp = i;
	     char c =  GetChar(text, distance-1);
	     printf("%c", c);
	   }
       }

     printf("\n");
    //show the input

    waitKey(0);                                          // Wait for a keystroke in the window

    return 0;
}
