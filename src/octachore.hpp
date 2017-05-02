#ifndef OCTACHORE_H
#define OCTACHORE_H

#include <leptonica/allheaders.h>
#include <string>
#include <tesseract/baseapi.h>

namespace Octachore {
std::string getAllText(std::string imagePath, std::string lang, tesseract::PageSegMode psm);
struct boxComponentImage {
  std::string name;
  Boxa* box;
};
Boxa* getAllComponentImage(std::string imagePath, tesseract::PageIteratorLevel blockType);
}

#endif // !OCTACHORE_H
