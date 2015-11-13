#ifndef HEAVY_H
#define HEAVY_H

#include <nan.h>
#include <node.h>
#include <math.h>
#include <stdio.h>

int iteration(double cx, double cy, int maxIter);

unsigned char* getMandelbrotPixels(unsigned int height,unsigned int width, double xmin,double xmax, double ymin, double ymax, unsigned int iterations);
v8::Local<v8::Array> copyArray(unsigned char *arr, unsigned long int length);

#endif
