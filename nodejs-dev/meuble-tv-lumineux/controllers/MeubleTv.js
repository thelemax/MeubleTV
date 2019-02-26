'use strict';

var utils = require('../utils/writer.js');
var MeubleTv = require('../service/MeubleTvService');

module.exports.meuble_tv_color = function meuble_tv_color (req, res, next) {
  var color = req.swagger.params['color'].value;
  MeubleTv.meuble_tv_color(color)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};

module.exports.meuble_tv_command = function meuble_tv_command (req, res, next) {
  var command = req.swagger.params['command'].value;
  MeubleTv.meuble_tv_command(command)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};

module.exports.meuble_tv_scenario = function meuble_tv_scenario (req, res, next) {
  var scenario = req.swagger.params['scenario'].value;
  MeubleTv.meuble_tv_scenario(scenario)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};
