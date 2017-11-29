#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "XXXXXXXX";
char pass[] = "********";

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(4);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(3);

// This code will update the virtual port 1
BLYNK_WRITE(V1) {
  int pinData = param.asInt();
  if (pinData == 1) {
    forward();
  }
  else if (pinData == 2) {
    backward();
  }
  else if (pinData == 3) {
    left();
  }
  else if (pinData == 4) {
    right();
  }
  else {
    stop();
  }
}

void setup() {
  //Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  AFMS.begin();
}

void loop() {
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

