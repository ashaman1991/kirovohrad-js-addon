'use strict';
let addon = require('../index');
let plain = require('./plain');
let util = require('./util');

let height = 900;
let width = 900;
let R = 1.7E-4;
let Cx = -1.25066;
let Cy = 0.02012;
let xmin = Cx - R;
let xmax = Cx + R;
let ymin = Cy - R;
let ymax = Cy + R;
let iterations = 20000;

let pic = plain.getMandelbrotPixels(height, width, xmin, xmax, ymin, ymax, iterations);
util.generatePng(pic, height, width, 'js.png');
//
addon.mandelbrotSync(height, width, xmin, xmax, ymin, ymax, iterations, function (val) {
  util.generatePng(val, height, width, 'native.png');
});
addon.mandelbrotAsync(height, width, xmin, xmax, ymin, ymax, iterations, "fname.png", function (val) {});
