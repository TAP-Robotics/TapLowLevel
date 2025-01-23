#pragma once
#include <Arduino.h>

#define MOTOR_A_ENCODER_A 2
#define MOTOR_A_ENCODER_B 3
#define MOTOR_A_INPUT_A 7
#define MOTOR_A_INPUT_B 6

#define MOTOR_B_ENCODER_A 4
#define MOTOR_B_ENCODER_B 5
#define MOTOR_B_INPUT_A 9
#define MOTOR_B_INPUT_B 8

class MotorSoftwareDriver
{
	int motorAPosition = 0;
	int motorBPosition = 0;

public:
	MotorSoftwareDriver();
	void setMotor(int dir);
	void readEncoder();
	void handlePICINT();

private:
	void setupPICINT();
	static int motorAPosition;
	static int motorBPosition;
};

int MotorSoftwareDriver::motorAPosition = 0;
int MotorSoftwareDriver::motorBPosition = 0;
