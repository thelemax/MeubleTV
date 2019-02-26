// Require the serialport node module
var serialport = require('serialport');
var portName = '/dev/ttyS0';

const FIRST_CHAR = '>';
const LAST_CHAR = '$';


// Open the port
var port = new serialport(portName, {
    baudRate: 9600,
    parser: new serialport.parsers.Readline('\r\n')
});

// Read the port data
port.on('open', function () {
    console.log('Serial: open');
    port.on('data', function(data) {
        console.log('<<< '+data);
    });
});

//Send Message
exports.sendMessage = function(message) {
  console.log('>>> '+message);
  port.write(FIRST_CHAR+message+LAST_CHAR, (err) => {
    if (err) {
      console.log("ERREUR");
      throw err;
    }
  });
}
