/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-stepper-motor-28byj-48-uln2003/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  Based on Stepper Motor Control - one revolution by Tom Igoe
*/

#include <Stepper.h>
#include <FirebaseESP32.h>
#include  <WiFi.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution


#define FIREBASE_HOST "dog-house-f1317-default-rtdb.firebaseio.com"
#define WIFI_SSID "IRVING2" // Change the name of your WIFI
#define WIFI_PASSWORD "Intimacy@5$?@GranAda9" // Change the password of your WIFI
#define FIREBASE_Authorization_key "tpggs7qUBY2N9Zg8AWRCOXb6eWYAROVWuv1iKRyj"

// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17

FirebaseData firebaseData;
FirebaseData firebaseData1;
FirebaseJson json;

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

void setup() {
  // set the speed at 5 rpm
  myStepper.setSpeed(15);
  // initialize the serial port
  Serial.begin(115200);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  
}

void loop() {
  //reading data
  
  Firebase.getString(firebaseData1, "/Flutter_ESP_Actions/Food/food");
  // step one revolution in one direction:
  if (firebaseData1.stringData() == "on") { 
    Serial.println("Dropping Food for");
  myStepper.step(stepsPerRevolution);
  myStepper.step(stepsPerRevolution);
  Firebase.setString(firebaseData, "/Flutter_ESP_Actions/Food/food", "off");
  Serial.println("Done...");
    }
  delay(1000);
  //Firebase.setString(firebaseData, "/Flutter_ESP_Actions/Food/food", "off");

  // step one revolution in the other direction:
  //Serial.println("counterclockwise");
  //myStepper.step(-stepsPerRevolution);
  //delay(1000);
}
