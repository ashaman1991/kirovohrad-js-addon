
/*
   c program:
   --------------------------------
   1. draws Mandelbrot set for Fc(z)=z*z +c
   using Mandelbrot algorithm ( boolean escape time )
   -------------------------------
   2. technique of creating ppm file is  based on the code of Claudio Rocchini
   http://en.wikipedia.org/wiki/Image:pixel_complex_plot.jpg
   create 24 bit pixel graphic file ,  portable pixmap file = PPM
   see http://en.wikipedia.org/wiki/Portable_pixmap
   to see the file use external application ( graphic viewer)
 */
 #include <stdio.h>
v8::Local<v8::Array> generatePng()
{
        /* screen ( integer) coordinate */
        int iX,iY;
        const int iXmax = 255;
        const int iYmax = 255;
        /* world ( double) coordinate = parameter plane*/
        double Cx,Cy;
        const double CxMin=-1.0;
        const double CxMax=1.0;
        const double CyMin=-1.0;
        const double CyMax=1.0;

        static unsigned char pixel[4];
        /* Z=Zx+Zy*i  ;   Z0 = 0 */
        double Zx, Zy;
        double Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
        /*  */
        int Iteration;
        const int IterationMax=500;
        /* bail-out value , radius of circle ;  */
        double ER2= 4;

        v8::Local<v8::Array> arr = Nan::New<v8::Array>(iXmax * iYmax * 4);

        for(iX=0; iX<iXmax; iX++)
        {
                for(iY=0; iY<iYmax; iY++)
                {
                        Cy= CyMin + (CyMax - CyMin) * iY / (iYmax - 1);
                        Cx= CxMin + (CxMax - CxMin) * iX / (iXmax - 1);
                        /* initial value of orbit = critical point Z= 0 */
                        Zx=0.0;
                        Zy=0.0;
                        Zx2=Zx*Zx;
                        Zy2=Zy*Zy;
                        /* */
                        for (Iteration=0; Iteration<IterationMax && ((Zx2+Zy2)<ER2); Iteration++)
                        {
                                Zy=2*Zx*Zy + Cy;
                                Zx=Zx2-Zy2 +Cx;
                                Zx2=Zx*Zx;
                                Zy2=Zy*Zy;
                        };

                        if (Iteration==IterationMax)
                        { /*  interior of Mandelbrot set = black */
                                pixel[0]=0;
                                pixel[1]=0;
                                pixel[2]=0;
                        }
                        else
                        { /* exterior of Mandelbrot set = white */
                                pixel[0]=255; /* Red*/
                                pixel[1]=255; /* Green */
                                pixel[2]=255; /* Blue */
                        };

                        int offset = (iYmax * iY + iX) * 4;
                        Nan::Set(arr, offset + 0, Nan::New(pixel[0]));
                        Nan::Set(arr, offset + 1, Nan::New(0));
                        Nan::Set(arr, offset + 2, Nan::New(0));
                        Nan::Set(arr, offset + 3, Nan::New(iX));
                }
        }
        return arr;
}
