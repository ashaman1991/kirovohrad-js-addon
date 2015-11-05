#include "functions.h"

using v8::FunctionTemplate;

// NativeExtension.cc represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("nothing").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(nothing)).ToLocalChecked());
  Nan::Set(target, Nan::New("anArray").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(anArray)).ToLocalChecked());
  Nan::Set(target, Nan::New("callback").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(callback)).ToLocalChecked());
}

NODE_MODULE(NativeExtension, InitAll)
