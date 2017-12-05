// Water Level Sensor Code
// Author: Michael Sadlier
// Date: 12th December 2017

// This is the code for running a Low Powered Bluetooth Connected Water Level Measurer.
// Some important things to note before beginning:
//                  
//                  Pins
//      | GND | ---------- | GND of SONAR   |
//      |  2  | ---------- | TXD of BLE     |
//      |  3  | ---------- | RXD of BLE     |
//      |  4  | ---------- | GND of BLE     |
//      |  5  | ---------- | TRIG of SONAR  |
//      |  6  | ---------- | ECHO of SONAR  |
//      |  7  | ---------- | VCC of SONAR   |
//      |  8  | ---------- | VCC of BLE     |
//
// This is the order of the connections from the Arduino Pro Mini to the component in order to work from this code.
//
// The Arduino transmits a signal at 16 second intervals and broadcasts and senses for 0.35 seconds following that. This means that there are roughly 4 measurements a minute.
// When the measurement and broadcasting is done, the microcontroller goes into Watchdog more for 8 seconds. This uses the least power possible. After this, the cycle repeats.
// To turn off the bluetooth, the ground pin is brought up to VCC, meaning that there is not enough potential difference to transmit. When there is only ground it can somehow
// still transmit, so this is very much a roundabout solution.

#include <NewPing.h>
#include <LowPower.h>

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

#define TRIGGER_PIN  5 // Trigger for the sonar
#define ECHO_PIN     6 // Echo for the sonar
#define MAX_DISTANCE 400 
#define VCC_DIGITAL_PIN 4 // Ground for Bluetooth
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {

  mySerial.begin(9600);

  pinMode(4, OUTPUT); 
  digitalWrite(4, LOW);
  pinMode(7, OUTPUT); // 5V for sonar
  digitalWrite(7, LOW);
  pinMode(8, OUTPUT); 
  digitalWrite(8, HIGH);

  delay(100);
  
  sendCommand("AT");
  sendCommand("AT+ROLE0");
  sendCommand("AT+POWE3");
  sendCommand("AT+NAMEInitialising");
}

double percentage;
int distance;
String message;
 
void loop() {

  digitalWrite(4, LOW);
  digitalWrite(7, HIGH);
  
  delay(200); 
  
  distance = sonar.ping_cm();
  digitalWrite(7, LOW);
  
  percentage = (100.0 - (distance + 8.0) / 250.0 * 100.0);
  message = "AT+NAMETank level: " + (String)percentage + "%";
  sendCommand(message);
  
  digitalWrite(4,HIGH);

  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);   
  
}

void sendCommand(String command){
  mySerial.println(command);  
  delay(75); 
}
