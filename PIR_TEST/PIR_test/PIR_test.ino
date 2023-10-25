/*     Arduini PIR Motion Sensor Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
 int calibrationTime = 30;
int pirSensor = 5;
//int relayInput = 7;

void setup() {
   
  Serial.begin(9600);
  Serial.print("Connecting...");
  pinMode(pirSensor, INPUT);
 // pinMode(relayInput, OUTPUT); 
  Serial.println("hello Pir");
  Serial.print("calibrating sensor ");
for(int i = 0; i < calibrationTime; i++)
{ Serial.print("."); delay(1000); }
Serial.println(" done");
Serial.println("SENSOR ACTIVE");
delay(50);
}

void loop() {
  int sensorValue = digitalRead(pirSensor);
  Serial.print("sensor value : ");
  Serial.println(sensorValue);
  delay(1000);

 // if (sensorValue == 1) {
 //   digitalWrite(relayInput, LOW); // The Relay Input works Inversly
 // }
}
