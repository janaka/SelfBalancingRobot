/********************************************************
 * 
 ********************************************************/

#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID speedPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

void setup()
{
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = analogRead(0);
  myPID.Compute();
  analogWrite(3,Output);
}

int getCurrrentSpeed() {

//Speed measure comes from the encoders of the motor it would seem ??. 
// with the stepper motor I should be able to calculate based on step timing or someting.

var speed;
return speed;
}

