#include <FirebaseESP32.h>
#include  <WiFi.h>


#define FIREBASE_HOST "dog-house-f1317-default-rtdb.firebaseio.com"
#define WIFI_SSID "IRVING2" // Change the name of your WIFI
#define WIFI_PASSWORD "Intimacy@5$?@GranAda9" // Change the password of your WIFI
#define FIREBASE_Authorization_key "tpggs7qUBY2N9Zg8AWRCOXb6eWYAROVWuv1iKRyj"


FirebaseData firebaseData;
FirebaseData firebaseData1;
FirebaseJson json;


byte pump1 = 5;
byte pump2 = 10;
void setup() {
 Serial.begin(9600);
 //while (!Serial);
 pinMode(pump1, OUTPUT); // variant low/high
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
  Firebase.getString(firebaseData1, "/Flutter_ESP_Actions/Water/water");

if (firebaseData1.stringData() == "on") { 
    Serial.println("Dropping Wtaer ");
  digitalWrite(pump1, HIGH); // pump1 deactivated
  delay(4000);
   Firebase.setString(firebaseData, "/Flutter_ESP_Actions/Water/water", "off");
  digitalWrite(pump1, LOW); // pump1 activated
  Serial.println("Done...");
    }
  delay(500);
 
}
