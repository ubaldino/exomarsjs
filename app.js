
var express = require('express');

app = require('express.io')()
app.http().io()

var passport         = require('passport')
  , util             = require('util')
  , FacebookStrategy = require('passport-facebook').Strategy
  , logger           = require('morgan')
  , session          = require('express-session')
  , bodyParser       = require("body-parser")
  , cookieParser     = require("cookie-parser")
  , expressLayouts = require('express-ejs-layouts')
  , methodOverride   = require('method-override');

var FACEBOOK_APP_ID = "292025954335781"
var FACEBOOK_APP_SECRET = "fb7a36d022187c96e065f5a9ecaacaa1";


passport.serializeUser(function(user, done) {
  done(null, user);
});

passport.deserializeUser(function(obj, done) {
  done( null , obj );
});


passport.use(new FacebookStrategy({
    clientID: FACEBOOK_APP_ID,
    clientSecret: FACEBOOK_APP_SECRET,
    callbackURL: "http://localhost:7076/auth/facebook/callback",
    profileFields: ['id', 'displayName', 'photos']
  },
  function(accessToken, refreshToken, profile, done) {
    process.nextTick(function () {
      return done(null, profile);
    });
  }
));


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
app.io.route('encender', function( req ) {
    trama = req.data.comando+req.data.velocidad;
    console.log( trama );

    if ( req.data.comando == "sensores" ) {
        trama = "RSX";
    }
    else if ( req.data.comando == 's' ) {
        var delay = 80 ;
        p_serial.write( "s0");        
        setTimeout( function(){
            p_serial.write( "s0");        
            console.log("stop seguro");        
        },delay);
        setTimeout( function(){
            p_serial.write( "s0");        
            console.log("stop seguro");        
        },delay); 
    }

    p_serial.write( trama , function() {
      console.log( trama );
    });

    req.io.respond({
        success: trama
    })

})

app.io.route('apagar', function(req) {
    p_serial.write( "s0" , function() {
      console.log('...Led apagado..');
      console.log( req.data.hey );
    });

    req.io.respond({
        success: 'Mesage enviado desde el servidor apagado'
    })

})


// configuraciones Express
app.use( '/static', express.static(__dirname + '/public') );

app.set( 'views', __dirname + '/vistas');
app.use( expressLayouts )
app.set( 'view engine', 'ejs');

app.use( logger() );
app.use( cookieParser() );
app.use( bodyParser() );
app.use( methodOverride() );
app.use( session( { secret: 'keyboard cat' } ) );

app.use( passport.initialize() );
app.use( passport.session() );




//##########   Peticiones  urls ################
app.get( '/' , filtroAuth , function( req , res ){
    console.log("----------------")
    console.log( req.user.photos[0].value )
    console.log("----------------")
    res.render( 'index' , { user : req.user } );
});

app.get( '/login' , function( req , res ){
  res.render( 'login' , { user : req.user } );
});

app.get('/taylor.mp4', function(req, res) { 
    res.sendfile(__dirname + '/taylor.mp4')
})



app.get('/auth/facebook',
  passport.authenticate('facebook', { scope: ['email', 'public_profile' , 'user_friends'] } ),
  function(req, res){
    // The request will be redirected to Facebook for authentication, so this
    // function will not be called.
  });

app.get('/auth/facebook/callback', 
    passport.authenticate('facebook', { failureRedirect: '/login' }),
    function(req, res) {
        res.redirect('/');
});



app.get('/logout', function(req, res){
  req.logout();
  res.redirect('/' );
});


app.listen( 7076 )

console.log("exomars en linea puerto: 7076")



function filtroAuth( req , res , next ) {
    if ( req.isAuthenticated() )
        return next(); 
    res.redirect('/login')
}