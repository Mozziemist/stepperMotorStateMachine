#include <Stepper.h>
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

const int buttonIncreaseSpeedPin = 4;
const int buttonStopResetPin = 2;

enum {INIT = 0, SPEED1 = 3, SPEED2 = 6, SPEED3 = 9, SPEED4 = 12};

int state;
int currentVelocity;


class ButtonListener {
  private:
    int prevButtonState;
    unsigned long prevPress;

  public:
    ButtonListener(){
      prevButtonState = LOW;
      prevPress = millis();
    }

    bool validButtonPress(int buttonPin){
      int buttonState = digitalRead(buttonPin);
      
      if (buttonState == LOW && prevButtonState == HIGH && millis() - prevPress > 1000)
        {
          prevButtonState = buttonState;
          prevPress = millis();
          return true;
        }
      else
        {
          prevButtonState = buttonState;
          return false;
        }
    }
};

/********************SETUP************************/
ButtonListener speedButton, stopButton;

void setup() {
  Serial.begin(9600);

  pinMode(buttonIncreaseSpeedPin, INPUT);
  pinMode(buttonStopResetPin, INPUT);

  state = INIT;
  currentVelocity = INIT;
}

/********************LOOP*************************/
void loop() {
  
  
  switch(state){
    case INIT:
      stateInit();
      break;
    case SPEED1:
      stateSpeed1();
      break;
    case SPEED2:
      stateSpeed2();
      break;
    case SPEED3:
      stateSpeed3();
      break;
    case SPEED4:
      stateSpeed4();
      break;
    default:
      break;
  }
  
}

/*********************STATEINIT*************************/
void stateInit(){

  //wait for input
  
  bool buttonPressed = false;

  Serial.println("init");

  do {
    if (speedButton.validButtonPress(buttonIncreaseSpeedPin))
    {
      Serial.println("speed pressed in init");
      switch (currentVelocity){
        case INIT:
          state = SPEED1;
          break;
        case SPEED1:
          state = SPEED1;
          break;
        case SPEED2:
          state = SPEED2;
          break;
        case SPEED3:
          state = SPEED3;
          break;
        case SPEED4:
          state = SPEED4;
          break;
        default:
          break;

      }
      buttonPressed = true;
    }
    else if (stopButton.validButtonPress(buttonStopResetPin))
    {
      currentVelocity = INIT;
      buttonPressed = true;
      Serial.println("stop pressed in init");
    }
  } while(!buttonPressed);
  
}

/******************STATESPEED1**************************/
void stateSpeed1(){
  //set motor to SPEED1
  myStepper.setSpeed(SPEED1);

  //micros per step
  double microsPerStep = (60000000 / (SPEED1 * stepsPerRevolution)) + 1;
  unsigned long prevStep = micros();

  Serial.println("speed1 ");
  

  //wait for input
  bool buttonPressed = false;

  do {
    if (micros() - prevStep > microsPerStep)
    {
      myStepper.step(1);
      prevStep = micros();
    }
    
    if (speedButton.validButtonPress(buttonIncreaseSpeedPin))
    {
      state = SPEED2;
      buttonPressed = true;
      Serial.println("speed pressed in speed1");
    }
    else if (stopButton.validButtonPress(buttonStopResetPin))
    {
      currentVelocity = SPEED1;
      state = INIT;
      buttonPressed = true;
      Serial.println("stop pressed in speed1");
    }
  } while(!buttonPressed);

  Serial.println("Left speed1");
}

/*******************STATESPEED2****************************/
void stateSpeed2(){
  //set motor to SPEED2
  myStepper.setSpeed(SPEED2);

  //micros per step
  double microsPerStep = (60000000 / (SPEED2 * stepsPerRevolution)) + 1;
  unsigned long prevStep = micros();

  Serial.println("speed2 ");

  //wait for input
  bool buttonPressed = false;

  do {
    if (micros() - prevStep > microsPerStep)
    {
      myStepper.step(1);
      prevStep = micros();
    }
    
    if (speedButton.validButtonPress(buttonIncreaseSpeedPin))
    {
      state = SPEED3;
      buttonPressed = true;
      Serial.println("speed pressed in speed2");
    }
    else if (stopButton.validButtonPress(buttonStopResetPin))
    {
      currentVelocity = SPEED2;
      state = INIT;
      buttonPressed = true;
      Serial.println("stop pressed in speed2");
    }
  } while(!buttonPressed);
}

/********************STATESPEED3*******************************/
void stateSpeed3(){
  //set motor to SPEED3
  myStepper.setSpeed(SPEED3);

  //micros per step
  double microsPerStep = (60000000 / (SPEED3 * stepsPerRevolution)) + 1;
  unsigned long prevStep = micros();

  Serial.println("speed3 ");

  //wait for input
  bool buttonPressed = false;

  do {
    if (micros() - prevStep > microsPerStep)
    {
      myStepper.step(1);
      prevStep = micros();
    }
    
    if (speedButton.validButtonPress(buttonIncreaseSpeedPin))
    {
      state = SPEED4;
      buttonPressed = true;
      Serial.println("speed pressed in speed3");
    }
    else if (stopButton.validButtonPress(buttonStopResetPin))
    {
      currentVelocity = SPEED3;
      state = INIT;
      buttonPressed = true;
      Serial.println("stop pressed in speed3");
    }
  } while(!buttonPressed);
}

/********************STATESPEED4*******************************/
void stateSpeed4(){
  //set motor to SPEED4
  myStepper.setSpeed(SPEED4);

  //micros per step
  double microsPerStep = (60000000 / (SPEED4 * stepsPerRevolution)) + 1;
  unsigned long prevStep = micros();

  Serial.println("speed4 ");

  //wait for input
  bool buttonPressed = false;

  do {
    if (micros() - prevStep > microsPerStep)
    {
      myStepper.step(1);
      prevStep = micros();
    }
    
    if (stopButton.validButtonPress(buttonStopResetPin))
    {
      currentVelocity = SPEED4;
      state = INIT;
      buttonPressed = true;
      Serial.println("stop pressed in speed4");
    }
  } while(!buttonPressed);
}
