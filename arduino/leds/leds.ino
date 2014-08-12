

void setup() {
	pinMode( 7 , 1 );
	Serial.begin( 9600 );
}

char leer_serial(){
	String valor = "";
	while( Serial.available() ){
	    valor += (char) Serial.read();
	    delay( 2 );
	}
	return valor[0];
}

void loop( ) {
	char valor = '\0';
	if( Serial.available() ){
	    valor = leer_serial();
	}

	if( valor == 'a' )
		digitalWrite( 7 , 1 );
	if( valor == 'b' )
		digitalWrite( 7 , 0 );
	delay(1);
	Serial.flush();

}
