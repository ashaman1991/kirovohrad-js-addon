
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

v8::Local<v8::Array>getMandelbrotPixels(unsigned int height,
                                        unsigned int width,
                                        double       xmin,
                                        double       xmax,
                                        double       ymin,
                                        double       ymax,
                                        unsigned int iterations) {
  v8::Local<v8::Array> pix = Nan::New<v8::Array>((height * width) << 2);

  for (unsigned int ix = 0; ix < width; ++ix) {
    for (unsigned int iy = 0; iy < height; ++iy) {
      double x      = xmin + (xmax - xmin) * ix / (width - 1);
      double y      = ymin + (ymax - ymin) * iy / (height - 1);
      int    offset = 4 * (width * iy + ix);
      double i      = iteration(x, y, iterations);

      if (i  ==  iterations) {
        Nan::Set(pix, offset + 0, Nan::New(0));
        Nan::Set(pix, offset + 1, Nan::New(0));
        Nan::Set(pix, offset + 2, Nan::New(0));
      } else {
        double c = 3 * log(i) / log(iterations - 1.0);

        if (c < 1) {
          Nan::Set(pix, offset + 0, Nan::New((unsigned char)(255 * c)));
          Nan::Set(pix, offset + 1, Nan::New(0));
          Nan::Set(pix, offset + 2, Nan::New(0));
        } else
        if ((c < 2) && (c > 1)) {
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

void Mandelbrot::Execute() {
  // Nan::Set(pixels, 0, Nan::New(255));
  std::cout << "<<<<<<<<<" << std::endl;
  // v8::Local<v8::Array> pix = Nan::New<v8::Array>(10); //
  // getMandelbrotPixels(height,
  //                     width, xmin, xmax,
  //                     ymin, ymax,
  //                     iterations);

  // pixels = &pix;

  // pixels = Nan::New<v8::Array>(10);//
  std::cout << "<<<<<<<<<" << std::endl;
}
