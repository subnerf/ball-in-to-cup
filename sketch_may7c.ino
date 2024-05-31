#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

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
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    move_forward(); // Call the function to move forward
    irrecv.resume();
  }
}