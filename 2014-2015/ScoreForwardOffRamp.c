#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftMotor,     tmotorTetrix, PIDControl, driveLeft, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rightMotor,    tmotorTetrix, PIDControl, reversed, driveRight, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    leftServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    centerServo,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    rightServo,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    basketServo,          tServoStandard)
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

// NOTE: Wheels are 4" in diameter, times pi gives ~12.566" per rotation.
//       AndyMark motors are 280 CPR, or 1120 PPR (seen by nMotorEncoder[x])
//       Tetrix motors are 360 CPR, or 1440 PPR
//
//       12.566 in/rotation  1120 clicks/rotation  ~89 clicks/in

short inchesAsClicks(short inches)
{
	return (inches * 89);
}

task main()
{
  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.

  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ////                                                   ////
  ////    Add your robot specific autonomous code here.  ////
  ////                                                   ////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////

  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;

  servo[leftServo] = 124;
  servo[rightServo] = 131;

  // NOTE: Go forward down the ramp
  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(90))
  {
  	motor[leftMotor] = 30;
  	motor[rightMotor] = 30;  // Extra 1" for 10%, 2.5" for 25%, 3.5" for 50%
  }

  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;

  // NOTE: Go straight forward to cylinder (not convinced distances correct)
  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(5))
  {
  	motor[leftMotor] = 30;
  	motor[rightMotor] = 30;  // Extra 1" for 10%, 2.5" for 25%, 3.5" for 50%
  }

  // NOTE: Go straight forward to cylinder (not convinced distances correct)
  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(10))
  {
  	motor[leftMotor] = 15;
  	motor[rightMotor] = 15;  // Extra 1" for 10%, 2.5" for 25%, 3.5" for 50%
  }


  motor[leftMotor] = 0;
  motor[rightMotor] = 0;

  nMotorEncoder[Lift] = 0;

  while (nMotorEncoder[Lift] < 3500) {
  	motor[Lift] = 35;
  }
  while (nMotorEncoder[Lift] < 4000) {
  	motor[Lift] = 30;
  }
  while (nMotorEncoder[Lift] < 4500) {
  	motor[Lift] = 25;
  }

  // 5000 is about the exact height we need
  motor[Lift] = 0;

  servo[basketServo] = 246;
  wait1Msec(1250);
  servo[basketServo] = 135;

  // Drop the goal catcher
  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;

  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(4))
  {
    motor[leftMotor] = -100;
    motor[rightMotor] = -100;
  }

  motor[leftMotor] = 0;
  motor[rightMotor] = 0;
  wait1Msec(250);

  while (nMotorEncoder[Lift] > 1000) {
  	motor[Lift] = -35;
  }
  while (nMotorEncoder[Lift] > 500) {
  	motor[Lift] = -25;
  }
  while (nMotorEncoder[Lift] > 30) {
  	motor[Lift] = -15;
  }

  motor[Lift] = 0;

  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;

  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(10))
  {
  	motor[leftMotor] = -30;
  	motor[rightMotor] = -30;  // Extra 1" for 10%, 2.5" for 25%, 3.5" for 50%
  }

  motor[leftMotor] = 0;
  motor[rightMotor] = 0;

  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;

  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(12))
  {
  	motor[leftMotor] = 10;
  	motor[rightMotor] = 30;
  }

  motor[leftMotor] = 0;
  motor[rightMotor] = 0;

  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;

  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(8))  //7.5
  {
  	motor[leftMotor] = -30;
  	motor[rightMotor] = 30;
  }

  motor[leftMotor] = 0;
  motor[rightMotor] = 0;

  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;

  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(13)) //12.5
  {
  	motor[leftMotor] = -20;
  	motor[rightMotor] = -20;
  }

  motor[leftMotor] = 0;
  motor[rightMotor] = 0;

  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;

  servo[rightServo] = 244;

  wait1Msec(250);

  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(78))
  {
    motor[leftMotor] = 65;
    motor[rightMotor] = 70;
  }

  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(93))
  {
    motor[leftMotor] = 70;
    motor[rightMotor] = 70;
  }

  motor[leftMotor] = 0;
  motor[rightMotor] = 0;

  nMotorEncoder[leftMotor] = 0;
  nMotorEncoder[rightMotor] = 0;

  while (abs(nMotorEncoder[leftMotor]) < inchesAsClicks(18))
  {
    motor[leftMotor] = -30;
    motor[rightMotor] = 30;
  }

  motor[leftMotor] = 0;
  motor[rightMotor] = 0;

  wait1Msec(5000);
}
