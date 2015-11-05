#include "functions.h"
#include "./lib/heavy.h"

NAN_METHOD(nothing) {}

NAN_METHOD(anArray) {
        v8::Local<v8::Array> arr = generatePng();
        info.GetReturnValue().Set(arr);
}

NAN_METHOD(callback) {
        v8::Local<v8::Function> callbackHandle = info[0].As<v8::Function>();
        Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callbackHandle, 0, 0);
}
