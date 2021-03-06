
#include "heavy.h"

using v8::Function;
using v8::Local;
using v8::Number;
using v8::Value;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;

int iteration(double cx, double cy, int maxIter) {
  double x  = 0.0;
  double y  = 0.0;
  double xx = 0;
  double yy = 0;
  double xy = 0;

  int i = maxIter;

  while (i-- && xx + yy <= 4) {
    xy = x * y;
    xx = x * x;
    yy = y * y;
    x  = xx - yy + cx;
    y  = xy + xy + cy;
  }
  return maxIter - i;
}

unsigned char* getMandelbrotPixels(unsigned int height,
                                   unsigned int width,
                                   double       xmin,
                                   double       xmax,
                                   double       ymin,
                                   double       ymax,
                                   unsigned int iterations) {
  unsigned char *pix = new unsigned char[(height * width) << 2];

  for (unsigned int ix = 0; ix < width; ++ix) {
    for (unsigned int iy = 0; iy < height; ++iy) {
      double x      = xmin + (xmax - xmin) * ix / (width - 1);
      double y      = ymin + (ymax - ymin) * iy / (height - 1);
      int    offset = 4 * (width * iy + ix);
      double i      = iteration(x, y, iterations);

      if (i  ==  iterations) {
        pix[offset]     = 0;
        pix[offset + 1] = 0;
        pix[offset + 2] = 0;
      } else {
        double c = 3 * log(i) / log(iterations - 1.0);

        if (c < 1) {
          pix[offset]     = (unsigned char)(255 * c);
          pix[offset + 1] = 0;
          pix[offset + 2] = 0;
        } else
        if ((c < 2) && (c > 1)) {
          pix[offset]     = 255;
          pix[offset + 1] = (unsigned char)(255 * (c - 1));
          pix[offset + 2] = 0;
        } else {
          pix[offset]     = 255;
          pix[offset + 1] = 255;
          pix[offset + 2] = (unsigned char)(255 * (c - 2));
        }
      }
      pix[offset + 3] = 255;
    }
  }
  return pix;
}

v8::Local<v8::Array>copyArray(unsigned char *arr, unsigned long int length) {
  v8::Local<v8::Array> copy = Nan::New<v8::Array>(length);

  for (unsigned long int i = 0; i < length; i++) {
    Nan::Set(copy, i, Nan::New(arr[i]));
  }

  return copy;
}
