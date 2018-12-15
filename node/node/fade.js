var SerialPort = require("serialport");
const express = require('express');
const app = express();
var server = require("http").Server(app);
var io = require("socket.io").listen(server);


var Readline = SerialPort.parsers.Readline;



var serial = "n"



	



var port = new SerialPort('/dev/cu.usbmodem144140', {
	baudRate: 9600
})


const parser = port.pipe(new Readline({delimiter: '\r\n'}));
parser.on('data', function(e){
	console.log(e)
//	io.sockets.emit("event", e);
})
	// parser.on('data', data =>{
	//   console.log('got word from arduino:', data);
	// });

port.on('open', function(){
	console.log("Port sucessfull openden!")
})

port.on('close', function(){
	console.log("Arduino is disconnected!")
})

port.on('error', function(e){
	console.log(e)
})




/*
*
*
*
*	EXPRESS
*
*
*/



app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});


server.listen(3000, function(){
  console.log(':(');
});
app.use('/', express.static(__dirname));

/*
*
* THE WEBSOCKET
*
*/

io.on('connection', function(socket){
	console.log("A client connected to my server!")
	socket.on('toggle', function(msg){
		
		port.write("n")
  });
	socket.on('toggle2', function(msg){
		port.write("a")
  });
	socket.on('toggle3', function(msg){
		port.write("b")
  });
	socket.on('toggle4', function(msg){
		port.write("c")
  });
	socket.on('slider', function(msg){
		port.write(msg)
  });

})




/*

//-----STORY-----//

DEFINE

FRÜH MORGENS - (Aufstehen - noch dunkel)

MORGENS - (weg zur arbeit + supermarkt)

Mittags - (arbeit)

spät nachmittags - (finish work - mit kollegen weggehen)

abends - (nach hauseweg) 

abends - (zuhause)








*/ 

































