//AccelStepper
#include <AccelStepper.h>
//AccelStepper stepper(1, 9, 8);// pulses Digital 9 (CLK); Direction Digital 8 (CCW)
//AccelStepper stepper=AccelStepper(1, 46,48 ); //AccelStepper(motorInterfaceType, stepPin, dirPin);
//Defining pins

/*#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62*/
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

AccelStepper stepper(1, X_STEP_PIN, X_DIR_PIN); // 1 = Driver

const int RotaryCLK = 19; //CLK pin on the rotary encoder
const int RotaryDT = 18; //DT pin on the rotary encoder
const int RotarySW = 2; //SW pin on the rotary encoder (Button function)
//const int multiple = 1;

//Defining variables
int ButtonCounter = 0;
int RotateCounter = 0;

//Statuses
int CLKNow;
int CLKPrevious;

int DTNow;
int DTPrevious;

unsigned long lastButtonPress = 0; 

//Time
float TimeNow1;
float TimeNow2;
float TimeNow3;



void setup()
{
  stepper.setEnablePin(X_ENABLE_PIN);
stepper.setPinsInverted(false, false, true); //invert logic of enable pin
stepper.enableOutputs();

  Serial.begin(9600);

   pinMode(19, INPUT_PULLUP);//monitors state of the switch between arduino and computer
   pinMode(18, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
   
    //Store states
  CLKPrevious = digitalRead(RotaryCLK); //obtains the value from clk pin and stores it in CLKprevious
  DTPrevious = digitalRead(RotaryDT);
 
 attachInterrupt(digitalPinToInterrupt(RotaryCLK), rotate, CHANGE);//Whenever a change will occur, the interrupt service routine(ISR) will be called. In this case the ISR is rotate
 attachInterrupt(digitalPinToInterrupt(RotaryDT), rotate, CHANGE);
 
 attachInterrupt(digitalPinToInterrupt(RotarySW), buttonPressed, FALLING); //CHANGE to trigger the interrupt whenever the pin changes value
                                                                           //FALLING for when the pin goes from high to low

  stepper.setMaxSpeed(1000); //SPEED = Steps / second
  stepper.setAcceleration(5000); //ACCELERATION = Steps /(second)^2

TimeNow1 = millis(); //stores the Start time
 
}


void loop()
{
  
  //TimeNow2 = millis();
  //buttonPressed();
 int swState = digitalRead(RotarySW);
    //If we detect LOW signal, button is pressed
  if (swState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      ButtonCounter++; //increase the counter
      Serial.println(ButtonCounter);
    }

    // Remember last button press event
    lastButtonPress = millis();
  }  
 if((ButtonCounter%2!=0)&&(ButtonCounter>0)) //is odd and more than 0
{ RunTheMotor1();} //single steps
  if(ButtonCounter%2==0) //is even (can be 0)
  { RunTheMotor2();}
}


//////////////////////////////////////////////////////////
void buttonPressed()
{  
  /*TimeNow2 = millis();
  if(TimeNow2 - TimeNow3 > 1000)
  {
  ButtonCounter++; //increase the counter
  }
  TimeNow3 = millis();
    //You can add something here, like resetting the RotateCounter (e.g. redefine 0 position) */
    // Read the button state
  /*int swState = digitalRead(RotarySW);
    //If we detect LOW signal, button is pressed
  if (swState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      ButtonCounter++; //increase the counter
      Serial.println(ButtonCounter);
    }

    // Remember last button press event
    lastButtonPress = millis();
  }  */
}
//////////////////////////////////////////////////////



void rotate()
{
  CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin

  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so increase
    if (digitalRead(RotaryDT) != CLKNow) {
      RotateCounter--;
     
    } else {
      // Encoder is rotating CW so decrease
      RotateCounter++;      
    }    
  }
  Serial.println(RotateCounter);
  CLKPrevious = CLKNow;  // Store last CLK state
}


void RunTheMotor1() //function for the motor
{    int opp = (-1)*RotateCounter;
    stepper.enableOutputs(); //enable pins
    stepper.moveTo(opp); //-1 is to match the rotation of the encoder with the rotation of the stepper
    while(stepper.distanceToGo() != 0)
    {
      stepper.runToNewPosition(opp);
    }
   
}

void RunTheMotor2() //function for the motor
{    int opp = (-1)*RotateCounter;
    stepper.enableOutputs(); //enable pins
    stepper.moveTo(opp*1000); //-1 is to match the rotation of the encoder with the rotation of the stepper
    while(stepper.distanceToGo() != 0)
    {
      stepper.runToNewPosition(opp*1000);
    }
   
}
