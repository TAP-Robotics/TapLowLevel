#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  205  // Minimum pulse length count (out of 4096)
#define SERVOMAX  410  // Maximum pulse length count (out of 4096)
#define USMIN     1000 // Minimum pulse width in microseconds
#define USMAX     2000 // Maximum pulse width in microseconds
#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates

int servoPins[5] = {0,1,2,3,4};

Adafruit_PWMServoDriver servoPwm = Adafruit_PWMServoDriver();

void setup() { 
	Serial.begin(9600);
	
	servoPwm.begin();
	servoPwm.setPWMFreq(SERVO_FREQ);

	servoPwm.setPWM(0, 0, SERVOMIN);
	servoPwm.setPWM(1, 0, SERVOMIN);
}

void loop() {
	for(int i = 0; i != 5; i ++) {
		servoPwm.setPWM(servoPins[i],0,SERVOMAX);
		delay(300);		
	}

	for(int i = 0; i != 5; i++) {
		servoPwm.setPWM(servoPins[i],0,SERVOMIN);
		delay(300);		
	}
}
