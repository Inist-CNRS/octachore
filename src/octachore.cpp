#include "octachore.hpp"
#include <vector>

using namespace std;
using namespace v8;

Octachore::Octachore() {}
Octachore::~Octachore() {}

Nan::Persistent<v8::Function>& Octachore::constructor() {
  static Nan::Persistent<v8::Function> my_constructor;
  return my_constructor;
}

void Octachore::Init(v8::Local<v8::Object> exports) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Octachore").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "load", load);
  Nan::SetPrototypeMethod(tpl, "getAllText", getAllText);

  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  exports->Set(Nan::New("Octachore").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

void Octachore::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    Octachore* obj = new Octachore();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor());
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void Octachore::load(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2)
    return Nan::ThrowTypeError("Load requires at least 2 argument");
  Octachore* octachore = Nan::ObjectWrap::Unwrap<Octachore>(info.Holder());
  String::Utf8Value imagePathAttr(info[0]->ToString());
  String::Utf8Value langAttr(info[1]->ToString());
  string imagePath(*imagePathAttr);
  string lang(*langAttr);

  octachore->image = pixRead(imagePath.c_str());
  if (!octachore->image) {
    return Nan::ThrowError("leptonica image initialization failed");
  }
  octachore->api = new tesseract::TessBaseAPI();
  octachore->api->Init(NULL, lang.c_str());
  octachore->api->SetImage(octachore->image);
}

void Octachore::getAllText(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1)
    return Nan::ThrowTypeError("Load requires at least 1 argument");
  Octachore* octachore = Nan::ObjectWrap::Unwrap<Octachore>(info.Holder());
  int psm(info[0]->NumberValue());
  octachore->api->SetPageSegMode(static_cast<tesseract::PageSegMode>(psm));
  octachore->api->Recognize(0);
  string outputText{octachore->api->GetUTF8Text()};
  info.GetReturnValue().Set(Nan::New<String>(outputText).ToLocalChecked());
}

// Boxa* Octachore::getAllComponentImage(string imagePath, tesseract::PageIteratorLevel blockType) {
//   Pix* image = pixRead(imagePath.c_str());
//   if (!image) {
//     return nullptr;
//   }
//   tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
//   api->Init(NULL, "eng");
//   api->SetVariable("debug_file", "/dev/null");
//   api->SetPageSegMode(tesseract::PSM_AUTO_ONLY);
//   api->SetImage(image);
//   Boxa* boxes = api->GetComponentImages(blockType, false, NULL, NULL);
//   api->End();
//   pixDestroy(&image);
//   return boxes;
// }

NODE_MODULE(octachore, Octachore::Init);