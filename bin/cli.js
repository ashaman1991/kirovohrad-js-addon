#!/usr/bin/env node

'use strict';
let addon = require('../index');
let plain = require('../js/plain');
let util = require('../js/util');
let program = require('commander');

program
  .version("1.0.0")
  .option('-n, --native', 'Use native async code (or use JS version by default)')
  .option('-o, --out [path]', 'Custom save path')
  .option('-i --iterations [iterations]', 'Number of iterations', parseInt)
  .option('-c --count [count]', 'How much pictures do you want?', parseInt)
  .parse(process.argv);

let count = program.count || 1;
let nativeMode = program.native ? true : false;
let path = program.out || '';

let height = 1000;
let width = 1000;
let R = 1.7E-4;
let Cx = -1.25066;
let Cy = 0.02012;
let xmin = Cx - R;
let xmax = Cx + R;
let ymin = Cy - R;
let ymax = Cy + R;
let iterations = program.iterations || 20000;

for (let i = 0; i < count; i++) {
  if (nativeMode) {
    addon.mandelbrotAsync(height, width, xmin, xmax, ymin, ymax, iterations, path + 'native' + i + '.png', function (val) {});
  } else {
    util.generatePng(plain.getMandelbrotPixels(height, width, xmin, xmax, ymin, ymax, iterations), height, width, path + 'js' + i + '.png');
  }
}
