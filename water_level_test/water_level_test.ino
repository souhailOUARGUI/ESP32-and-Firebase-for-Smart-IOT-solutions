
#include <FirebaseESP32.h>
#include  <WiFi.h>
#include "DHT.h"

#define FIREBASE_HOST "dog-house-f1317-default-rtdb.firebaseio.com"
#define WIFI_SSID "IRVING2" // Change the name of your WIFI
#define WIFI_PASSWORD "Intimacy@5$?@GranAda9" // Change the password of your WIFI
#define FIREBASE_Authorization_key "tpggs7qUBY2N9Zg8AWRCOXb6eWYAROVWuv1iKRyj"

#define POWER_PIN  0 // ESP32 pin GIOP17 connected to sensor's VCC pin
#define SIGNAL_PIN 4 // ESP32 pin GIOP36 (ADC0) connected to sensor's signal pin

FirebaseData firebaseData;
FirebaseJson json;


int value = 0;
String val = "Empty";// variable to store the sensor value

void setup() {
  Serial.begin(115200);
  pinMode(POWER_PIN, OUTPUT);   // configure pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
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
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  Serial.print("The water sensor value: ");
  Serial.println(value);

  if (value<=100){ val = "Empty"; Serial.println(val); } 
  else if (value>100 && value<=1500){ val = "Medium"; Serial.println(val); }
  else if (value>1500 && value<=1650){ val = "Medium"; Serial.println(val); }
  else if (value>1700){ 
  val = "High";  Serial.println(val); 
  }


  Firebase.setString(firebaseData, "/ESP32_WATER/waterLevel", val);
  delay(200);
}
