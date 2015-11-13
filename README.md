# Node native addon performance demo for KirovohradJS conference

Uses Mandelbrot set generation algorythm to demonstrate differences in performance between JS and native C++ code on NodeJS.

## Installation

1) Clone
```
git clone https://github.com/ashaman1991/kirovohrad-js-addon.git && cd kirovohrad-js-addon
```

2) ``npm install``

3) Install libpng

For Ubuntu:
```
sudo apt-get install libpng12-dev
```

4) Build

```
npm run build
```

### Expose CLI globally

```
sudo npm link
```

## Using CLI

  Usage: native-demo [options]

```
  Options:

    -h, --help                    output usage information
    -V, --version                 output the version number
    -n, --native                  Use native async code (or use JS version by default)
    -o, --out [path]              Custom save path
    -i --iterations [iterations]  Number of iterations
    -c --count [count]            How much pictures do you want?
 ```
