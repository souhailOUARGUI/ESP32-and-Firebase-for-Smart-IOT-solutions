void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
     Serial.begin(9600);
   Serial.println("Reading From the Sensor");
}
// put your main code here, to run repeatedly:

  void loop() {
  
 
  
   
   
      digitalWrite(5,HIGH);
     
     delay(2000);
            digitalWrite(5,LOW);
    
    delay(2000);
}
