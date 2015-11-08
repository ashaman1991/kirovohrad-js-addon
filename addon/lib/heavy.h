#ifndef HEAVY_H
#define HEAVY_H

#include <nan.h>
#include <node.h>
#include <math.h>
#include <iostream>

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

using namespace node;
using namespace v8;
int iteration(double cx, double cy, int maxIter);

v8::Local<v8::Array> getMandelbrotPixels(unsigned int height,unsigned int width, double xmin,double xmax, double ymin, double ymax, unsigned int iterations);

class Mandelbrot : public AsyncWorker {
private:

v8::Local<v8::Array>* pixels;
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
}

void Execute();

// Executed when the async work is complete
// this function will be run inside the main event loop
// so it is safe to use V8 again
void HandleOKCallback() {
        // HandleScope scope;
        std::cout << ">>>>>>>>>>" << std::endl;
        v8::Local<v8::Array> pix = Nan::New<v8::Array>(10);
        pixels= &pix;
        Handle<Value> data = Handle<Value>::Cast(*pixels);
        Local<Value> argv[1] = {
                data
        };
        // Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, 1, argv);
        callback->Call(1, argv);
}
};

#endif
