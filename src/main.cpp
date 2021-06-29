#include <Arduino.h>
#include <ESP8266WiFi.h>

#define ANALOG_MOISTURE_MIN 440
#define ANALOG_MOISTURE_MAX 850

#define RED_LED D5
#define GREEN_LED D6
#define BLUE_LED D7
#define PUMP_PIN D1

int optimal_min = 30;
int optimal_max = 70;

int pump_time = 5000;

void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(PUMP_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(PUMP_PIN, LOW);

  digitalWrite(PUMP_PIN, HIGH);
  delay(2000);
  digitalWrite(PUMP_PIN, LOW);
}

void reset() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

int get_moisture() {
  int analog_moisture_val = analogRead(A0);
  int val = map(analog_moisture_val, ANALOG_MOISTURE_MIN, ANALOG_MOISTURE_MAX,
                100, 1);

  Serial.printf("Moisture sensor reading: %d\n", val);

  return val;
}

void pump() {
  int i = 0;
  while (get_moisture() < optimal_max && i++ < 20) {
    digitalWrite(PUMP_PIN, HIGH);
    delay(pump_time);
    digitalWrite(PUMP_PIN, LOW);
    delay(pump_time * 2);
  }
}

void loop() {
  int moisture_val = get_moisture();

  reset();

  if (moisture_val < optimal_min) {
    digitalWrite(RED_LED, HIGH);
    pump();
  } else if (moisture_val > optimal_max) {
    digitalWrite(BLUE_LED, HIGH);
  } else {
    digitalWrite(GREEN_LED, HIGH);
  }

  delay(1000);
}