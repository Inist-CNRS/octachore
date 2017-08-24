const Octachore = require('../src/octachore');
const octa = new Octachore();
octa.load('data/test.tif', 'eng');
console.log(octa.getAllText(2));
