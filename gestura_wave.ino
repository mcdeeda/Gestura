const int pingPin = 8; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 9; // Echo Pin of Ultrasonic Sensor
const int numReadings = 10;

int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   for (int thisReading = 0; thisReading < numReadings; thisReading++){
    readings[thisReading] = 0;
   }
}

void loop() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   total -= readings[readIndex];
   readings[readIndex] = duration;
   total += readings[readIndex];
   readIndex += 1;

   if (readIndex >= numReadings){
    readIndex = 0;
   }

   average = total / numReadings;
   Serial.println(average);
   delay(10);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
