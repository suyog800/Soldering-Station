// ConstantSpeed.pde
// -- mode: C++ --
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

#define Z_STEP_PIN       46 // 46
#define Z_DIR_PIN         48// 48
#define Z_ENABLE_PIN      62//62

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56
AccelStepper stepperz(1, Z_STEP_PIN, Z_DIR_PIN); // 1 = Driver
AccelStepper steppery(1, Y_STEP_PIN, Y_DIR_PIN);
void setup()
{  
  stepperz.setEnablePin(Z_ENABLE_PIN);
  stepperz.setPinsInverted(false, false, true); //invert logic of enable pin
  stepperz.enableOutputs();
  stepperz.setMaxSpeed(1000);
  stepperz.setSpeed(1000);	
  steppery.setEnablePin(Y_ENABLE_PIN);
  steppery.setPinsInverted(false, false, true); //invert logic of enable pin
  steppery.enableOutputs();
  steppery.setMaxSpeed(1000);
  steppery.setSpeed(1000);
}

void loop()
{  
   stepperz.runSpeed();
    steppery.runSpeed();
}