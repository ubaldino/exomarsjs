#include <Servo.h>
#include <string.h>

#define M1 2
#define M2 3
#define M3 4

#define M4 5
#define M5 6
#define M6 7

#define M7 2
#define M8 3

#define M9 14
#define M10 15


#define ANG_M1 87
#define ANG_M2 86
#define ANG_M3 80

#define ANG_M4 86
#define ANG_M5 86
#define ANG_M6 85

#define ANG_M7 120
#define ANG_M8 90

#define LI 0
#define LS 180

#define TEMP_CALC '\xee'
#define CHANGE_MODE '\xef'
#define MEDIR_DIST '\xf0'
#define IR_RIGHT '\xf1'
#define IR_LEFT '\xf2'
#define MIC_UP '\xf3'
#define MIC_DOWN '\xf4'
#define CAM1_RIGHT_FWD '\xf5'
#define CAM1_LEFT_BWD '\xf6'
#define CAM1_LEFT '\xf7' 
#define CAM1_RIGHT '\xf8'
#define CAM2_UP '\xf9'
#define CAM2_DOWN '\xfa'

#define ADELANTE    97  // a
#define RETROCEDER  114 // r
#define IZQUIERDA   105 // i
#define DERECHA     100 // d
#define DETENER     115 // s

#define IZQUIERDA_ADELANTE    73 // I
#define IZQUIERDA_RETROCEDER  72 // H

#define DERECHA_ADELANTE    68 // D
#define DERECHA_RETROCEDER  69 // E


Servo motor1 , motor2 , motor3 ;
Servo motor4 , motor5 , motor6 ;
Servo cam1 , cam2 , mic , ir ;
byte cmd;
int ir_sensor = A0;
byte trama_motores[] = { 0 , 0 } ;
byte clave , valor ;

void setup(){

  //atachar();
  /*
  ini();
  detachar();
  

  camatach();
  cam1.write(ANG_M7);
  cam2.write(ANG_M8);
  delay(1000);
  camdetach();
  */
  Serial.begin(9600);
  delay( 500 );
}

void loop(){
    delay( 10 );    
    if( Serial.available()  ){

        leerSerial();
        switch ( clave ) {
            case ADELANTE :
                adelante( valor );
                break;
            case RETROCEDER :
                retroceder( valor );
                break;
            case IZQUIERDA :
                izquierda( valor );
                break;
            case DERECHA :
                derecha( valor );
                break;
            case DETENER :
                detener();
                break;
            case IZQUIERDA_ADELANTE :
                izquierda_adelante( valor );
                break;
            case IZQUIERDA_RETROCEDER :
                izquierda_retroceder( valor );
                break;
            case DERECHA_ADELANTE :
                derecha_adelante( valor );
                break;
            case DERECHA_RETROCEDER :
                derecha_retroceder( valor );
                break;
        }
    }
    Serial.flush();
}


int velocidad_servo( byte velocidad ){
    int vel = 0;
    switch ( velocidad ) {
        case 48 : vel = 0  ; break ;
        case 49 : vel = 10 ; break ;
        case 50 : vel = 20 ; break ;
        case 51 : vel = 30 ; break ;
        case 52 : vel = 40 ; break ;
        case 53 : vel = 50 ; break ;
        case 54 : vel = 60 ; break ;
        case 55 : vel = 70 ; break ;
        case 56 : vel = 80 ; break ;
        case 57 : vel = 90 ; break ;
    }
    return vel;
}

void adelante ( byte velocidad ){
    atachar();
    int valor = velocidad_servo( velocidad );
    motor1.write( ANG_M1 + valor  );  
    motor2.write( ANG_M2 + valor  );  
    motor3.write( ANG_M3 + valor  );  

    motor4.write( ANG_M4 - valor  );  
    motor5.write( ANG_M5 - valor  );  
    motor6.write( ANG_M6 - valor  );  
}

void retroceder( byte velocidad ){
    atachar();
    int valor = velocidad_servo( velocidad );
    motor1.write( ANG_M1 - valor  );  
    motor2.write( ANG_M2 - valor  );  
    motor3.write( ANG_M3 - valor  );  

    motor4.write( ANG_M4 + valor  );  
    motor5.write( ANG_M5 + valor  );  
    motor6.write( ANG_M6 + valor  );  
}


void izquierda( byte velocidad ){
    atachar();
    int valor = velocidad_servo( velocidad );
    motor1.write( ANG_M1 + valor  );  
    motor2.write( ANG_M2 + valor  );  
    motor3.write( ANG_M3 + valor  );  

    motor4.write( ANG_M4 + valor  );  
    motor5.write( ANG_M5 + valor  );  
    motor6.write( ANG_M6 + valor  );  
}

void izquierda_adelante ( byte velocidad ){
    atachar();
    int valor = velocidad_servo( velocidad );
    motor1.write( ANG_M1 + valor ) ;  
    motor2.write( ANG_M2 + valor ) ;  
    motor3.write( ANG_M3 + valor ) ;  

    motor4.write( ANG_M4 - ( valor / 2 )  );  
    motor5.write( ANG_M5 - ( valor / 2 )  );  
    motor6.write( ANG_M6 - ( valor / 2 )  );  
}

void izquierda_retroceder( byte velocidad ){
    atachar();
    int valor = velocidad_servo( velocidad );
    motor1.write( ANG_M1 - ( valor / 2 )  );  
    motor2.write( ANG_M2 - ( valor / 2 )  );  
    motor3.write( ANG_M3 - ( valor / 2 )  );  

    motor4.write( ANG_M4 + valor );  
    motor5.write( ANG_M5 + valor );  
    motor6.write( ANG_M6 + valor );  
}




void derecha( byte velocidad ){
    atachar();
    int valor = velocidad_servo( velocidad );
    motor1.write( ANG_M1 - valor  );  
    motor2.write( ANG_M2 - valor  );  
    motor3.write( ANG_M3 - valor  );  

    motor4.write( ANG_M4 - valor  );  
    motor5.write( ANG_M5 - valor  );  
    motor6.write( ANG_M6 - valor  );  
}


void derecha_adelante ( byte velocidad ){
    atachar();
    int valor = velocidad_servo( velocidad );
    motor1.write( ANG_M1 + ( valor / 2 ) ) ;  
    motor2.write( ANG_M2 + ( valor / 2 ) ) ;  
    motor3.write( ANG_M3 + ( valor / 2 ) ) ;  

    motor4.write( ANG_M4 - valor  );  
    motor5.write( ANG_M5 - valor  );  
    motor6.write( ANG_M6 - valor  );  
}

void derecha_retroceder( byte velocidad ){
    atachar();
    int valor = velocidad_servo( velocidad );
    motor1.write( ANG_M1 - valor  );  
    motor2.write( ANG_M2 - valor  );  
    motor3.write( ANG_M3 - valor  );  

    motor4.write( ANG_M4 + ( valor / 2 ) );  
    motor5.write( ANG_M5 + ( valor / 2 ) );  
    motor6.write( ANG_M6 + ( valor / 2 ) );  
}



void detener(){
    motor1.write( ANG_M1 );  
    motor2.write( ANG_M2 );  
    motor3.write( ANG_M3 );  

    motor4.write( ANG_M4 );  
    motor5.write( ANG_M5 );  
    motor6.write( ANG_M6 );
    detachar();  
}

void vaciar_serial() {
    while( Serial.available() ){
        Serial.read();
        delay( 2 );
    }
    Serial.read();
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
        else
            Serial.read();
    }
}


void detachar(){
  motor1.detach() ;
  motor2.detach() ;
  motor3.detach() ;
  motor4.detach() ;
  motor5.detach() ;
  motor6.detach() ;
    
}

void atachar(){
  motor1.attach( M1 ) ;
  motor2.attach( M2 ) ;
  motor3.attach( M3 ) ;
  motor4.attach( M4 ) ;
  motor5.attach( M5 ) ;
  motor6.attach( M6 ) ;
    
}


