#include <FirebaseESP32.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiClient.h>

//#define FIREBASE_HOST "dog-house-f1317-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "AIzaSyCDqxx2swJ7U0cMYZUS0QQ4fZSsGwG4QOM"
//#define WIFI_SSID "IRVING2" // Tên wifi của bạn
//#define WIFI_PASSWORD "Intimacy@5$?@GranAda9" // Password wifi của bạn
#define DHTPIN 4    
#define DHTTYPE DHT11

#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

#define WIFI_SSID "IRVING2"
#define WIFI_PASSWORD "Intimacy@5$?@GranAda9"



/* 2. Define the API Key */
#define API_KEY "AIzaSyCDqxx2swJ7U0cMYZUS0QQ4fZSsGwG4QOM"

/* 3. Define the RTDB URL */
#define DATABASE_URL "dog-house-f1317-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "ouargui550@gmail.com"
#define USER_PASSWORD "11111111"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;


unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

DHT dht(DHTPIN, DHTTYPE);
void setup()
{

  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  
  Firebase.begin(&config, &auth);

  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

}







void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Đọc nhiệt độ theo độ C

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;

  }

  Serial.print("temperature: ");
  Serial.print(t);
  Serial.print("*C  ");
  Serial.print("humidity: ");
  Serial.print(h);
  Serial.println("%  ");

  Firebase.setFloat( fbdo,F("test/temperature"), t);

  Firebase.setFloat ( fbdo,F("test/humidity"), h);

  delay(200);

}
