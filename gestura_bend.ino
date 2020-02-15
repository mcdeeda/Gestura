const int numReadings = 10;
boolean counter = false;

int readings[numReadings]; 
int readings2[numReadings];
int readIndex = 0;             
int total2 = 0;
int total = 0;                 
int average2 = 0;                ;
int average = 0;

int inputPin = A0;
int inputPin2 = A5;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
    readings2[thisReading] = 0;
  }
}

void loop() {
  // subtract the last reading:
  total = total - readings[readIndex];
  total2 = total2 - readings2[readIndex];
  readings[readIndex] = analogRead(inputPin);
  readings2[readIndex] = analogRead(inputPin2);
  total = total + readings[readIndex];
  total2 = total2 + readings2[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  average2 = total2 / numReadings;
  // send it to the computer as ASCII digits
  if(counter){
    
      Serial.println(average);
   }
   else{
    
  Serial.println(average2);
    }
    counter = !counter;
  delay(10);        // delay in between reads for stability
}
