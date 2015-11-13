'use strict';

let nativeExtension = require('../');
let assert = require('chai')
  .assert;
let fs = require('fs');
let util = require('../js/util');
let plain = require('../js/plain');

let height = 1200;
let width = 1200;
let R = 1.7E-4;
let Cx = -1.25066;
let Cy = 0.02012;
let xmin = Cx - R;
let xmax = Cx + R;
let ymin = Cy - R;
let ymax = Cy + R;
let iterations = 20000;

before(function (done) {
  done();
});

after(function (done) {
  fs.readdir('./', function (err, files) {
    let pics = files.filter(function (elem) {
      return elem.match('\.png');
    })

    pics.forEach(function (pic) {
      fs.unlink(pic);
    })
    done();
  });
});

describe('Native extension', function () {
  this.timeout(10000);
  it('should generate Png file synchronously::C++', function (done) {
    nativeExtension.mandelbrotSync(height, width, xmin, xmax, ymin, ymax, iterations, function (pixels) {
      assert.isArray(pixels);
      util.generatePng(pixels, height, width, 'testNativeSync.png', done);
    });
  });

  it('should generate Png file asynchronously::C++', function (done) {
    nativeExtension.mandelbrotAsync(height, width, xmin, xmax, ymin, ymax, iterations, 'testNativeAsync.png', function (res) {
      done();
    });
  });

  it('should generate Png file synchronously::JS', function (done) {
    util.generatePng(plain.getMandelbrotPixels(height, width, xmin, xmax, ymin, ymax, iterations), height, width, 'jsTest.png', done);
  });
});
