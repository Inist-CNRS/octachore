# Octachore

Just another nodeJS wrapper for [tesseract-ocr](https://github.com/tesseract-ocr)

## Usage
```javascript

const Octachore = require('octachore')

let ocr = new Octachore()

ocr.input(__dirname + '/data/test.tif')
  .output(__dirname + '/data/output/test')
  .lang('fra')
  .exec().catch((error) => {
    // Do something
  }).then((sdtout) => {
    // Do something
  })
```

## API

* input
* output
* lang
* psm (page segmentation mode)


### TODO

* Make a C++ module for nodeJS with tesseract and leptonica
