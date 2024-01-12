#pragma once

/*
All speed values are in -255 to 255 range, -255 meaning bakcwards and 255 meaning forwards
*/

struct EclipseDriverMotorConfig {

	int pinPWMA;
	int pinPWMB;

	int pinA0;
	int pinA1;
	int pinB0;
	int pinB1;

	int pinSTANDBY;
	bool pinSTANDBYActiveState; //false if pin is active low, pull pin low to shutdown, if active high set to true

	bool invertLeft;
	bool invertRight;

};

static EclipseDriverMotorConfig getDefaultConfig() {

	EclipseDriverMotorConfig config;

	config.pinPWMA = 14;
	config.pinPWMB = 8;
	config.pinA0 = 13;
	config.pinA1 = 12;
	config.pinB1 = 9;
	config.pinB0 = 10;
	config.pinSTANDBY = 11;
	config.pinSTANDBYActiveState = false;
	config.invertLeft = false;
	config.invertRight = false;

	return config;

}


class EclipseDriverMotor {
	
public:

	EclipseDriverMotor(struct EclipseDriverMotorConfig config);  //Constructor
	EclipseDriverMotorConfig get_config();                       //Returns a struct containing the current config in use
	void begin();                                                //Initializes pins 
	void enableMotor(bool enable);                               //Alias for motor_standby
	void drive(int speed, int dir);                              //Converts a speed and direction to left and right values, and outputs them using left() and right();
	void left(int speed);                                        //Outputs to left motor
	void right(int speed);										 //Outputs to right motor
	                                                             
private:                                                         
	                                                             
	struct EclipseDriverMotorConfig _config;                     //Contains the current config being used
	void motor_standby(bool standby);

};
