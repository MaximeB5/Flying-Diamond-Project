// Pins
const int PIN_TRIGGER = 2; // Digital 2
const int PIN_ECHO    = 3; // Digital 3

// Timeout : time required before considering an obstacle ( = no measurement before)
// 4m going, 4m coming = ~8m
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

// Speed of the sound in the air
// mm/µs because the time measurement is performed in µs and we want a result in mm
const float SOUND_SPEED = 340.0 / 1000;

void setup() {
  // Serial port
  Serial.begin(115200);

  // Pins
  pinMode(PIN_TRIGGER, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Write during 10µs on the Trigger pin in order to send an eight cycle sonic burst at 40 kHZ (cf. HC SR04 datasheet)
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Get the time between sending the pulse and the echo if the echo exists
  long time_measurement = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);

  // Get the distance from the time measurement ( / 2.0 because it includes going and coming)
  float distance_mm = time_measurement / 2.0 * SOUND_SPEED;

  // Print data
  Serial.print(F("Distance: "));
  Serial.print(distance_mm);
  Serial.print(F("mm ("));
  Serial.print(distance_mm / 10.0, 2);
  Serial.print(F("cm, "));
  Serial.print(distance_mm / 1000.0, 2);
  Serial.println(F("m)"));

  // Delay
  delay(500);
}
