#include <Wire.h>
#include <Zumo32U4.h>
#include <LSM303.h>

Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4Encoders encoders;

unsigned long motorLastTime = 0;
long motorIntervalTime = 4; 
unsigned long imuLastTime = 0;
long imuIntervalTime = 10; 
int speed = 0;
int finalSpeed = 0;
LSM303 compass;
char report[80];

void setup()
{  
  buttonA.waitForButton();

  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
  
  delay(1000); 
}


void loop()
{ 
  unsigned long currentTime = millis();

  compass.read();
  
  if(currentTime - motorLastTime > motorIntervalTime) 
  {    
    motorLastTime = currentTime;   

    speed = speed % 360;
    speed++;
    finalSpeed = sin(radians(speed)) * 400;
    motors.setLeftSpeed(finalSpeed);      
    motors.setRightSpeed(finalSpeed);            

    snprintf(report, sizeof(report), "A: %6d E: %6d, %6d Speed: %6d", compass.a.x, encoders.getCountsLeft(), encoders.getCountsRight(), finalSpeed);
    Serial.println(report);
  } 
  
}
