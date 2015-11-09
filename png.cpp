#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <png.h>

// Creates a test image for saving. Creates a Mandelbrot Set fractal of size
// width x height
png_bytep* createMandelbrotImage(int width,
                                 int height);

// This function actually writes out the PNG image file. The string 'title' is
// also written into the image file
int writeImage(char       *filename,
               int         width,
               int         height,
               png_bytep  *buffer,
               const char *title);


int main(int argc, char *argv[])
{
  // Make sure that the output filename argument has been provided
  if (argc != 2) {
    fprintf(stderr, "Please specify output file\n");
    return 1;
  }

  // Specify an output image size
  int width  = 100;
  int height = 300;

  // Create a test image - in this case a Mandelbrot Set fractal
  // The output is a 1D array of floats, length: width * height
  printf("Creating Image\n");
  png_bytep *buffer = createMandelbrotImage(width,
                                            height);

  if (buffer == NULL) {
    return 1;
  }

  const char *title = "This is my test image";
  int result        = writeImage(argv[1], width, height, buffer, title);

  // Free up the memorty used to store the image
  // free(buffer);

  return result;
}

int writeImage(char       *filename,
               int         width,
               int         height,
               png_bytep  *buffer,
               const char *title)
{
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
               8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  png_write_image(png_ptr, buffer);

  // End write
  png_write_end(png_ptr, NULL);

  return code;
}

png_bytep* createMandelbrotImage(int width,
                                 int height)
{
  png_bytep *buffer = (png_bytep *)malloc(height);

  if (buffer == NULL) {
    fprintf(stderr, "Could not create image buffer\n");
    return NULL;
  }

  for (int i = 0; i < height; i++) {
    png_bytep row = (png_bytep)malloc(width);

    for (int y = 0; y < width; y++) {
      row[y] = 0xff;

      // row[y + 1] = 0;
      // row[y + 2] = 0;
    }
    buffer[i] = row;
  }
  return buffer;
}
