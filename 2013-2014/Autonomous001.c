#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     irseeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S4,     sonar,          sensorSONAR)
#pragma config(Motor,  motorA,          oneShotMotor,  tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          slideMotor,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          pulleyMotor,   tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     leftMotor,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rightMotor,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     conveyorMotor, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

short inchesAsRotations(short inches)
{
	return inches * 100;
	//return inches * 220;
}

int determineSector(int rotations)
{
	int sector = 5;
	if (rotations > inchesAsRotations(45))
	{
		sector = 6;
	}

	return sector;
}

task scoreFromSensor()
{
	while (true)
	{
		int value = SensorValue[irseeker];
		int checkValue = determineSector(nMotorEncoder[leftMotor]);

  	if (value == checkValue)
  	{
  		motor[motorA] = 100;
  		wait1Msec(200);
  		motor[motorA] = 0;
  		wait1Msec(50);
  		motor[motorA] = -100;
  		wait1Msec(200);
  		motor[motorA] = 0;
  		break;
  	}
	}
}

task main()
{
	initializeRobot();
	// FIXME: This needs to be here!!!!
  waitForStart(); // Wait for the beginning of autonomous phase.

  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ////                                                   ////
  ////    Add your robot specific autonomous code here.  ////
  ////                                                   ////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////

  // FIXME: Put this back in to
	//wait1Msec(10000);

	// Reset to 0
  nMotorEncoder[leftMotor] = 0;

  StartTask(scoreFromSensor);

  // NOTE: Start slow for short period
  while (nMotorEncoder[leftMotor] < inchesAsRotations(2))
  {
  	motor[leftMotor] = 25;
  	motor[rightMotor] = 25;
  	wait1Msec(20);
  }

  // NOTE: Drive straight (FIX this code later)
  while (nMotorEncoder[leftMotor] < inchesAsRotations(70))
  {
  	motor[leftMotor] = 35;
  	motor[rightMotor] = 35;
  	wait1Msec(20);
  }
  motor[leftMotor] = 0;
 	motor[rightMotor] = 0;

 	nMotorEncoder[rightMotor] = 0;
 	while (nMotorEncoder[rightMotor] < inchesAsRotations(15))
 	{
 		motor[rightMotor] = 30;
	}
	motor[rightMotor] = 0;

	nMotorEncoder[leftMotor] = 0;
	while (nMotorEncoder[leftMotor] < inchesAsRotations(15))
	{
		motor[leftMotor] = 40;
		motor[rightMotor] = 40;
	}

	motor[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
 	while (nMotorEncoder[rightMotor] < inchesAsRotations(18))
 	{
 		motor[rightMotor] = 30;
	}
	motor[rightMotor] = 0;

	nMotorEncoder[leftMotor] = 0;
	while (nMotorEncoder[leftMotor] < inchesAsRotations(65))
	{
		motor[leftMotor] = 90;
		motor[rightMotor] = 90;
	}

	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}
