#ifndef HEAVY_H
#define HEAVY_H

#include <nan.h>
#include <node.h>
#include <math.h>

using v8::Function;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;

using namespace node;
using namespace v8;
int iteration(double cx, double cy, int maxIter);

unsigned char* getMandelbrotPixels(unsigned int height,unsigned int width, double xmin,double xmax, double ymin, double ymax, unsigned int iterations);
v8::Local<v8::Array> copyArray(unsigned char *arr, unsigned long int length);

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

public:

Mandelbrot(Callback *callback,
           unsigned int height,
           unsigned int width,
           double xmin,
           double xmax,
           double ymin,
           double ymax,
           unsigned int iterations
           )
        : AsyncWorker(callback),
        height(height),
        width(width),
        xmin(xmin),
        xmax(xmax),
        ymin(ymin),
        ymax(ymax),
        iterations(iterations) {
}

~Mandelbrot() {
  delete pixels;
}

void Execute();

// Executed when the async work is complete
// this function will be run inside the main event loop
// so it is safe to use V8 again
void HandleOKCallback();
};

#endif
