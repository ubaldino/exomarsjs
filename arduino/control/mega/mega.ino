byte clave, valor;

void setup(){
  Serial1.begin(9600); //mini-mega
  Serial.begin(9600); //cubi-mega 
}

void loop(){
    delay(10);    
    if(Serial.available()){
        leerSerial();
        Serial1.write(clave);
        Serial1.write(valor);            
    }
    Serial.flush();
}

void leerSerial() {
    int band = 0;
    while( Serial.available() ){
        if( band == 0 ){
            clave = Serial.read();
            delay( 1 );
            valor = Serial.read();
            delay( 1 );
            band = 1;
        }
        else{
            Serial.read();
        }
    }
}


