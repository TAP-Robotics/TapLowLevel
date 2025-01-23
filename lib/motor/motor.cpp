#include <motor.hpp>

MotorSoftwareDriver::MotorSoftwareDriver()
{
	Serial.println("Initializing MotorSoftwareDriver");

	pinMode(MOTOR_A_ENCODER_A, INPUT);
	pinMode(MOTOR_A_ENCODER_B, INPUT);
	pinMode(MOTOR_A_INPUT_A, OUTPUT);
	pinMode(MOTOR_A_INPUT_B, OUTPUT);

	pinMode(MOTOR_B_ENCODER_A, INPUT);
	pinMode(MOTOR_B_ENCODER_B, INPUT);
	pinMode(MOTOR_B_INPUT_A, OUTPUT);
	pinMode(MOTOR_A_INPUT_B, OUTPUT);

	attachInterrupt(digitalPinToInterrupt(MOTOR_A_ENCODER_A), readEncoder, RISING);
}

void MotorSoftwareDriver::readEncoder()
{
	int b = digitalRead(MOTOR_A_ENCODER_B);
	if (b > 0)
	{
		MotorSoftwareDriver::motorAPosition++;
	}
	else
	{
		MotorSoftwareDriver::motorAPosition--;
	}
}

void MotorSoftwareDriver::setupPICINT()
{
	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT20);
	PCMSK2 |= (1 << PCINT22);
}

void MotorSoftwareDriver::setMotor(int dir)
{
	if (dir == 1)
	{
		digitalWrite(MOTOR_A_INPUT_A, HIGH);
		digitalWrite(MOTOR_A_INPUT_B, LOW);

		digitalWrite(MOTOR_B_INPUT_A, LOW);
		digitalWrite(MOTOR_B_INPUT_B, HIGH);
	}
	else if (dir == -1)
	{

		Serial.println("neg");
		digitalWrite(MOTOR_A_INPUT_A, LOW);
		digitalWrite(MOTOR_A_INPUT_B, HIGH);

		digitalWrite(MOTOR_B_INPUT_A, HIGH);
		digitalWrite(MOTOR_B_INPUT_B, LOW);
	}
}

void MotorSoftwareDriver::handlePICINT()
{
	if (digitalRead(MOTOR_B_ENCODER_A) == digitalRead(MOTOR_B_ENCODER_B))
	{
		MotorSoftwareDriver::motorBPosition++; // Increment position if direction is forward
	}
	else
	{
		MotorSoftwareDriver::motorBPosition--; // Decrement position if direction is backward
	}
}

ISR(PCINT2_vect) {
	MotorSoftwareDriver::handlePICINT();
}