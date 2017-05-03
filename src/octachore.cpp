#include "octachore.hpp"
#include <sys/stat.h>
#include <vector>

using namespace std;

string Octachore::getAllText(string imagePath, string lang, tesseract::PageSegMode psm) {
  Pix* image = pixRead(imagePath.c_str());
  if (!image) {
    return nullptr;
  }
  tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
  api->Init(NULL, lang.c_str());
  api->SetPageSegMode(psm);
  api->SetImage(image);
  api->Recognize(0);
  string outputText{api->GetUTF8Text()};
  api->End();
  pixDestroy(&image);
  return outputText;
}

Boxa* Octachore::getAllComponentImage(string imagePath, tesseract::PageIteratorLevel blockType) {
  Pix* image = pixRead(imagePath.c_str());
  if (!image) {
    return nullptr;
  }
  tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
  api->Init(NULL, "eng");
  api->SetPageSegMode(tesseract::PSM_AUTO_ONLY);
  api->SetImage(image);
  Boxa* boxes = api->GetComponentImages(blockType, true, NULL, NULL);
  api->End();
  pixDestroy(&image);
  return boxes;
}