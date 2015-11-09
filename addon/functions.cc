#include "functions.h"
#include "./lib/heavy.h"
#include <nan.h>

using namespace node;
using namespace v8;
NAN_METHOD(mandelbrotSync) {
  // get calback argument
  unsigned int height     = info[0]->Uint32Value();
  unsigned int width      = info[1]->Uint32Value();
  double xmin             = info[2]->NumberValue();
  double xmax             = info[3]->NumberValue();
  double ymin             = info[4]->NumberValue();
  double ymax             = info[5]->NumberValue();
  unsigned int iterations = info[6]->Uint32Value();

  v8::Local<v8::Function> callbackHandle = info[7].As<v8::Function>();

  unsigned char *arr = getMandelbrotPixels(height,
                                           width,
                                           xmin,
                                           xmax,
                                           ymin,
                                           ymax,
                                           iterations);

  // cast pixel array to return into callback
  v8::Local<v8::Array> pix = copyArray(arr, (height * width) << 2);
  Handle<Value> picture    = Handle<Value>::Cast(pix);
  Local<Value>  argv[1]    = { picture };
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, 1, argv);
  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(CalculateAsync)
{
  unsigned int height     = info[0]->Uint32Value();
  unsigned int width      = info[1]->Uint32Value();
  double xmin             = info[2]->NumberValue();
  double xmax             = info[3]->NumberValue();
  double ymin             = info[4]->NumberValue();
  double ymax             = info[5]->NumberValue();
  unsigned int iterations = info[6]->Uint32Value();
  Callback    *callback   = new Callback(info[7].As<Function>());

  AsyncQueueWorker(new Mandelbrot(callback,
                                  height,
                                  width,
                                  xmin,
                                  xmax,
                                  ymin,
                                  ymax,
                                  iterations));
}
