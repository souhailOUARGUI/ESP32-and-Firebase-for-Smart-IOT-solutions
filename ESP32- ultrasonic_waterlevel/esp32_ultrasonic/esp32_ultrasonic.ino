#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <FirebaseESP32.h>

int trigger_pin = 5;
int echo_pin   = 18;

// Replace with your network credentials
const char* ssid = "IRVING2";
const char* password = "Intimacy@5$?@GranAda9";
#define FIREBASE_Authorization_key "tpggs7qUBY2N9Zg8AWRCOXb6eWYAROVWuv1iKRyj"
#define FIREBASE_HOST "dog-house-f1317-default-rtdb.firebaseio.com"
String val = "null";// variable to store the sensor value


FirebaseData firebaseData;
FirebaseJson json;

String page = "";
int distance_cm;

void setup() {
  Serial.begin(115200);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  delay(500);

  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  
  
  
}

void loop() {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  long duration = pulseIn(echo_pin, HIGH);
  distance_cm = (duration / 2) / 29.09;
  Serial.println(distance_cm);

  if (distance_cm>=11){ val = "Empty"; Serial.println(val); } 
  else if (distance_cm>=7 && distance_cm<11){ val = "low"; Serial.println(val); }
  else if (distance_cm>=4 && distance_cm<7){ val = "Medium"; Serial.println(val); }
  else if (distance_cm<4){ 
  val = "High";  Serial.println(val); 
  }

  
  Firebase.setString(firebaseData, "/ESP32_APP/WATER/WaterLevel", val);

  
  delay(300);
}
