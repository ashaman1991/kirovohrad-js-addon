'use strict';
let http = require('http');
let addon = require('./addon/');
let plain = require('./plain');
let util = require('./util');

// http.createServer(function (req, res) {
//     let url = req.url;
//     console.log(url);
//     res.writeHead(200, {
//       'Content-Type': 'text/plain'
//     });
//     res.end('Hello World\n');
//   })
//   .listen(1337, "127.0.0.1");

console.log('Server running at http://127.0.0.1:1337/');
let height = 800;
let width = 1200;
let pic = plain.heavy(height, width);
// console.log(pic);
util.generatePng(pic, height, width);
