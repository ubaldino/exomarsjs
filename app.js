
app = require('express.io')()
app.http().io()

// ###########  conección usb_serial
var puerto_serial  = require( "serialport" );

/*
var interval = setInterval( function(){ 
    console.log("datos al cliente");
    app.io.broadcast( "mensaje", "mensaje del servidor"  );  
    //req.io.broadcast
}, 500 );
*/

var p_serial = new puerto_serial.SerialPort(
    "/dev/ttyUSB0" ,
    {
        baudrate: 9600 ,
        parser: puerto_serial.parsers.readline('\r\n')
    }
);  

p_serial.on( "close" , function (err) {
    console.log("Puerto serial cerrado");
});

p_serial.on("error", function (err) {
    console.error("error", err);
});

p_serial.on("open", function () {
    console.log("Puerto serial listo....");
});

p_serial.on( "data" , function (data) {
    console.log( data );
    app.io.broadcast( 'mensaje' ,  {
        mensaje: data
    });
});

//###########   rutas  ############
app.io.route('encender', function(req) {
    p_serial.write( "a" , function() {
      console.log('...Led prendido..');
    });

    req.io.respond({
        success: 'Mesage enviado desde el servidor encendido'
    })

})

app.io.route('apagar', function(req) {
    p_serial.write( "b" , function() {
      console.log('...Led apagado..');
      console.log( req.data.hey );
    });

    req.io.respond({
        success: 'Mesage enviado desde el servidor apagado'
    })

})

//##########   Peticiones  urls ################
app.get('/', function(req, res) {
    res.sendfile(__dirname + '/vista.html')
})

app.get('/jquery-2.0.3.min.js', function(req, res) { 
    res.sendfile(__dirname + '/js/jquery-2.0.3.min.js')
})

app.get('/control.js', function(req, res) { 
    res.sendfile(__dirname + '/js/control.js')
})

app.get('/joydiv.js', function(req, res) { 
    res.sendfile(__dirname + '/js/joydiv.js')
})

app.get('/estilos.css', function(req, res) { 
    res.sendfile(__dirname + '/css/estilos.css')
})

app.get('/joydiv-skin-default.css', function(req, res) { 
    res.sendfile(__dirname + '/css/joydiv-skin-default.css')
})

app.get('/taylor.mp4', function(req, res) { 
    res.sendfile(__dirname + '/taylor.mp4')
})

app.listen( 7076 )
console.log("exomars en linea puerto: 7076")
