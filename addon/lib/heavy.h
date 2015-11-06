#include <stdio.h>

int iteration(double cx, double cy, int maxIter) {
        double x = 0.0;
        double y = 0.0;
        double xx = 0;
        double yy = 0;
        double xy = 0;

        int i = maxIter;
        while (i-- && xx + yy <= 4) {
                xy = x * y;
                xx = x * x;
                yy = y * y;
                x = xx - yy + cx;
                y = xy + xy + cy;
        }
        return maxIter - i;
}

v8::Local<v8::Array> getMandelbrotPixels(unsigned int height,unsigned int width, double xmin,double xmax, double ymin, double ymax, unsigned int iterations) {
        v8::Local<v8::Array> pix = Nan::New<v8::Array>((height * width) << 2);
        for (unsigned int ix = 0; ix < width; ++ix) {
                for (unsigned int iy = 0; iy < height; ++iy) {
                        double x = xmin + (xmax - xmin) * ix / (width - 1);
                        double y = ymin + (ymax - ymin) * iy / (height - 1);
                        int offset = 4 * (width * iy + ix);
                        double i = iteration(x, y, iterations);

                        if ( i  ==  iterations) {
                                Nan::Set(pix, offset + 0, Nan::New(0));
                                Nan::Set(pix, offset + 1, Nan::New(0));
                                Nan::Set(pix, offset + 2, Nan::New(0));
                        } else {
                                double c = 3 * log(i) / log(iterations - 1.0);
                                if(c < 1) {
                                        Nan::Set(pix, offset + 0, Nan::New((unsigned char)(255 * c)));
                                        Nan::Set(pix, offset + 1, Nan::New(0));
                                        Nan::Set(pix, offset + 2, Nan::New(0));
                                } else
                                if(c < 2 && c > 1) {
                                        Nan::Set(pix, offset + 0, Nan::New(255));
                                        Nan::Set(pix, offset + 1, Nan::New((unsigned char)(255 * (c - 1))));
                                        Nan::Set(pix, offset + 2, Nan::New(0));
                                } else {
                                        Nan::Set(pix, offset + 0, Nan::New(255));
                                        Nan::Set(pix, offset + 1, Nan::New(255));
                                        Nan::Set(pix, offset + 2, Nan::New((unsigned char)(255 * (c - 2))));
                                }

                        }
                        Nan::Set(pix, offset + 3, Nan::New(255));
                }
        }
        return pix;
}


v8::Local<v8::Array> generatePng(unsigned int height,unsigned int width)
{
        /* screen ( integer) coordinate */
        int iX,iY;
        const int iXmax = width;
        const int iYmax = height;
        /* world ( double) coordinate = parameter plane*/
        double Cx,Cy;
        const double CxMin=-2.0;
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

        v8::Local<v8::Array> arr = Nan::New<v8::Array>(height * width * 4);

        for(iX=0; iX<iXmax; iX++)
        {
                for(iY=0; iY<iYmax; iY++)
                {
                        Cy= CyMin + (CyMax - CyMin) * iY / (iYmax);
                        Cx= CxMin + (CxMax - CxMin) * iX / (iXmax);
                        /* initial value of orbit = critical point Z= 0 */
                        Zx=0.0;
                        Zy=0.0;
                        Zx2=Zx*Zx;
                        Zy2=Zy*Zy;
                        /* */
                        for (Iteration=0; Iteration<IterationMax && ((Zx2+Zy2)<ER2); Iteration++)
                        {
                                Zy=2*Zx*Zy + Cy;
                                Zx=Zx2-Zy2 + Cx;
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

                        int offset = (iXmax * iY + iX) * 4;
                        Nan::Set(arr, offset + 0, Nan::New(pixel[0]));
                        Nan::Set(arr, offset + 1, Nan::New(0));
                        Nan::Set(arr, offset + 2, Nan::New(0));
                        Nan::Set(arr, offset + 3, Nan::New(255));
                }
        }
        return arr;
}
