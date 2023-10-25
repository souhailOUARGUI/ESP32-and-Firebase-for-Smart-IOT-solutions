#include "SPIFFS.h"
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
if(!SPIFFS.begin(true)){
Serial.println("An error has occured while mounting SPIFFS");
return;
  }

                  // File TO write
  
  File file = SPIFFS.open("/test.txt",FILE_WRITE);
  if(!file){
Serial.println("Error while opening the file for writing");
return;
  }
  if(file.println("dogInfo { Name : max, age : 2 }")){
  Serial.println("File was written");
  }else{
    Serial.print("File writing failed");
    }
    file.close();

                    // File TO append

  File AppendFile = SPIFFS.open("/test.txt",FILE_APPEND);
  if(!AppendFile ){
Serial.println("Error while opening the file for appending");
return;
  }

  if(AppendFile.println("dogHouseInfo { Name : max's, id : 2 } ")){
  Serial.println("File was appended");
  }else{
    Serial.print("File appending failed");
    }
    AppendFile.close();
    
                        // File reading

    File file2 = SPIFFS.open("/test.txt");
    if(!file2){
      Serial.println("Error while opening the file for reading");
     return;
      }

     Serial.println("File content:");

      while(file2.available()){
        Serial.write(file2.read());
        }
        file2.close();

  Serial.println(SPIFFS.exists("/test.txt"));
  Serial.println(SPIFFS.exists("/nonexistingtest.txt"));      
}

void loop() {
  // put your main code here, to run repeatedly:
 
}
