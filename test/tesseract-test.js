'use strict'

const pkg = require('./../package.json'),
      child_process = require('child_process'),
      Tesseract = require('./../src/tesseract'),
      chai = require('chai'),
      expect = chai.expect

describe(pkg.name + '/tesseract.js', () => {
  describe('#input', () => {
    it('should set input param', (done) => {
      let ocr = new Tesseract()
      expect(ocr.input('fileInput.tif')._input).to.equal('fileInput.tif')
      done()
    })
  })
  describe('#output', () => {
    it('should set output param', (done) => {
      let ocr = new Tesseract()
      expect(ocr.output('fileOutput.tif')._output).to.equal('fileOutput.tif')
      done()
    })
  })
  describe('#lang', () => {
    it('should set lang option', (done) => {
      let ocr = new Tesseract()
      expect(ocr.lang('fra').options[0]).to.equal('-l fra')
      done()
    })
  })
  describe('#psm', () => {
    it('should set psm option', (done) => {
      let ocr = new Tesseract()
      expect(ocr.psm(3).options[0]).to.equal('-psm 3')
      done()
    })
  })
  describe('#exec', () => {
    it('should ocrize some tiff and give back some txt', (done) => {
      let ocr = new Tesseract()
      ocr.input(__dirname + '/data/test.tif')
        .output(__dirname + '/data/output/test')
        .lang('fra')
        .exec().then((sdtout) => {
          done()
        })
    })
    after(() => {
      child_process.exec('rm ' + __dirname + '/data/output/test.txt')
    })
  })
})
