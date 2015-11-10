#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <nan.h>
#include <node.h>
#include <stdio.h>
#include <png.h>
#include "heavy.h"
using v8::Function;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;

class Mandelbrot : public AsyncWorker {
private:

unsigned char* pixels;
unsigned int height;
unsigned int width;
double xmin;
double xmax;
double ymin;
double ymax;
unsigned int iterations;
const char* fname;

public:

Mandelbrot(Callback *callback,
           unsigned int height,
           unsigned int width,
           double xmin,
           double xmax,
           double ymin,
           double ymax,
           unsigned int iterations,
           const char* fname
           )
        : AsyncWorker(callback),
        height(height),
        width(width),
        xmin(xmin),
        xmax(xmax),
        ymin(ymin),
        ymax(ymax),
        iterations(iterations),
        fname(fname) {
}

~Mandelbrot() {
  delete pixels;
}

void Execute();

void HandleOKCallback();
};

#endif
