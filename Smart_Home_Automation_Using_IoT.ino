#define BLYNK_TEMPLATE_ID           "TMPLa0UCB-3b"
#define BLYNK_DEVICE_NAME           "Home Automation System"
#define BLYNK_AUTH_TOKEN            "LYaF85nA4CovgWy1NKGkE5r9gwj-rxGy"

#include <BlynkSimpleStream.h>
#include <LiquidCrystal.h>
#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;

Servo myservo;
const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int lampPin = 13, ledPin = 12, fanPin = 11, trigPin = 10, echoPin = 7;
int ldrSensorPin = A0;
int ldrSensorValue = 1;
int pinData1 = 0, pinData2 = 0, pinData3 = 0, pinData4 = 0;

void setup() {
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  pinMode(lampPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ldrSensorPin, INPUT);
  lcd.begin(16, 2);
  myservo.attach(6);
}

BLYNK_WRITE(V1) {  // Button Widget is writing to pin V1
  pinData1 = param.asInt();
  if (pinData1 == 1) {  // turn the lampPin on
    digitalWrite(lampPin, HIGH);
  }
  else {  // turn the lampPin off
    digitalWrite(lampPin, LOW);
  }
}

BLYNK_WRITE(V2) {  // Button Widget is writing to pin V2
  pinData2 = param.asInt();
  if (pinData2 == 1) {  // turn the ledPin on
    digitalWrite(ledPin, HIGH);
  }
  else {  // turn the ledPin off
    digitalWrite(ledPin, LOW);
  }
}

BLYNK_WRITE(V3) {  // Button Widget is writing to pin V3
  pinData3 = param.asInt();
  if (pinData3 == 1) {  // turn the fanPin on
    digitalWrite(fanPin, HIGH);
  }
  else {  // turn the fanPin off
    digitalWrite(fanPin, LOW);
  }
}

BLYNK_WRITE(V4) {  // Button Widget is writing to pin V4
  pinData4 = param.asInt();
  if (pinData4 == 1) {  // turn all devices on
    digitalWrite(lampPin, HIGH);
    digitalWrite(ledPin, HIGH);
    digitalWrite(fanPin, HIGH);
  }
  else {  // turn all devices off
    digitalWrite(lampPin, LOW);
    digitalWrite(ledPin, LOW);
    digitalWrite(fanPin, LOW);
  }
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.412;
  if (distance > 200) {
    lcd.setCursor(0, 0);
    lcd.print("WELCOME!");
    lcd.setCursor(0, 2);
    lcd.print("DISTANCE:");
    lcd.print(">200cm");
  }
  else if ((distance <= 200) || (distance > 100)) {
    lcd.setCursor(0, 0);
    lcd.print("PLEASE ENTER");
    lcd.setCursor(0, 2);
    lcd.print("DISTANCE:");
    lcd.print(distance);
    lcd.print("cm");
  }
  if (distance >= 200) {
    myservo.write(120);
  }
  else {
    myservo.write(0); 
  }
  Serial.print("distance");
  Serial.println(distance);
  ldrSensorValue = analogRead(ldrSensorPin);
  if ((pinData1 == 0) && (pinData4 == 0)) {
    if (ldrSensorValue <= 450) {  // turn the lampPin on
      digitalWrite(lampPin, HIGH);
    }
    else {  // turn the lampPin off
      digitalWrite(lampPin, LOW);
    }
  }
  Blynk.run();
}
