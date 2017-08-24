#ifndef OCTACHORE_H
#define OCTACHORE_H

#include <leptonica/allheaders.h>
#include <nan.h>
#include <string>
#include <tesseract/baseapi.h>

class Octachore : public Nan::ObjectWrap {
public:
  static void Init(v8::Local<v8::Object> exports);

private:
  explicit Octachore();
  ~Octachore();
  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static inline Nan::Persistent<v8::Function>& constructor();
  static void load(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void getAllText(const Nan::FunctionCallbackInfo<v8::Value>& info);
  Pix* image;
  tesseract::TessBaseAPI* api;
};

#endif // !OCTACHORE_H
