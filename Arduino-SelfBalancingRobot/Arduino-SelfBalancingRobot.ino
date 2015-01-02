/********************************************************
 * 
 ********************************************************/

#include <PID_v1.h>

//Define Variables we'll be connecting to
double speedSetpoint, inputSpeed, outputSpeed;
double angleSetpoint, inputAngle, outputAngle;

//Specify the links and initial tuning parameters
PID speedPID(&inputSpeed, &outputSpeed, &speedSetpoint,2,5,1, DIRECT);
PID anglePID(&inputAngle, &outputAngle, &angleSetpoint,2,5,1, DIRECT);

double fakeangle = 10;
double fakespeed = 2;
void setup()
{
  Serial.begin(115200);
  Serial.println("init");
  initPIDs();
}

void loop()
{
 // Serial.print("compute");
  inputSpeed = getCurrentSpeed();
  speedSetpoint = 0; // keep stationary
  speedPID.Compute();
 //Serial.print(inputSpeed); 
 //Serial.print (F(" "));
 //Serial.println(outputSpeed);
 
  angleSetpoint = -outputSpeed;
  inputAngle = getCurrentAngle();
  
  
  anglePID.Compute();
  
  changeMotorSpeed(outputAngle);
  
  delay(1000);  
}

void initPIDs() {
   //initialize the variables we're linked to
  //inputSpeed = getCurrrentSpeed();
  speedSetpoint = 0;
  //inputAngle = getCurrentAngle();
  angleSetpoint = 0;
  anglePID.SetOutputLimits(-180,180);
  //turn the PID on
  speedPID.SetMode(AUTOMATIC); 
  anglePID.SetMode(AUTOMATIC); 
  
}

int getCurrentSpeed() {

  // Speed measure comes from the encoders of the motor it would seem ??. 
  // with the stepper motor I should be able to calculate based on step timing or someting.

  fakespeed = fakespeed + 1;
  return fakespeed;
}


int getCurrentAngle() {
  // this comes fromt he Acc + Gyro (MPU 6050 in my case)
  // not sure how to combine the x,y,z for a single value. Or do I take rotation angle around 
  //just Y
  //  I need β, β is the angle between the z axis and the Z axis. http://en.wikipedia.org/wiki/Euler_angles
  
  fakeangle = fakeangle + 1;
  return fakeangle;

}


void changeMotorSpeed(double pidOutputAngle)
{
 
   fakeangle = pidOutputAngle;
   fakespeed = pidOutputAngle;
  Serial.print("adjust motor = ");
  Serial.println(pidOutputAngle);
}

