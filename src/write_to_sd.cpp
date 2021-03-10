#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define cardSelect 4

File logfile; 

// blink out an error code
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}

char filename[15];

void setup() {
     
    Serial.begin(115200); 
    if (!SD.begin(cardSelect)){
        Serial.println("Card init. failed!");
        error(2);
    }

    // create filename
    strcpy(filename,"/ANALOG00.TXT");
    for (uint8_t i = 0; i < 100; i++) {
        filename[7] = '0' + i/10;
        filename[8] = '0' + i%10;
        // create if does not exist, do not open existing, write, sync after write
        if (! SD.exists(filename)) {
            break;
        }
    }


    // create file 

    logfile = SD.open(filename, FILE_WRITE);
    if( ! logfile ) {
        Serial.print("Couldnt create "); 
        Serial.println(filename);
        error(3);
    }
    Serial.print("Writing to "); 
    Serial.println(filename);

    Serial.println("Ready!");
    logfile.close();

    
}

void loop() { 
  logfile = SD.open(filename, FILE_WRITE);
  logfile.println(millis());
  Serial.println(millis());
  delay(100);
  logfile.close();
}



    