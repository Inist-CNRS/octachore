'use strict'

const child_process = require('child_process')

class Tesseract {
  constructor() {
    this.options = []
    this._input = null
    this._output = null
    this._hocr = false
  }
  input(imagename) {
    this._input = imagename
    return this
  }
  output(outputbase) {
    this._output = outputbase
    return this
  }
  lang(lang) {
    this.options.unshift('-l ' + lang)
    return this
  }
  psm(number) {
    this.options.unshift('-psm ' + number)
    return this
  }
  hocr() {
    this._hocr = true
    return this
  }
  exec() {
    if (!this.input || !this.output) {
      return new Error("Missing something")
    }
    let args = this.options.concat(this._input).concat(this._output).join(' ')
    if (this._hocr) args += ' hocr'
    return new Promise((resolve, reject) => {
      child_process.exec('tesseract ' + args, (error, stdout, stderr) => {
        if (error) {
          reject(error)
        } else {
          resolve(stdout)
        }
      })
    })
  }
}

module.exports = Tesseract
