var SerialPort = require("serialport");
const express = require('express');
const app = express();
var server = require("http").Server(app);
var io = require("socket.io").listen(server);


var Readline = SerialPort.parsers.Readline;



var serial = "n"



	



var port = new SerialPort('/dev/cu.usbmodem143140', {
	baudRate: 9600
})


const parser = port.pipe(new Readline({delimiter: '\r\n'}));
parser.on('data', function(e){
	sconsole.log(e)
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
	socket.on('stop', function(msg){
		
		port.write("stop")
  });
	socket.on('play', function(msg){
		port.write("play")
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






uint32_t early_morning[] = {72,75, 100};
uint32_t morning[] = {217,159, 108};
uint32_t day[] = {204,180, 249};
uint32_t afternoon[] = {193,180, 198};
uint32_t evening[] = {118,106, 109};
uint32_t lateevening[] = {49,49, 52};








*/ 

































