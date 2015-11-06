'use strict';
let http = require('http');
let addon = require('./addon/');
let plain = require('./plain');
let util = require('./util');

let height = 400;
let width = 600;
let xmin = -2;
let xmax = 1;
let ymin = -1;
let ymax = 1;
let iterations = 700;

// let pic = plain.getMandelbrotPixels(height, width, xmin, xmax, ymin, ymax, iterations);
addon.anArray(height, width, function (val) {
  // console.log(val);
  util.generatePng(val, height, width);
});
// console.log(pic);
// util.generatePng(pic, height, width);
// console.log(nativePic.slice(0, 100));
// util.generatePng(nativePic, height, width);
