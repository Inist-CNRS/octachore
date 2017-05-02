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
  void Execute() { std::this_thread::sleep_for(chrono::milliseconds(1000)); }
  // Executes in event loop
  void HandleOKCallback() {
    Local<Integer> codePSM = Nan::New(psm);
    Local<Value> argv[] = {codePSM};
    callback->Call(1, argv);
  }

private:
  int psm;
  string pathImage;
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