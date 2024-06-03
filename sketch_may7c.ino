#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long startTime = 0; // Variable to store the start time

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void move_forward() {
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  analogWrite(10, 255);
  digitalWrite(13, HIGH);
  analogWrite(11, 255);
  startTime = millis(); // Store the start time
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (startTime == 0) { // Check if move_forward has not been called yet
      move_forward(); // Call the function to move forward
    }
    irrecv.resume();
  }

  if (startTime != 0 && millis() - startTime > 10000) { // Check if 10 seconds have passed
    // Stop the motors
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    analogWrite(10, 0);
    digitalWrite(13, LOW);
    analogWrite(11, 0);
  }
}
