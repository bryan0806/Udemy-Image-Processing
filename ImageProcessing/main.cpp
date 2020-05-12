#include <iostream>
#include "ImageProcessing.h"

using namespace std;

int main()
{
    Mask lpmask;
    unsigned char *tmp;
    int i;

    int imgWidth, imgHeight, imgBitDepth;
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgInBuffer[_512by512_IMG_SIZE];
    unsigned char imgOutBuffer[_512by512_IMG_SIZE];

    const char imgName[] ="images/girlface.bmp";
    const char newImgName[] ="images/girlface_conv.bmp";

    ImageProcessing *myImage  = new ImageProcessing(imgName,
                                                    newImgName,
                                                    &imgHeight,
                                                    &imgWidth,
                                                    &imgBitDepth,
                                                    &imgHeader[0],
                                                    &imgColorTable[0],
                                                    &imgInBuffer[0],
                                                    &imgOutBuffer[0]
                                                    );


     lpmask.Cols=5;
     lpmask.Rows=5;
     lpmask.Data= (unsigned char *)malloc(25);

     /* -1 -1 -1 -1 -1
        -1 -1 -1 -1 -1
        -1 -1 24 -1 -1
        -1 -1 -1 -1 -1
        -1 -1 -1 -1 -1*/

     tmp = lpmask.Data;
     for (i=0;i<25;i++)
     {
         *tmp =-1;
         //cout<< *tmp << " " <<endl;
         ++tmp;
     }

     tmp = lpmask.Data+13;
     *tmp=24;

     //check mask
     for(i=0;i<25;i++){
        cout << "i=" << i << "value=" << (signed int)*(lpmask.Data+i) << endl;
     }


     myImage->readImage();

     myImage->Convolve2D(imgHeight,imgWidth,&lpmask,imgInBuffer,imgOutBuffer);
     myImage->writeImage();

     cout<<"Success !"<<endl;
     cout<<"Image Height : "<<imgHeight<<endl;
     cout<<"Image Width  : "  <<imgWidth<<endl;

    return 0;
}
