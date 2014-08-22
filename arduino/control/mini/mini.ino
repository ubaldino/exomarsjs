#include <Servo.h>
#include <string.h>

#define M1 2
#define M2 3
#define M3 4

#define M4 5
#define M5 6
#define M6 7

#define MIC 8 //M7
#define IR  9 //M8
#define CAM_ID 10 //M9
#define CAM_AB 11 //M10

#define ANG_M1 87
#define ANG_M2 86
#define ANG_M3 80

#define ANG_M4 86
#define ANG_M5 86
#define ANG_M6 85

#define ANG_CAM_ID 120
#define ANG_CAM_AB 100
#define ANG_MIC 90
#define ANG_IR 60

#define LI 0
#define LS 180

#define TEMP_CALC '\xee'
#define CHANGE_MODE '\xef'
#define MEDIR_DIST '\xf0'
#define IR_RIGHT '\xf1'
#define IR_LEFT '\xf2'
#define MIC_UP '\xf3'
#define MIC_DOWN '\xf4'
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

#define CAMARA_ARRIBA 74 //J
#define CAMARA_ABAJO  75 //K
#define CAMARA_IZQ    76 //L
#define CAMARA_DER    77 //M
#define MIC_ARRIBA    79 //N
#define MIC_ABAJO     78 //O
#define CAMARA_IZQ_C  80 //P
#define CAMARA_DER_C  81 //Q
#define IR_IZQ        82 //R
#define IR_DER        83 //S

Servo motor1 , motor2 , motor3 ;
Servo motor4 , motor5 , motor6 ;
Servo camid , camab , mic , ir ;
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
  inicializar();
  delay(500);
  killear();
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
            case CAMARA_ARRIBA :
                camab.attach(CAM_AB);
                camab_up();
                delay(500);
                camab.detach();
                break;
            case CAMARA_ABAJO :
                camab.attach(CAM_AB);
                camab_down();
                delay(500);
                camab.detach();
                break;
            case CAMARA_DER :
                camid.attach(CAM_ID);
                camid_der();
                delay(500);
                camid.detach();
                break;
            case CAMARA_IZQ :
                camid.attach(CAM_ID);
                camid_izq();
                delay(500);
                camid.detach();
                break;
            case MIC_ABAJO :
                mic.attach(MIC);
                mic_down();
                delay(500);
                mic.detach();
                break;    
            case MIC_ARRIBA :
                mic.attach(MIC);
                mic_up();
                delay(500);
                mic.detach();
                break;
            case CAMARA_IZQ_C :
                camid.attach(CAM_ID);
                camid_izq_bwd();
                delay(500);
                camid.detach();
                break;
            case CAMARA_DER_C :
                camid.attach(CAM_ID);
                camid_der_fwd();
                delay(500);
                camid.detach();
                break;
            case IR_IZQ :
                ir.attach(IR);
                ir_izq();
                delay(500);
                ir.detach();
                break;
            case IR_DER :
                ir.attach(IR);
                ir_der();
                delay(500);
                ir.detach();
                break;        
        }
        delay(10);
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

void camid_izq(){
  int ang = camid.read() - 10;
  if(ang < LS && ang > LI){
    camid.write(ang);
  }
  delay(100);
}

void camid_izq_bwd(){
  int nro = 0;
  Serial.println(camid.read());
  int ang = camid.read() - 35;
  if(ang < LS && ang > LI){
    while(nro < 7){
      camid.write(camid.read()-5);
      delay(70);
      nro = nro + 1;
    }
  }
  Serial.println(camid.read());
}

void camid_der_fwd(){
  int nro = 0;
  Serial.println(camid.read());
  int ang = camid.read() + 35;
  if(ang < LS && ang > LI){
    while(nro < 7){
      camid.write(camid.read()+5);
      delay(70);
      nro = nro + 1;
    }
  }
  Serial.println(camid.read());
}

void camid_der(){
  int ang = camid.read() + 10;
  if(ang < LS && ang > LI){
    camid.write(ang);
  }
  delay(100);
}

void camab_up(){
  int ang = camab.read() + 10;
  if(ang < LS && ang > LI){
    camab.write(ang);
  }
  delay(1000);
}

void camab_down(){
  int ang = camab.read() - 10;
  if(ang < LS && ang > LI){
    camab.write(ang);
  }
  delay(1000);
}

void mic_up(){/*
  Serial.println(Serial.read());
  if(mic.read() >= 90){
    for(int i = 110; i > 90; i--){
      mic.write(mic.read()-5);
      delay(70);
    }
  }
  Serial.println(mic.read());*/
  
  mic.write(90);
 
}

void mic_down(){/*
  Serial.println(Serial.read());
  for(int i = 90; i < 105; i++){
    mic.write(mic.read() + 5);
    delay(70);
  }
  Serial.println(mic.read());*/
  
  mic.write(30);
 
}

void inicializar(){
  camab.attach(CAM_AB);
  camid.attach(CAM_ID);
  mic.attach(MIC);
  ir.attach(IR);
  camab.write(ANG_CAM_AB);
  camid.write(ANG_CAM_ID);
  mic.write(ANG_MIC);
  ir.write(ANG_IR);
}

void killear(){
  camab.detach();
  camid.detach();
  mic.detach();
  ir.detach();
}

void ir_der(){
  Serial.println(ir.read());
  if(ir.read() == 60){
    ir.write(0);
  }else{
    ir.write(60);
  }
  Serial.println(ir.read());
}

void ir_izq(){
  Serial.println(ir.read());
  if(ir.read() == 60){
    ir.write(120);
  }else{
    ir.write(60);
  }
  Serial.println(ir.read());
}




