//secret.h


//a function for image_mean
int image_mean( unsigned char  * image, int width, int height)
{
  int average = 0;
  int pixel;
  
    for( int y = 0; y < height; y++)
      {
	for(int x = 0; x < width ; x++)
	  {
            pixel = image[x + y * width] ; //get the pixel value
	    average = pixel + average;
	  }
      }
    
    average = average/(width*height);
    return average;
}

//--------------------------------------------------------------------------
int put_in_txt( unsigned char  * image, int sp, int average)
{

  while( abs(image[sp] - average) > 20)
    {
      sp += 30;
    }
  image[sp]=average;

  return sp;

}

//--------------------------------------------------------------------------
int GetIndex(char * txt, char xxxx, int n)
{
  int index = 0;



  for(int i = 0; i<n; i++)
    {
      if(txt[i] == xxxx)
	index = i;

    }

  //  cout << "Input is " << xxxx <<" index = " << index+1 << endl;

  return index+1;
}

char GetChar(char * txt, int index)
{
  char out = txt[index];

  //  cout << "output is " << out <<" index = " << index << endl;

  return out;


}
