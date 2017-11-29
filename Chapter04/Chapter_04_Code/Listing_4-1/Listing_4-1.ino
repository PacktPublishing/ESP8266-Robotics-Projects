#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "da999e8ef4ac42148f9fe8427dxxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxxxxx";
char pass[] = "xxxxxx";

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(4);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(3);

// This function will be called every time Joystick Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1)
{
  int x = param[0].asInt(); // get x axis value
  int y = param[1].asInt(); // get y axis value

  // process received value
  if (y > 220)
    forward();

  else if (y < 35)
    backward();

  else if (x > 220)
    right();

  else if (x < 35)
    left();

  else
    stop();
}

void setup()
{
  Blynk.begin(auth, ssid, pass);

  AFMS.begin();

}

void loop()
{
  Blynk.run();
}

void forward() {

  L_MOTOR->setSpeed(200);
  L_MOTOR->run( FORWARD );

  R_MOTOR->setSpeed(200);
  R_MOTOR->run( FORWARD );

}

void backward() {

  L_MOTOR->setSpeed(150);
  L_MOTOR->run( BACKWARD );

  R_MOTOR->setSpeed(150);
  R_MOTOR->run( BACKWARD );

}

void stop() {

  L_MOTOR->setSpeed(0);
  L_MOTOR->run( RELEASE );

  R_MOTOR->setSpeed(0);
  R_MOTOR->run( RELEASE );

}

void left() {

  L_MOTOR->setSpeed(100);
  L_MOTOR->run( BACKWARD );

  R_MOTOR->setSpeed(100);
  R_MOTOR->run( FORWARD );

}

void right() {

  L_MOTOR->setSpeed(100);
  L_MOTOR->run( FORWARD );

  R_MOTOR->setSpeed(100);
  R_MOTOR->run( BACKWARD );

}

