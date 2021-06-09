#include <Arduino.h>

#define ANALOG_MOISTURE_MIN 440
#define ANALOG_MOISTURE_MAX 850

#define RED_LED D5
#define GREEN_LED D6
#define BLUE_LED D7

int optimal_min = 50;
int optimal_max = 60;

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void reset() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void loop() {
  int analog_moisture_val = analogRead(A0);
  int moisture_val = map(analog_moisture_val, ANALOG_MOISTURE_MIN,
                         ANALOG_MOISTURE_MAX, 100, 1);

  Serial.printf("Moisture sensor reading: %d\n", moisture_val);

  reset();

  if (moisture_val < optimal_min) {
    digitalWrite(RED_LED, HIGH);
  } else if (moisture_val > optimal_max) {
    digitalWrite(BLUE_LED, HIGH);
  } else {
    digitalWrite(GREEN_LED, HIGH);
  }

  delay(500);
}