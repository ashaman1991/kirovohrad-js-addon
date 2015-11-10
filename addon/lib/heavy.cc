
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

int writeImage(const char    *filename,
               int            width,
               int            height,
               unsigned char *buffer) {
  int   code           = 0;
  FILE *fp             = NULL;
  png_structp png_ptr  = NULL;
  png_infop   info_ptr = NULL;

  fp = fopen(filename, "wb");


  // Initialize write structure
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  // Initialize info structure
  info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, fp);

  // Write header (8 bit colour depth)
  png_set_IHDR(png_ptr, info_ptr, width, height,
               8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_bytep *row_pointers = (png_bytep *)png_malloc(png_ptr,
                                                    height *
                                                    sizeof(png_bytep));

  for (int i = 0; i < height; i++) {
    row_pointers[i] = &buffer[i * width * 4];
  }

  png_set_rows(png_ptr, info_ptr, row_pointers);

  png_write_png(png_ptr, info_ptr, 0x00, NULL);

  // End write
  png_write_end(png_ptr, NULL);

  return code;

  return 0;
}

void Mandelbrot::Execute() {
  pixels = getMandelbrotPixels(height,
                               width,
                               xmin,
                               xmax,
                               ymin,
                               ymax,
                               iterations);

  printf("%s\n", fname);
  writeImage(fname, width, height, pixels);
}

void Mandelbrot::HandleOKCallback() {
  v8::Local<v8::Array> pix = copyArray(pixels, (height * width) << 2);
  Handle<Value> data       = Handle<Value>::Cast(pix);
  Local<Value>  argv[1]    = {
    data
  };

  callback->Call(1, argv);
}
