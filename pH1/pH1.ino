#include<Arduino.h>

const int analogInPin = 34; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10], temp=0;

void setup() {
    Serial.begin(115200);
}

void loop() {
    // Read 10 samples from the pH sensor
    for(int i = 0; i < 10; i++) { 
        buf[i] = analogRead(analogInPin);
        delay(100); // Delay between readings
    }

    // Sort readings to remove outliers
    for(int i = 0; i < 9; i++) {
        for(int j = i + 1; j < 10; j++) {
            if(buf[i] > buf[j]) {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }

    // Calculate the average of the middle 8 sorted readings
    avgValue = 0;
    for(int i = 2; i < 8; i++) {
        avgValue += buf[i];
    }

    // Convert the average value to voltage
    float sensorpH = ((float)avgValue * 3.30 / 4095 );
    float actualpH = ((0.795*sensorpH)-1.63);


Serial.print("ph: ");
    Serial.println(actualpH,1);

    

    delay(100); // Wait for 1 second before next reading
}