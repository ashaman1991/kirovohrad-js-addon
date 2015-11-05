'use strict';
var fs = require('fs'),
  PNG = require('pngjs')
  .PNG;

function generatePng(pixels, height, width) {
  height = height || 100;
  width = width || 100;

  var png = new PNG({
    filterType: 4,
    width: width,
    height: height,
  });

  png.data = pixels;
  png.pack()
    .pipe(fs.createWriteStream('out.png'));
}

module.exports = {
  generatePng: generatePng
};
