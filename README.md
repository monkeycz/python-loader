# python-loader binding

load python runtime from specified path.


## Usage

```javascript

// for Windows
var path = require('path');
var pythonHome = path.join(path.dirname(process.execPath), 'Python27');
var pythonLoader = require('python-loader');
pythonLoader.load(pythonHome);

```


## Build

### For Mac

#### For Node.js
```bash

node-gyp rebuild --target=x.y.z 
# target nodejs version, eg: 0.10.28

```

#### For node-webkit
```bash

nw-gyp rebuild --target=x.y.z 
# target node-webkit version, eg: 0.8.6

```

### For Windows

#### For Node.js
```bash

cd python-loader\src
cl /O2 /MT /LD -Febinding.node binding.cc <NODE_GYP_ROOT>\.node-gyp\<NODEJS_VERSION>\ia32\node.lib <PYTHON_ROOT>\Python27\libs\python27.lib /I<NODE_GYP_ROOT>\.node-gyp\<NODEJS_VERSION>\src /I<NODE_GYP_ROOT>\.node-gyp\<NODEJS_VERSION>\deps\uv\include /I<NODE_GYP_ROOT>\.node-gyp\<NODEJS_VERSION>\deps\v8\include /I<PYTHON_ROOT>\Python27\include /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE"
copy binding.node <NODE_MODULES_ROOT>\python-loader\compiled\<NODEJS_VERSION>\win32\ia32

```

#### For node-webkit
```bash

cd python-loader\src
cl /O2 /MT /LD -Febinding.node binding.cc <NW_GYP_ROOT>\.nw-gyp\<NODE_WEBKIT_VERSION>\ia32\node.lib <PYTHON_ROOT>\Python27\libs\python27.lib /I<NW_GYP_ROOT>\.nw-gyp\<NODE_WEBKIT_VERSION>\src /I<NW_GYP_ROOT>\.nw-gyp\<NODE_WEBKIT_VERSION>\deps\uv\include /I<NW_GYP_ROOT>\.nw-gyp\<NODE_WEBKIT_VERSION>\deps\v8\include /I<PYTHON_ROOT>\Python27\include /D "WIN32" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE"
copy binding.node <NODE_MODULES_ROOT>\python-loader\compiled\<NODEJS_VERSION>\win32\ia32

```


## Install

```bash

npm install <protocol>://<user>@<domain>/<projects>/python-loader.git
# eg: npm install git+ssh://git@example.com/wapp/python-loader.git

```


## Test

```bash

node test/test.js

```
