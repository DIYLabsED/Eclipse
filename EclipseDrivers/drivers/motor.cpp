#include "motor.h"
#include "Arduino.h"

//Constructor
EclipseDriverMotor::EclipseDriverMotor(struct EclipseDriverMotorConfig config) {

	_config = config;

}

//Returns current confg in use, available to all
EclipseDriverMotorConfig EclipseDriverMotor::get_config() {
		
	return _config;

}

//Initializes pins
void EclipseDriverMotor::begin() {
		
	EclipseDriverMotorConfig config = get_config();

	pinMode(config.pinPWMA, OUTPUT);
	pinMode(config.pinPWMB, OUTPUT);
	pinMode(config.pinA0, OUTPUT);
	pinMode(config.pinA1, OUTPUT);
	pinMode(config.pinB0, OUTPUT);
	pinMode(config.pinB1, OUTPUT);
	pinMode(config.pinSTANDBY, OUTPUT);

	motor_standby(true);  //after initializing pins, put motor driver into standby mode

}

//Enables/Disables standby feature, true for standby, false for enable
void EclipseDriverMotor::motor_standby(bool standby) {
		
	EclipseDriverMotorConfig config = get_config();
	//If input is true, set standby pin to active state, else set it to inverse of that (deactive state)
	digitalWrite(config.pinSTANDBY, standby ? config.pinSTANDBYActiveState : !config.pinSTANDBYActiveState);

}

//Converts two inputs, front/back and left/right, called speed and turn, range -255 to 255, and convrets it into left and right speed values, range -255 to 255
void EclipseDriverMotor::drive(int speed, int dir) {

	int leftS = 0;
	int rightS = 0;

	leftS = speed + dir;
	rightS = speed - dir;

	leftS = constrain(leftS, -255, 255);
	rightS = constrain(rightS, -255, 255);

	left(leftS);
	right(rightS);

}

//Alias for motor_standby
void EclipseDriverMotor::enableMotor(bool enable) {

	motor_standby(!enable);

}

//Outputs to left motor
void EclipseDriverMotor::left(int speed) {

	EclipseDriverMotorConfig config = get_config();

	//Turn off motor if within 10 of zero either way
	if (speed > -10 && speed < 10) {
		analogWrite(config.pinPWMA, 0);
		return;
	}

	//If positive speed
	if (speed > 10) {

		analogWrite(config.pinPWMA, speed);
		digitalWrite(config.pinA0, config.invertLeft);
		digitalWrite(config.pinA1, !config.invertLeft);

	}

	//If negative speed
	if (speed < 10) {

		analogWrite(config.pinPWMA, -speed);
		digitalWrite(config.pinA0, !config.invertLeft);
		digitalWrite(config.pinA1, config.invertLeft);

	}

}

//Outputs to right motor
void EclipseDriverMotor::right(int speed) {

	EclipseDriverMotorConfig config = get_config();

	//Turn off motor if within 10 of zero either way
	if (speed > -10 && speed < 10) {
		analogWrite(config.pinPWMB, 0);
		return;
	}

	//If positive speed
	if (speed > 10) {

		analogWrite(config.pinPWMB, speed);
		digitalWrite(config.pinB0, config.invertRight);
		digitalWrite(config.pinB1, !config.invertRight);

	}

	//If negative speed
	if (speed < 10) {

		analogWrite(config.pinPWMB, -speed);
		digitalWrite(config.pinB0, !config.invertRight);
		digitalWrite(config.pinB1, config.invertRight);

	}

}
