'use strict'

const child_process = require('child_process')

class Tesseract {
  constructor() {
    this.options = []
    this._input = null
    this._output = null
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
    this.options.push('-l ' + lang)
    return this
  }
  psm(number) {
    this.options.push('-psm ' + number)
    return this
  }
  exec() {
    if (!this.input || !this.output) {
      return new Error("Il manque un truc")
    }
    let args = this.options.concat(this._input).concat(this._output).join(' ')
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
