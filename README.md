# python-loader binding

Load Python runtime from specified path.


## Usage

```javascript
var path = require('path');
var pythonHome;
if (process.platform === 'win32') {
	pythonHome = path.join(path.dirname(process.execPath), 'Python27');
} else if (process.platform === 'darwin') {
	pythonHome = '/System/Library/Frameworks/Python.framework/Versions/Current';
}
var pythonLoader = require('python-loader');
pythonLoader.load(pythonHome);
```


## Build

### Mac

```bash
# for Node.js
node-gyp rebuild --arch=[ia32/x64] --target=x.y.z 
# target nodejs version, eg: 0.10.28

```

```bash
# for node-webkit
nw-gyp rebuild --arch=[ia32/x64] --target=x.y.z 
# target node-webkit version, eg: 0.8.6

```

### Windows

```bash
# for Node.js
cd python-loader\src
cl /O2 /MT /LD -Febinding.node binding.cc <NODE_GYP_ROOT>\.node-gyp\<NODEJS_VERSION>\<NODEJS_ARCH>\node.lib <PYTHON_ROOT>\Python27\libs\python27.lib /I<NODE_GYP_ROOT>\.node-gyp\<NODEJS_VERSION>\src /I<NODE_GYP_ROOT>\.node-gyp\<NODEJS_VERSION>\deps\uv\include /I<NODE_GYP_ROOT>\.node-gyp\<NODEJS_VERSION>\deps\v8\include /I<PYTHON_ROOT>\Python27\include /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE"
copy binding.node <NODE_MODULES_ROOT>\python-loader\compiled\<NODEJS_VERSION>\win32\<NODEJS_ARCH>

```

```bash
# for node-webkit
cd python-loader\src
cl /O2 /MT /LD -Febinding.node binding.cc <NW_GYP_ROOT>\.nw-gyp\<NODE_WEBKIT_VERSION>\<NODE_WEBKIT_ARCH>\nw.lib <PYTHON_ROOT>\Python27\libs\python27.lib /I<NW_GYP_ROOT>\.nw-gyp\<NODE_WEBKIT_VERSION>\src /I<NW_GYP_ROOT>\.nw-gyp\<NODE_WEBKIT_VERSION>\deps\uv\include /I<NW_GYP_ROOT>\.nw-gyp\<NODE_WEBKIT_VERSION>\deps\v8\include /I<PYTHON_ROOT>\Python27\include /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE"
copy binding.node <NODE_MODULES_ROOT>\python-loader\compiled\<NODEJS_VERSION>\win32\<NODE_WEBKIT_ARCH>

```


## Install

```bash
npm install python-loader
```

or

```bash
npm install <protocol>://<user>@<domain>/<projects>/python-loader.git
# eg: npm install git+ssh://git@example.com/projects/python-loader.git
```


## Test

```bash
node test/test.js
```
