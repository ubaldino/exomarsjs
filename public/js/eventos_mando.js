var valor_camara = "Sin actividad";
var valor_exomars = "Sin actividad";
var element1 = document.getElementById('controller1');
var element2 = document.getElementById('controller2');
var joydiv1 = new JoydivModule.Joydiv( { 'element' : element1 } );
var joydiv2 = new JoydivModule.Joydiv( { 'element' : element2 } );
	
/*
function colores_cursores( id_cursor ){
	var ids_cursores = [ "adelante" , "izquierda" , "derecha" , "retroceder"];
	
	for (var i = ids_cursores.length - 1 ; i >= 0 ; i-- ) {
		
        var cursor = document.querySelector( "#"+ids_cursores[i] );
		if ( dato == ids_cursores[i] )
            cursor.style.borderBottomColor = "#F12F02";
        else
            cursor.style.borderBottomColor = null;
	}

}
*/

element1.addEventListener( 'joydiv-changed' , function( e ) {
    switch( joydiv1.getOneOf8Directions().name ){
    	case "up":
    		//colores_cursores("adelante");
			valor_exomars = "exomars: adelante";
			io.emit('encender', { comando: 'a' , velocidad: '4'  }, function( data ) {
			    console.log( data.success )
			})
			break;
    	case "down":
    		//colores_cursores("retroceder");
			valor_exomars = "exomars: atras";
			io.emit('encender', { comando: 'r' , velocidad: '4'  }, function( data ) {
			    console.log( data.success )
			})
			break;
    	case "left":
			valor_exomars = "exomars: izquierda";
			io.emit('encender', { comando: 'i' , velocidad: '4'  }, function( data ) {
			    console.log( data.success )
			})
			break;
		case "right":
			valor_exomars = "exomars: derecha";
			io.emit('encender', { comando: 'd' , velocidad: '4'  }, function( data ) {
			    console.log( data.success )
			})
			break;

    	case "up-left":
			valor_exomars = "exomars: adelante-izquierda";
			io.emit('encender', { comando: 'I' , velocidad: '4'  }, function( data ) {
			    console.log( data.success )
			})
			break;
    	case "up-right":
			valor_exomars = "exomars: adelante-derecha";
			io.emit('encender', { comando: 'D' , velocidad: '4'  }, function( data ) {
			    console.log( data.success )
			})
			break;
    	case "down-left":
			valor_exomars = "exomars: atras-izquierda";
			io.emit('encender', { comando: 'H' , velocidad: '4'  }, function( data ) {
			    console.log( data.success )
			})
			break;
    	case "down-right":
			valor_exomars = "exomars: atras-derecha";
			io.emit('encender', { comando: 'E' , velocidad: '4'  }, function( data ) {
			    console.log( data.success )
			})
			break;
    	case "none":
			valor_exomars = "exomars: Sin movimiento";
			io.emit('encender', { comando: 's' , velocidad: '0'  }, function( data ) {
			    console.log( data.success )
			})
			break;
    }
    document.getElementById( 'direction1' ).value = valor_exomars;
});

element2.addEventListener( 'joydiv-changed' , function( e ) {
    switch( joydiv2.getOneOf8Directions().name ){
    	case "up":
    		valor_camara = "camara: arriba"; 
    		io.emit('encender', { comando: 'J', velocidad: '0' }, function(data) {
			    console.log( data.success )
			});
    		break;
    	case "down":
    		valor_camara = "camara: abajo"; 
    		io.emit('encender', { comando: 'K', velocidad: '0' }, function(data) {
			    console.log( data.success )
			});
    		break;
    	case "left":
    		valor_camara = "camara: izquierda";
    		io.emit('encender', { comando: 'T', velocidad: '0' }, function(data) {
			    console.log( data.success )
			});
    		break;
		case "right":
    		valor_camara = "camara: derecha";
    		io.emit('encender', { comando: 'U', velocidad: '0' }, function(data) {
			    console.log( data.success )
			});
    		break;
    	case "up-left":
    		valor_camara = "camara: arriba-izquierda"; break;
    	case "up-right":
    		valor_camara = "camara: arriba-derecha"; break;
    	case "down-left":
    		valor_camara = "camara: abajo-izquierda"; break;
    	case "down-right":
    		valor_camara = "camara: abajo-derecha"; break;
    	case "none":
    		valor_camara = "camara: Sin movimiento"; break;
    }
    document.getElementById( 'direction2' ).value = valor_camara;

});
