#include "mandelbrot.h"

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

  writeImage(fname, width, height, pixels);
}

void Mandelbrot::HandleOKCallback() {
  callback->Call(0, 0);
}
