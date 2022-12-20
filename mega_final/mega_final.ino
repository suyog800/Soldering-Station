#include <AccelStepper.h>
#include <ezButton.h>
#include <String.h>
using namespace std;

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
AccelStepper stepperX(1, X_STEP_PIN, X_DIR_PIN); // 1 = Driver

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
AccelStepper stepperY(1, Y_STEP_PIN, Y_DIR_PIN); // 1 = Driver

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
AccelStepper stepperZ(1, Z_STEP_PIN, Z_DIR_PIN); // 1 = Driver

#define E_STEP_PIN        26
#define E_DIR_PIN         28
#define E_ENABLE_PIN      24
AccelStepper extruder(1, E_STEP_PIN, E_DIR_PIN); // 1 = Driver

String inString1 = "";    // string to hold input
String sub1 = "";    
String sub2 = "";
String sub3 = "";
String sub4 = "";
int pos[3];
int j=0;

ezButton limitSwitchLF(3); // left X XMIN
ezButton limitSwitchRG(2);//right X XMAX
ezButton limitSwitchLW(18); // lower Z ZMIN
ezButton limitSwitchHG(19);//upper Z ZMAX

long TravelX;  // Used to store the X value entered in the Serial Monitor
long TravelZ;// Used to store the Y value entered in the Serial Monitor
long TravelE;  
long TravelY;
void setup()
{ 
 
   
 stepperX.setEnablePin(X_ENABLE_PIN);
  stepperX.setPinsInverted(false, false, true); //invert logic of enable pin
  stepperX.enableOutputs(); 
  stepperX.setMaxSpeed(800.0); //SPEED = Steps / second
  stepperX.setAcceleration(800.0); //ACCELERATION = Steps /(second)^2
  
 stepperZ.setEnablePin(Z_ENABLE_PIN);
  stepperZ.setPinsInverted(false, false, true); //invert logic of enable pin
  stepperZ.enableOutputs();
  stepperZ.setMaxSpeed(800); //SPEED = Steps / second
  stepperZ.setAcceleration(800); //ACCELERATION = Steps /(second)^2

stepperY.setEnablePin(Y_ENABLE_PIN);
  stepperY.setPinsInverted(false, false, true); //invert logic of enable pin
  stepperY.enableOutputs();
  stepperY.setMaxSpeed(800); //SPEED = Steps / second
  stepperY.setAcceleration(800); //ACCELERATION = Steps /(second)^2

extruder.setEnablePin(E_ENABLE_PIN);
  extruder.setPinsInverted(false, false, true); //invert logic of enable pin
  extruder.enableOutputs();
  extruder.setMaxSpeed(800); //SPEED = Steps / second
  extruder.setAcceleration(800); //ACCELERATION = Steps /(second)^2


  Serial.begin(115200);
 
}

/*
void limitswitches()//function to check the limit switches
{
  limitSwitchLW.loop();
  if (limitSwitchLW.isPressed())
  {
    Serial.println("Lower Z is pressed");
   // stepperZ.setCurrentPosition(0);
    stepperZ.moveTo(0); //check sign accordingly to direction
    // TravelZ=0;
    //run_motor();
  }
  limitSwitchHG.loop();
  if (limitSwitchHG.isPressed())
  {
    Serial.println("Upper Z is pressed");
    //stepperZ.setCurrentPosition(0);
    stepperZ.moveTo(0);
    // TravelZ=0;
    //run_motor();
  }
  limitSwitchLF.loop();
  if (limitSwitchLF.isPressed())
  {
    Serial.println("Left x is pressed");
    //stepperX.setCurrentPosition(0);
    stepperX.moveTo(0);
   // TravelX=0;
    //run_motor();
  }
  limitSwitchRG.loop();
  if (limitSwitchRG.isPressed())
  {
    Serial.println("Right x is pressed");
    //stepperX.setCurrentPosition(0);
    stepperX.moveTo(0);
 //    TravelX=0;
    //run_motor();
  }
}
*/
void loop()
{
 
//limitswitches();

 readpico();
 run_motor();
  
  
 





}

void readpico()
{
  while (Serial.available()>0)  
  { // Check if values are available in the Serial Buffer

 
  int inChar = Serial.read();
      inString1 += (char)inChar;
      
      if(inChar=='\n'){
    Serial.println(inString1);
    j=0;
      for (int i=0; i<=18;i++)
      { 
        if (inString1[i]==',')
         {pos[j]=i;
         j++;
         
         }
        }
      //Serial.print("Pos:");
      //Serial.println(pos);         
      for( int i =0; i<pos[0];i++)
        {sub1+=inString1[i];}  
      for( int i =pos[0]+1; i<pos[1];i++)
        {sub2+=inString1[i];}  
      for( int i =pos[1]+1; i<pos[2];i++)
        {sub3+=inString1[i];}
       for( int i =pos[2]+1; i<=18;i++)
        {sub4+=inString1[i];}        
      TravelZ = sub1.toInt();
      TravelX = sub2.toInt();
      TravelY = sub3.toInt();
      TravelE = sub4.toInt();
      Serial.print("TravelZ ");
      Serial.println(TravelZ);
      Serial.print("TravelX ");
      Serial.println(TravelX);
      Serial.print("TravelY ");
      Serial.println(TravelY);
      
      // clear the string for new input:
      inString1 = "";
      sub1= "";
      sub2="";
      sub3="";
      sub4="";
      }
   }
}
void run_motor()
{
  int opp1 = -100*TravelX;
    stepperX.enableOutputs(); //enable pins
    stepperX.moveTo(opp1); //-1 is to match the rotation of the encoder with the rotation of the stepper
  int opp2 = -100*TravelZ;
    stepperZ.enableOutputs(); //enable pins
    stepperZ.moveTo(opp2); //-1 is to match the rotation of the encoder with the rotation of the stepper

    int opp3 = -100*TravelY;
    stepperY.enableOutputs(); //enable pins
    stepperY.moveTo(opp3); //-1 is to match the rotation of the encoder with the rotation of the stepper  

      int opp4 = -50*TravelE;
    extruder.enableOutputs(); //enable pins
    extruder.moveTo(opp4); //-1 is to match the rotation of the encoder with the rotation of the stepper
    
    while(((stepperZ.distanceToGo() != 0)||(stepperX.distanceToGo() != 0))||((stepperY.distanceToGo() !=0) ||(extruder.distanceToGo() !=0)))
    { 
     //limitswitches();
      //stepperX.runToNewPosition(opp1);
      //stepperZ.runToNewPosition(opp2);
    stepperZ.run();  
    stepperY.run();
    stepperX.run();
    extruder.run();
    }  
}
