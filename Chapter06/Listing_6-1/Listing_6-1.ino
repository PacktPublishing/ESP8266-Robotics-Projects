#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Buttons
const int forward = 12;
const int backward = 13;
const int left = 14;
const int right = 15;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "XXXXXXXX";
char pass[] = "********";

WidgetBridge bridge1(V1); //Initiating Bridge Widget on V1 of CONTROLLER

void setup() {

  // initialize the pushbutton pin as an input:
  pinMode(forward, INPUT);
  pinMode(backward, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);

  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {
    // Wait until Blynk is connected
  }

}

BLYNK_CONNECTED() {
  bridge1.setAuthToken("OtherAuthToken"); // Token for the ROBOT
}

void loop() {
  Blynk.run();

  // read the state of the pushbutton FORWARD:
  int forwardButtonState = digitalRead(forward);

  // check if the pushbutton is pressed. If it is, the forwardButtonState is HIGH:
  if (forwardButtonState == HIGH) {
    bridge1.virtualWrite(V1, 1);
  } else {
    bridge1.virtualWrite (V1, 0);
  }

  // read the state of the pushbutton BACKWARD:
  int backwardButtonState = digitalRead(backward);

  // check if the pushbutton is pressed. If it is, the backwardButtonState is HIGH:
  if (backwardButtonState == HIGH) {
    bridge1.virtualWrite(V1, 2);
  } else {
    bridge1.virtualWrite (V1, 0);
  }

  // read the state of the pushbutton LEFT:
  int leftButtonState = digitalRead(left);

  // check if the pushbutton is pressed. If it is, the leftButtonState is HIGH:
  if (leftButtonState == HIGH) {
    bridge1.virtualWrite(V1, 3);
  } else {
    bridge1.virtualWrite (V1, 0);
  }

  // read the state of the pushbutton RIGHT:
  int rightButtonState = digitalRead(right);

  // check if the pushbutton is pressed. If it is, the rightButtonState is HIGH:
  if (rightButtonState == HIGH) {
    bridge1.virtualWrite(V1, 4);
  } else {
    bridge1.virtualWrite (V1, 0);
  }

}

