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
    //   namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    //imshow( "Display window", input );                   // Show our input inside it.


    //conver the input to Black and white (gray input): -----------------------------------------------
    // Create a new matrix to hold the gray input
    Mat gray;
 
    // convert RGB input to gray
    cvtColor(input, gray, CV_RGB2GRAY);

    //show the input
    imshow( "Gray Input", gray );

    //-------------------------------------------------------------------------------------------
    //******************************************************************************************
    //******************************************************************************************
    //******************************************************************************************
    //IMAGE MODIFIED
    unsigned char  * image = gray.data;
    int  pixel;
    int average = 0;
    int sp;// = width*250;//starting pint of first avg value
    int first=1;

    //Step 1: find the average pixel value for the image
    average = image_mean(image, width, height);

    cout << "function average is " << average << endl;


    //Step 2: go through the image and set any pixels that equal the average to 1 above
     for( int y = 0; y < height; y++)
      {
	for(int x = 0; x < width ; x++)
	  {
            pixel = image[x + y * width] ; //get the pixel value
	    if(pixel == average)
	      {
		pixel++;
		//Step 3: find the first average pixel to start the message.
		if( first == 1) 
		  {
		    first = 0;
		    sp = x + y*width;
		  }
	      }
	    image[x + y * width] = pixel ; 
	   
	  }
      }


     //Step 4: make an alphabet
     average = image_mean(image, width, height);
     cout << "function average after modification is " << average << endl;
     cout << "starting point is = " << sp << endl;

     char text[30] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
		      'o','p','q','r','s','t','u','v','w','x','y','z',' ','$'};

     //Step 5: make a secret massage     
     //     char  msg[64] = "hello my name is aidan coopman";
     char  msg[64] = "yz";


     int msg_len =  strlen(msg);
     cout << "Msg length =  " << msg_len << endl;

     //Step 6: change the sp location to start the message
     image[sp]=average; //tells where to start and not a txt yet     

     //Step 7: Go through each charactor of the message and get its index from the text array
     //Take this index and add it to the previous sp change the pixel value in the image
     //to the avarage pixel value

     for( int i = 0; i<msg_len; i++)
     {

	  sp += GetIndex(text,msg[i],30);
	  sp = put_in_txt(image,sp, average); 
     }

     //save the image out
     imwrite("secret_image.png", gray);
     imshow( "Secret Message Image", gray );
     waitKey(0);

    
    return 0;
}
