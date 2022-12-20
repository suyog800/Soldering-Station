#include <AccelStepper.h>
#include <ezButton.h>
#include <String.h>
using namespace std;

#define Z_ENABLE_PIN       62
#define X_ENABLE_PIN       38
AccelStepper stepperX(1,54,55); // 1 = Driver
AccelStepper stepperZ(1,46,48); 
// please correct the pin no
AccelStepper stepperY(1,4,7);
AccelStepper extruder(1,4,7);

String inString1 = "";    // string to hold input
String sub1 = "";    
String sub2 = "";
String sub3 = "";
String sub4 = "";
int pos[3];
int j=0;

ezButton limitSwitchLW(10); // lower Z
ezButton limitSwitchHG(11);//upper Z
ezButton limitSwitchLF(9); // left X
ezButton limitSwitchRG(A0);//right X

long TravelX;  // Used to store the X value entered in the Serial Monitor
long TravelZ;// Used to store the Y value entered in the Serial Monitor
long TravelE;  
long TravelY;
void setup()
{ 
 
   
  stepperX.setEnablePin(X_ENABLE_PIN);
  stepperX.setPinsInverted(false, false, true); //invert 
  stepperX.setMaxSpeed(800.0); //SPEED = Steps / second
  stepperX.setAcceleration(800.0); //ACCELERATION = Steps /(second)^2
  
  stepperZ.setEnablePin(Z_ENABLE_PIN);
  stepperZ.setPinsInverted(false, false, true); //invert 
  stepperZ.setMaxSpeed(800); //SPEED = Steps / second
  stepperZ.setAcceleration(800); //ACCELERATION = Steps /(second)^2

  stepperY.setMaxSpeed(800); //SPEED = Steps / second
  stepperY.setAcceleration(800); //ACCELERATION = Steps /(second)^2

  extruder.setMaxSpeed(800); //SPEED = Steps / second
  extruder.setAcceleration(800); //ACCELERATION = Steps /(second)^2


  Serial.begin(115200);
 
}


/*void limitswitches()
{
  limitSwitchLW.loop();
  if (limitSwitchLW.isPressed())
  {
    Serial.println("Lower Z is pressed");
    stepperZ.setCurrentPosition(0);
    //stepperZ.moveTo(200);
    move_motor();
  }
  limitSwitchHG.loop();
  if (limitSwitchHG.isPressed())
  {
    Serial.println("Upper Z is pressed");
    stepperZ.setCurrentPosition(0);
    //stepperZ.moveTo(-500);
    move_motor();
  }
  limitSwitchLF.loop();
  if (limitSwitchLF.isPressed())
  {
    Serial.println("Left x is pressed");
    stepperX.setCurrentPosition(0);
    //stepperX.moveTo(125);
    move_motor();
  }
  limitSwitchRG.loop();
  if (limitSwitchRG.isPressed())
  {
    Serial.println("Right x is pressed");
    stepperX.setCurrentPosition(0);
    //stepperX.moveTo(-125);
    move_motor();
  }
}

 void move_motor() {
  // Check if the Steppers have reached desired position

  while ((stepperX.distanceToGo() != 0) || (stepperZ.distanceToGo() != 0))
  {
    
    stepperX.run();  // Move Stepper X into position
    stepperZ.run();  // Move Stepper Z into position
  }
}*/

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
      for (int i=0; i<=18;i++)
      { if (inString1[i]==',')
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
      Serial.print("TravelX ");
      Serial.println(TravelX);
      Serial.print("TravelZ ");
      Serial.println(TravelZ);
      
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

      int opp4 = -10*TravelE;
    extruder.enableOutputs(); //enable pins
    extruder.moveTo(opp4); //-1 is to match the rotation of the encoder with the rotation of the stepper
    
    while(((stepperZ.distanceToGo() != 0)||(stepperX.distanceToGo() != 0))||(((stepperY.distanceToGo() !=0) ||(extruder.distanceToGo !=0))))
    { 
     //limitswitches();
      //stepperX.runToNewPosition(opp1);
      //stepperZ.runToNewPosition(opp2);
    stepperZ.run();  
    stepperX.run();
    steppery.run();
    extruder.run();
    }  
}