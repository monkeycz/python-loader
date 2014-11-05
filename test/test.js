
var path = require('path');

var pythonHome = path.join(path.dirname(process.execPath), 'Python27');

var pythonLoader = require('python-loader');
pythonLoader.load(pythonHome);
