#include "octachore.hpp"
#include <chrono>
#include <nan.h>
#include <thread>

using namespace std;
using namespace Nan;
using namespace v8;

class GetAllComponentImageAsync : public AsyncWorker {
public:
  GetAllComponentImageAsync(string pathImage, int psm, Callback* callback)
      : pathImage(pathImage), psm(psm), AsyncWorker(callback) {}

  // Executes in worker thread
  void Execute() {
    blockBoxes = Octachore::getAllComponentImage(pathImage, static_cast<tesseract::PageIteratorLevel>(psm));
  }
  // Executes in event loop
  void HandleOKCallback() {
    if (blockBoxes) {
      Local<Array> results = New<v8::Array>(blockBoxes->n);
      Local<String> x_prop = Nan::New<String>("x").ToLocalChecked();
      Local<String> y_prop = Nan::New<String>("y").ToLocalChecked();
      Local<String> w_prop = Nan::New<String>("w").ToLocalChecked();
      Local<String> h_prop = Nan::New<String>("h").ToLocalChecked();
      for (int i = 0; i < blockBoxes->n; i++) {
        Local<Object> box = Nan::New<Object>();
        Nan::Set(box, x_prop, Nan::New<Number>(blockBoxes->box[i]->x));
        Nan::Set(box, y_prop, Nan::New<Number>(blockBoxes->box[i]->y));
        Nan::Set(box, w_prop, Nan::New<Number>(blockBoxes->box[i]->w));
        Nan::Set(box, h_prop, Nan::New<Number>(blockBoxes->box[i]->h));
        results->Set(i, box);
      }
      Local<Value> argv[] = {Nan::Null(), results};
      callback->Call(2, argv);
    } else {
      Local<String> error = Nan::New<String>("Cannot open input file").ToLocalChecked();
      Local<Value> argv[] = {error};
      callback->Call(1, argv);
    }
  }

private:
  int psm;
  string pathImage;
  Boxa* blockBoxes;
};

NAN_METHOD(getAllComponentImage) {
  v8::String::Utf8Value pathImage(info[0]->ToString());
  std::string strPathImage(*pathImage);
  int psm = info[1]->IntegerValue();
  Callback* callback = new Callback(info[2].As<Function>());
  AsyncQueueWorker(new GetAllComponentImageAsync(strPathImage, psm, callback));
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, New<String>("getAllComponentImage").ToLocalChecked(),
           GetFunction(New<FunctionTemplate>(getAllComponentImage)).ToLocalChecked());
}

NODE_MODULE(octachore, Init)