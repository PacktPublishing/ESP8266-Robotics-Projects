/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  WARNING!
    It's very tricky to get it working. Please read this article:
    http://help.blynk.cc/hardware-and-libraries/arduino/esp8266-with-at-firmware

  This sketch shows how to read values from Virtual Pins

  App project setup:
    Slider widget (0...100) on Virtual Pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// This is the library for the TB6612 that contains the class Motor and all the functions
#include <SparkFun_TB6612.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "53e4da8793764b6197fc44a673ce4e21";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Dialog4G";
char pass[] = "123456";

// Hardware Serial on Mega, Leonardo, Micro...
// #define EspSerial Serial

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
#define AIN1 12
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

const int offsetA = 1;
const int offsetB = 1;

// Initializing motors
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V1)
{
  int x = param[0].asInt(); // get x axis value
  int y = param[1].asInt(); // get y axis value

  // process received value

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

  if (y > 220)
    /*
      Use of the forward function, which takes as arguments two motors
      and optionally a speed.  If a negative number is used for speed
      it will go backwards
    */
    forward(motor1, motor2, 150);

  else if (y < 35)
    /*
      Use of the back function, which takes as arguments two motors
      and optionally a speed.  Either a positive number or a negative
      number for speed will cause it to go backwards
    */
    back(motor1, motor2, -150);

  else if (x > 220)
    /*
      Use of the left and right functions which take as arguments two
      motors and a speed.  This function turns both motors to move in
      the appropriate direction.  For turning a single motor use drive
    */
    right(motor1, motor2, 150);

  else if (x < 35)
    /*
      Use of the left and right functions which take as arguments two
      motors and a speed.  This function turns both motors to move in
      the appropriate direction.  For turning a single motor use drive
    */
    left(motor1, motor2, 150);

  else
    brake(motor1, motor2);


}

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8442);
}

void loop()
{
  Blynk.run();
}

