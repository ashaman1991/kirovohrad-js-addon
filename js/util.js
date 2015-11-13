'use strict';
let fs = require('fs'),
  PNG = require('pngjs')
  .PNG;

function generatePng(pixels, height, width, fName) {
  fName = fName || 'out.png';
  height = height || 100;
  width = width || 100;

  let png = new PNG({
    filterType: 4,
    width: width,
    height: height,
  });

  // console.log(fName);

  png.data = pixels;
  let fstream = fs.createWriteStream(fName);
  fstream.on('finish', function () {
    console.log(fName);
  });
  png.pack()
    .pipe(fstream);
}

module.exports = {
  generatePng: generatePng
};
