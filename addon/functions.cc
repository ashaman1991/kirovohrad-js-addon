#include "functions.h"
#include "./lib/heavy.h"
#include <node.h>
#include <nan.h>
#include <math.h>

using namespace node;
using namespace v8;

NAN_METHOD(nothing) {
}

NAN_METHOD(anArray) {
        // get calback argument
        v8::Local<v8::Function> callbackHandle = info[2].As<v8::Function>();
        unsigned int height = info[0]->Uint32Value();
        unsigned int width = info[1]->Uint32Value();
        v8::Local<v8::Array> arr = getMandelbrotPixels(height, width, -2, 1, -1, 1, 700);
        // cast pixel array to return into callback
        Handle<Value> picture = Handle<Value>::Cast(arr);
        Local<Value> argv[1] = { picture };
        Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, 1, argv);
        info.GetReturnValue().SetUndefined();
}

NAN_METHOD(callback) {
        v8::Local<v8::Function> callbackHandle = info[0].As<v8::Function>();
        Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, 0, 0);
}
