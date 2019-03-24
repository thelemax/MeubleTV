var express = require("express");
var bodyParser = require('body-parser')
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

const  app = express();
app.use(bodyParser.urlencoded({ extended: true }))
app.use(bodyParser.json());

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

/*
[
  { "commande": "nomCommande1", "parametres": ["param1", "param2", ... ] },
  { "commande": "nomCommande2", "parametres": ["param1", "param2", ... ] }
]
*/
app.post('/sequence', (req, res) => {
	 console.log(req.body);
  var commande = "";
  var array = req.body
  for (var i = 0; i < array.length; i++) {
	  if (i > 0) commande += '|';
	  switch (array[i].commande.toLowerCase()) {
		case 'loop':
			commande += 'LOOP';
			break;
		case 'sleep':
			commande += 'SLEEP';
			break;
		case 'off':
			commande += 'OFF';
			break;
		case 'clear':
			commande += 'CLEAR';
			break;
		case 'show':
			commande += 'SHOW';
			break;
		case 'rainbow':
			commande += 'RAINBOW';
			break;
		case 'setbrightness':
			commande += 'BRIGHT';
			break;
		case 'color':
			commande += 'COLOR';
			break;
		case 'setcolor':
			commande += 'COLORP';
			break;
		case 'settop':
			commande += 'TOP';	
			break;
		case 'setbottom':
			commande += 'BOTTOM';
			break;
		case 'setmiddle':
			commande += 'MIDDLE';
			break;
	    default:	
			res.status(500).json({message: "Commande inconnue"})
			res.end();
			return;
	  }
	  for (var j = 0; j < array[i].parametres.length; j++) {
		commande += ';' + array[i].parametres[j];
	  }
	  
  }
  envoyerMessage(commande, res);
});

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
	envoyerMessage('OFF', res);
});

app.get('/clear', (req, res) => {
	envoyerMessage('CLEAR', res);
});

app.get('/show', (req, res) => {
	envoyerMessage('SHOW', res);
});

app.get('/rainbow', (req, res) => {
	envoyerMessage('RAINBOW', res);
});

app.get('/setBrightness/:scale', (req, res) => {
	envoyerMessage('BRIGHT;' + req.params.scale, res);
});

app.get('/setColor/:pos/:color', (req, res) => {
	//BLANC, BLEU, ROUGE, VERT, MAGENTA, CYAN, JAUNE, GRIS, ROSE, VIOLET, ORANGE
	//255;255;255
	envoyerMessage('COLORP;' + req.params.pos + ';' + req.params.color, res);
});

app.get('/color/:color', (req, res) => {
	//BLANC, BLEU, ROUGE, VERT, MAGENTA, CYAN, JAUNE, GRIS, ROSE, VIOLET, ORANGE
	//255;255;255
	envoyerMessage('COLOR;' + req.params.color, res);
});

app.get('/setTop/:pos/:color', (req, res) => {
	envoyerMessage('TOP;' + req.params.pos + ';' + req.params.color, res);
});

app.get('/setBottom/:pos/:color', (req, res) => {
	envoyerMessage('BOTTOM;' + req.params.pos + ';' + req.params.color, res);
});

app.get('/setMiddle/:pos/:color', (req, res) => {
	envoyerMessage('MIDDLE;' + req.params.pos + ';' + req.params.color, res);
});