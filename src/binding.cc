
#include <node.h>

#ifdef WIN32
#include <windows.h>
#endif

using namespace v8;
using namespace node;

void load(const FunctionCallbackInfo<Value>& args)
{
    HandleScope scope(args.GetIsolate());

    if (args.Length() < 1 || !args[0]->IsString()) {
        args.GetReturnValue().Set(args.GetIsolate()->ThrowException(
            Exception::Error(String::NewFromUtf8(args.GetIsolate(), "Missing param: load(pythonHome)."))));
        return;
    }

    String::Utf8Value pythonHome(args[0]->ToString());

#ifdef WIN32
    char lpPathStringA[MAX_PATH];
    wchar_t lpPathStringW[MAX_PATH];

    sprintf(lpPathStringA, "%s", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0, lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (!SetEnvironmentVariable(L"PYTHONHOME", lpPathStringW)) {
        args.GetReturnValue().Set(args.GetIsolate()->ThrowException(
            Exception::Error(String::NewFromUtf8(args.GetIsolate(), "Failed to set environment variable: PYTHONHOME."))));
        return;
    }

    sprintf(lpPathStringA, "%s\\python27.dll", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0, lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (LoadLibrary(lpPathStringW) == NULL) {
        args.GetReturnValue().Set(args.GetIsolate()->ThrowException(
            Exception::Error(String::NewFromUtf8(args.GetIsolate(), "Failed to load library: python27.dll."))));
        return;
    }

    sprintf(lpPathStringA, "%s\\pywintypes27.dll", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0,lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (LoadLibrary(lpPathStringW) == NULL) {
        args.GetReturnValue().Set(args.GetIsolate()->ThrowException(
            Exception::Error(String::NewFromUtf8(args.GetIsolate(), "Failed to load library: pywintypes27.dll."))));
        return;
    }

    sprintf(lpPathStringA, "%s\\pythoncomloader27.dll", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0, lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (LoadLibrary(lpPathStringW) == NULL) {
        args.GetReturnValue().Set(args.GetIsolate()->ThrowException(
            Exception::Error(String::NewFromUtf8(args.GetIsolate(), "Failed to load library: pythoncomloader27.dll."))));
        return;
    }

    sprintf(lpPathStringA, "%s\\pythoncom27.dll", *pythonHome);
    MultiByteToWideChar(CP_UTF8, 0, lpPathStringA, -1, lpPathStringW, MAX_PATH);
    if (LoadLibrary(lpPathStringW) == NULL) {
        args.GetReturnValue().Set(args.GetIsolate()->ThrowException(
            Exception::Error(String::NewFromUtf8(args.GetIsolate(), "Failed to load library: pythoncom27.dll."))));
        return;
    }
#elif __APPLE__
    setenv("PYTHONHOME", *pythonHome, 1);
#endif

    args.GetReturnValue().Set(Undefined(args.GetIsolate()));
}

void init(Handle<Object> exports)
{
    HandleScope scope(Isolate::GetCurrent());

    // module.exports.load
    exports->Set(String::NewFromUtf8(Isolate::GetCurrent(), "load", String::kInternalizedString),
        FunctionTemplate::New(Isolate::GetCurrent(), load)->GetFunction());
}

NODE_MODULE(binding, init)
