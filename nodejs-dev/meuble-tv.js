var express = require("express");
var serialport = require('serialport');

const FIRST_CHAR = '>';
const LAST_CHAR = '$';

var portName = '/dev/ttyS0';
var serverPort = 8080;

// Open the port
var port = new serialport(portName, {
  baudRate: 9600,
  parser: new serialport.parsers.Readline('\n')
});

var app = express();

app.listen(serverPort, () => {
 console.log("Server running on port " + serverPort);
});

port.on('open', ()=>{
    console.log('Serial port open');
});

port.on('data', data =>{
	console.log('< ' + data.toString('ascii'));
});

function envoyerMessage(cmd, res) {
	port.write(cmd + '\n', (err) => {
	console.log('> ' + cmd);
    if (err) {
      res.status(500).json({message: "Erreur lors de l'envoi de la commande"});
    } else {
		res.status(200).json({message: "ok"});
		/*
		port.on('data', data =>{
			var retour = data.toString('ascii');
			console.log('< ', retour);
			if (retour == "ok") {
				res.status(200).json({message: "ok"});
			} else {
				res.status(500).json({message: "Commande inconnue"});
			}
		});
		*/		
	}
	res.end();
  });
}

app.get('/cmd/:cmd', (req, res) => {
  port.write(req.params.cmd + '\n', (err) => {
	console.log('> ' + req.params.cmd);
    if (err) {
      res.statusCode = 500;
    } else {
	  res.statusCode = 202; 	
	}
	res.end();
  });
});

app.get('/off', (req, res) => {
	envoyerMessage('off', res);
});

app.get('/clear', (req, res) => {
	envoyerMessage('clear', res);
});

app.get('/show', (req, res) => {
	envoyerMessage('show', res);
});

app.get('/rainbow', (req, res) => {
	envoyerMessage('rainbow', res);
});

app.get('/setBrightness/:scale', (req, res) => {
	envoyerMessage('setBrightness;' + req.params.scale, res);
});

app.get('/setColor/:pos/:color', (req, res) => {
	envoyerMessage('setColor;' + req.params.pos + ';' + req.params.color, res);
});

app.get('/color/white', (req, res) => {
	envoyerMessage('white', res);
});

app.get('/color/red', (req, res) => {
	envoyerMessage('red', res);
});

app.get('/color/green', (req, res) => {
	envoyerMessage('green', res);
});

app.get('/color/blue', (req, res) => {
	envoyerMessage('blue', res);
});

app.get('/color/:color', (req, res) => {
	envoyerMessage('color;' + req.params.color, res);
});

app.get('/setTop/:pos/:color', (req, res) => {
	envoyerMessage('setTop;' + req.params.pos + ';' + req.params.color, res);
});

app.get('/setBottom/:pos/:color', (req, res) => {
	envoyerMessage('setBottom;' + req.params.pos + ';' + req.params.color, res);
});

app.get('/setMiddle/:pos/:color', (req, res) => {
	envoyerMessage('setMiddle;' + req.params.pos + ';' + req.params.color, res);
});