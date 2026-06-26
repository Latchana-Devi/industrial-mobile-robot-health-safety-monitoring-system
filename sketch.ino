#define GREEN_LED 4
#define YELLOW_LED 5
#define RED_LED 6
#define BUZZER 7
#define BATTERY_PIN A0
#define BUTTON_PIN 3
#define TRIG_PIN 9
#define ECHO_PIN 10

void setup() {
  pinMode(GREEN_LED, OUTPUT);
pinMode(YELLOW_LED, OUTPUT);
pinMode(RED_LED, OUTPUT);
pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance > 50) {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  noTone(BUZZER);
  Serial.println("Status: Safe");
}
else if (distance > 20) {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  tone(BUZZER, 1000);
  Serial.println("Status: Warning");
}
else {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  tone(BUZZER, 2000);
  Serial.println("Status: Emergency - Obstacle Very Close!");

}
int battery = analogRead(BATTERY_PIN);

Serial.print("Battery Level: ");
Serial.println(battery);

if (battery < 300) {
  Serial.println("Warning: Battery Low!");
}
if (digitalRead(BUTTON_PIN) == LOW) {
  Serial.println("******** EMERGENCY STOP ********");
  Serial.println("Robot Stopped");

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  tone(BUZZER, 2500);

  delay(1000);

  noTone(BUZZER);
}
  delay(500);
}
