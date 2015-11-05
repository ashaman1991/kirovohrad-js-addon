module.exports = {
  heavy: function (height, width) {
    console.log('This is heavy js!');
    return mandelbrot(height, width, -2, 1, -1, 1, 700);
  }
};

function mandelIter(cx, cy, maxIter) {
  var x = 0.0;
  var y = 0.0;
  var xx = 0;
  var yy = 0;
  var xy = 0;

  var i = maxIter;
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
  var pix = [];

  for (var ix = 0; ix < width; ++ix) {
    for (var iy = 0; iy < height; ++iy) {
      var x = xmin + (xmax - xmin) * ix / (width - 1);
      var y = ymin + (ymax - ymin) * iy / (height - 1);
      var i = mandelIter(x, y, iterations);
      var ppos = 4 * (width * iy + ix);

      if (i > iterations) {
        pix[ppos] = 0;
        pix[ppos + 1] = 0;
        pix[ppos + 2] = 0;
      } else {
        var c = 3 * Math.log(i) / Math.log(iterations - 1.0);

        if (c < 1) {
          pix[ppos] = Math.round(255 * c);
          pix[ppos + 1] = 0;
          pix[ppos + 2] = 0;
        } else if (c < 2) {
          pix[ppos] = 255;
          pix[ppos + 1] = Math.round(255 * (c - 1));
          pix[ppos + 2] = 0;
        } else {
          pix[ppos] = 255;
          pix[ppos + 1] = 255;
          pix[ppos + 2] = Math.round(255 * (c - 2));
        }
      }
      pix[ppos + 3] = 255;
    }
  }

  return pix;
}
