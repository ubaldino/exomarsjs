
$(function() {
	io = io.connect()

	io.on( 'mensaje', function( msg ) {
	    $("#pn_mensajes").html( msg.mensaje + "<br/>" )
	});

	$('.encender').on( 'click', function() {
	    console.log( "evento click - encender" );
	    io.emit('encender', { hey: 'server' }, function(data) {
		    console.log( data.success )
		})
	});

	$('.apagar').on( 'click', function() {
	    console.log( "evento click - apagar" );
	    io.emit('apagar', { hey: 'server' }, function(data) {
		    console.log( data.success )
		})
	});

	/*
	evento cuando carga la pagina
	io.emit('ready', { hey: 'server' }, function(data) {
	    console.log( data.success )
	})
	*/
});
