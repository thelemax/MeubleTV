'use strict';


var serial = require('../utils/serial.js');

/**
 *
 * color String 
 * returns String
 **/
exports.meuble_tv_color = function(color) {
  return new Promise(function(resolve, reject) {
    try {
      var commande = 'C'+color;
      examples['application/json'] = [{ "commande" : commande }];
      serial.sendMessage(commande);
      resolve(examples[Object.keys(examples)[0]]);
    } catch (err) {
      reject(err.message);
    }
  });
}


/**
 *
 * command String 
 * no response value expected for this operation
 **/
exports.meuble_tv_command = function(command) {
  return new Promise(function(resolve, reject) {
	try {
      serial.sendMessage(command);
      resolve();
    } catch (err) {
      reject(err.message);
    }
  });
}


/**
 *
 * scenario String 
 * returns String
 **/
exports.meuble_tv_scenario = function(scenario) {
  return new Promise(function(resolve, reject) {
    try {
      var commande = 'S'+scenario;
      var examples = {};
      examples['application/json'] = [{ "commande" : commande }];
      serial.sendMessage(commande);
      resolve(examples[Object.keys(examples)[0]]);
    } catch (err) {
      reject(err.message);
    }
  });
}

