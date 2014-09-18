

$(function() {

	/*io.on( 'mensaje', function( msg ) {
		if ( msg.charAt( 0 ) == 'X' ) {
			var datos = msg.split(":");
			var temperatura = datos[ 1 ];
			var humedad = datos[ 2 ];
			var distancia = datos[ 3 ];

			var dhtml = '<p>Temperatura : '+temperatura  '</p><br/>';
			dhtml += '<p>Humedad : ' + hunedad  '</p><br/>';
			dhtml += '<p>Distancia : ' + distancia  '</p><br/>';
			$('#muestreo').html( dhtml );
			
		}else{
			$("#pn_mensajes").html( msg.mensaje + "<br/>" )
			
		}
	});
	*/

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
