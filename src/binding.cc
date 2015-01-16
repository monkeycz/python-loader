
#include <node.h>

#ifdef WIN32
#include <windows.h>
#endif

using namespace v8;
using namespace node;

Handle<Value> load(const Arguments& args)
{
    HandleScope scope;

    if (args.Length() < 1 || !args[0]->IsString()) {
        return ThrowException(
            Exception::Error(String::New("Missing param: load(pythonHome).")));
    }

    String::Utf8Value pythonHome(args[0]->ToString());

#ifdef WIN32
    char lpPathStringA[MAX_PATH];
    wchar_t lpPathStringW[MAX_PATH];

    sprintf(lpPathStringA, "%s", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0, lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (!SetEnvironmentVariable(L"PYTHONHOME", lpPathStringW)) {
        return ThrowException(
            Exception::Error(String::New("Failed to set environment variable: PYTHONHOME.")));
    }

    sprintf(lpPathStringA, "%s\\python27.dll", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0, lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (LoadLibrary(lpPathStringW) == NULL) {
        return ThrowException(
            Exception::Error(String::New("Failed to load library: python27.dll.")));
    }

    sprintf(lpPathStringA, "%s\\pywintypes27.dll", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0,lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (LoadLibrary(lpPathStringW) == NULL) {
        return ThrowException(
            Exception::Error(String::New("Failed to load library: pywintypes27.dll.")));
    }

    sprintf(lpPathStringA, "%s\\pythoncomloader27.dll", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0, lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (LoadLibrary(lpPathStringW) == NULL) {
        return ThrowException(
            Exception::Error(String::New("Failed to load library: pythoncomloader27.dll.")));
    }

    sprintf(lpPathStringA, "%s\\pythoncom27.dll", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0, lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (LoadLibrary(lpPathStringW) == NULL) {
        return ThrowException(
            Exception::Error(String::New("FFailed to load library: pythoncom27.dll.")));
    }
#elif __APPLE__
    setenv("PYTHONHOME", *pythonHome, 1);
#endif

    return Undefined();
}

void init(Handle<Object> exports)
{
    HandleScope scope;

    // module.exports.load
    exports->Set(String::NewSymbol("load"),
        FunctionTemplate::New(load)->GetFunction());
}

NODE_MODULE(binding, init)
