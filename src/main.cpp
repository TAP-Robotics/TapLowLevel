#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_I2CDevice.h>

#define ENC1 2
#define ENC2 3
#define M1IN2 6
#define M1IN1 7

#define ENC21 4  // Pin change interrupt pin
#define ENC22 5
#define M2IN2 8
#define M2IN1 9

int pos = 0;
int dor = 1;

int pos2 = 0;

void readEncoder() {
	int b = digitalRead(ENC2);
	if (b > 0) { pos ++;} else { pos --; }
}

void setMotor(int dir) {
	if (dir == 1) {
		digitalWrite(M1IN1, HIGH);
		digitalWrite(M1IN2, LOW);		

		digitalWrite(M2IN1, LOW);
		digitalWrite(M2IN2, HIGH);
	} else if (dir == -1) {

		Serial.println("neg");
		digitalWrite(M1IN1, LOW);
		digitalWrite(M1IN2, HIGH);

		digitalWrite(M2IN1, HIGH);
		digitalWrite(M2IN2, LOW);		
	}
}

void setupPinChangeInterrupts() {
    PCICR |= (1 << PCIE2);    // Enable pin change interrupts for PORTD (pins 4-7)
    PCMSK2 |= (1 << PCINT20); // Enable interrupt for ENC21 (pin 4)
    PCMSK2 |= (1 << PCINT21); // Enable interrupt for ENC22 (pin 5)
}

ISR(PCINT2_vect) {
    if (digitalRead(ENC21) == digitalRead(ENC22)) {
        pos2++; // Increment position if direction is forward
    } else {
        pos2--; // Decrement position if direction is backward
    }
}

void setup()
{
	Serial.begin(9600);
	pinMode(ENC1, INPUT);
	pinMode(ENC2, INPUT);
	pinMode(M1IN1, OUTPUT);
	pinMode(M1IN2, OUTPUT);
	
	pinMode(ENC21, INPUT);
	pinMode(ENC22, INPUT);
	pinMode(M2IN1, OUTPUT);
	pinMode(M2IN2, OUTPUT);

	attachInterrupt(digitalPinToInterrupt(ENC1), readEncoder, RISING);
	setupPinChangeInterrupts();
}

void loop()
{
	Serial.print(">pos:");
	Serial.println(pos);
	setMotor(dor);
	dor = -dor;	

	Serial.print(">pos2:");
	Serial.println(pos2);	

	delay(5000);
}