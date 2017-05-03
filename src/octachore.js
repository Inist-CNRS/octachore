const octachore = require("bindings")("octachore");
octachore.getAllComponentImage("/home/meja/Dev/envrac/tiff/lorem-ipsum.tif", 2, (error, results) => {
  if (error) {
    console.log(error)
  } else {
    console.log(results)
  }
})
module.exports = octachore;