"use strict";
module.exports = {
  getMandelbrotPixels: mandelbrot,
};

function mandelIter(cx, cy, maxIter) {
  let x = 0.0;
  let y = 0.0;
  let xx = 0;
  let yy = 0;
  let xy = 0;

  let i = maxIter;
  while (i-- && xx + yy <= 4) {
    xy = x * y;
    xx = x * x;
    yy = y * y;
    x = xx - yy + cx;
    y = xy + xy + cy;
  }
  return maxIter - i;
}

function mandelbrot(height, width, xmin, xmax, ymin, ymax, iterations) {
  let pix = [];

  for (let ix = 0; ix < width; ++ix) {
    for (let iy = 0; iy < height; ++iy) {
      let x = xmin + (xmax - xmin) * ix / (width - 1);
      let y = ymin + (ymax - ymin) * iy / (height - 1);
      let i = mandelIter(x, y, iterations);
      let offset = 4 * (width * iy + ix);

      if (i > iterations) {
        pix[offset] = 0;
        pix[offset + 1] = 0;
        pix[offset + 2] = 0;
      } else {
        let c = 3 * Math.log(i) / Math.log(iterations - 1.0);

        if (c < 1) {
          pix[offset] = Math.round(255 * c);
          pix[offset + 1] = 0;
          pix[offset + 2] = 0;
        } else if (c < 2) {
          pix[offset] = 255;
          pix[offset + 1] = Math.round(255 * (c - 1));
          pix[offset + 2] = 0;
        } else {
          pix[offset] = 255;
          pix[offset + 1] = 255;
          pix[offset + 2] = Math.round(255 * (c - 2));
        }
      }
      pix[offset + 3] = 255;
    }
  }

  return pix;
}
