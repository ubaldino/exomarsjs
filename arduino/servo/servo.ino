#include <Servo.h>  
   

#define ANG_M1 90
#define ANG_M2 90



Servo servo1 , servo2 ;

void setup() {
	servo1.attach(  8 , 620 , 2200 );
	servo2.attach(  9 );
	delay( 500 );

	servo1.write( 90 );
	delay( 1000 );
	servo1.write( 90 );
	delay( 1000 );
	servo1.write( 90 );
	delay( 1000 );
	servo1.detach();
}

void loop() {
	servo1.write( 90 );
	for(int i=5 ; i<175 ; i++ ){
	    servo1.write( i );
	    delay(100);
	}
	
}
