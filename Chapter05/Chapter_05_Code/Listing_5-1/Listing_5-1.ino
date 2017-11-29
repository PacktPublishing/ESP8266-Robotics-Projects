#include "ESP8266WiFi.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "sensorbar.h" //SparkFun line follower array Arduino library

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(4);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(3);

// Uncomment one of the four lines to match your SX1509's address
//  pin selects. SX1509 breakout defaults to [0:0] (0x3E).
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
//const byte SX1509_ADDRESS = 0x3F;  // SX1509 I2C address (01)
//const byte SX1509_ADDRESS = 0x70;  // SX1509 I2C address (10)
//const byte SX1509_ADDRESS = 0x71;  // SX1509 I2C address (11)

SensorBar mySensorBar(SX1509_ADDRESS);

//Define motor polarity for left and right side -- USE TO FLIP motor directions if wired backwards
#define RIGHT_WHEEL_POL 1
#define LEFT_WHEEL_POL 1

//Define the states that the decision-making machines uses:
#define IDLE_STATE 0
#define READ_LINE 1
#define GO_FORWARD 2
#define GO_LEFT 3
#define GO_RIGHT 4

uint8_t state;

void driveBot( int16_t driveInput );
void turnBot( float turnInput );
void stop();


void setup() {

  AFMS.begin();

  mySensorBar.setBarStrobe();

  mySensorBar.clearInvertBits();

  mySensorBar.begin();

}

void loop() {

  int position = mySensorBar.getPosition();

  uint8_t nextState = state;

  switch (state) {
    case IDLE_STATE:
      stop();       // Stops both motors
      nextState = READ_LINE;
      break;
    case READ_LINE:
      if ( mySensorBar.getDensity() < 7 )
      {
        nextState = GO_FORWARD;
        if ( mySensorBar.getPosition() < -50 )
        {
          nextState = GO_LEFT;
        }
        if ( mySensorBar.getPosition() > 50 )
        {
          nextState = GO_RIGHT;
        }
      }
      else
      {
        nextState = IDLE_STATE;
      }
      break;
    case GO_FORWARD:
      driveBot(200);
      nextState = READ_LINE;
      break;
    case GO_LEFT:
      turnBot(-.75);
      nextState = READ_LINE;
      break;
    case GO_RIGHT:
      turnBot(.75);
      nextState = READ_LINE;
      break;
    default:
      stop();       // Stops both motors
      break;
  }
  state = nextState;
  //delay(100);
}



void driveBot( int16_t driveInput )
{
  int16_t rightVar;
  int16_t leftVar;
  rightVar = driveInput * RIGHT_WHEEL_POL;
  leftVar = -1 * driveInput * LEFT_WHEEL_POL;
  R_MOTOR->setSpeed (rightVar);
  L_MOTOR->setSpeed (leftVar);

}

void turnBot( float turnInput )
{
  int16_t rightVar;
  int16_t leftVar;
  //If turn is positive
  if ( turnInput > 0 )
  {
    rightVar = -1 * 255 * RIGHT_WHEEL_POL * turnInput;
    leftVar = -1 * 255 * LEFT_WHEEL_POL * turnInput;
  }
  else
  {
    rightVar = 255 * RIGHT_WHEEL_POL * turnInput * -1;
    leftVar = 255 * LEFT_WHEEL_POL * turnInput * -1;
  }

  R_MOTOR->setSpeed (rightVar);
  L_MOTOR->setSpeed (leftVar);
  delay(5);

}


void stop() {

  L_MOTOR->setSpeed(0);
  L_MOTOR->run( RELEASE );

  R_MOTOR->setSpeed(0);
  R_MOTOR->run( RELEASE );

}

