#ifndef HEAVY_H
#define HEAVY_H

#include <nan.h>
#include <node.h>
#include <math.h>

int iteration(double cx, double cy, int maxIter);

v8::Local<v8::Array> getMandelbrotPixels(unsigned int height,unsigned int width, double xmin,double xmax, double ymin, double ymax, unsigned int iterations);
#endif
