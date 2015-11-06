#include "functions.h"
#include "./lib/heavy.h"
#include <node.h>
#include <nan.h>
#include <math.h>

using namespace node;
using namespace v8;
NAN_METHOD(anArray) {
        // get calback argument
        unsigned int height = info[0]->Uint32Value();
        unsigned int width = info[1]->Uint32Value();
        double xmin = info[2]->NumberValue();
        double xmax = info[3]->NumberValue();
        double ymin = info[4]->NumberValue();
        double ymax = info[5]->NumberValue();
        unsigned int iterations = info[6]->Uint32Value();

        v8::Local<v8::Function> callbackHandle = info[7].As<v8::Function>();

        v8::Local<v8::Array> arr = getMandelbrotPixels(height, width, xmin, xmax, ymin, ymax, iterations);
        // cast pixel array to return into callback
        Handle<Value> picture = Handle<Value>::Cast(arr);
        Local<Value> argv[1] = { picture };
        Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, 1, argv);
        info.GetReturnValue().SetUndefined();
}
