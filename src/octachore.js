const octachore = require(__dirname+'/../build/Release/octachore.node');
// const octachore = require(__dirname+'/../build/Debug/octachore.node');
octachore.getAllComponentImage("/home/meja/Dev/envrac/tiff/lorem-ipsum.tif", 5, (code) => {
  console.log(code);
})