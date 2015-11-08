#include "functions.h"

using v8::FunctionTemplate;

// NativeExtension.cc represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("mandelbrotSync").ToLocalChecked(),
           Nan::GetFunction(Nan::New<FunctionTemplate>(
                              mandelbrotSync)).ToLocalChecked());
  Nan::Set(target, Nan::New("mandelbrotAsync").ToLocalChecked(),
           Nan::GetFunction(Nan::New<FunctionTemplate>(
                              CalculateAsync)).ToLocalChecked());
}

NODE_MODULE(NativeExtension, InitAll)
