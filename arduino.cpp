Added reset after 20s
// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int redLedPin = 11;
const int buzzerPin = 3;
const int greenLedPin = 4;
// defines variables
long duration;
int distance;

int sequenceTracker = 1;
int state = -1;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  
}

void resting() {
  digitalWrite(greenLedPin, HIGH);
}

void missingCupSequence() {
  // noTone(buzzerPin);
  // digitalWrite(buzzerPin, LOW);
  int interval = 200;
  // RED LED ON and BUZZER ON
      digitalWrite(buzzerPin, HIGH);
    tone(buzzerPin, 2000);
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);
  delay(interval);
  // No RED and BUZZER
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  delay(interval);
  // RED LED ON and BUZZER ON
      digitalWrite(buzzerPin, HIGH);
    tone(buzzerPin, 2000);
  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);
  delay(interval);
  // No RED and BUZZER
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  noTone(buzzerPin);
  digitalWrite(buzzerPin, LOW);
  delay(interval);
}

void drinkWater() {
  if (state == 3) {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    delay(20000);
    state = -1;
    return;
  }
    // Clears the trigPin
  digitalWrite(redLedPin, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");

  if (distance < 6) { // If cup is on
    if (state == -1) {
      state = 0;
    } else if (state == 1) {
      state = 3;
    } else {
    digitalWrite(buzzerPin, HIGH);
    tone(buzzerPin, 2000);
    delay(500);
    noTone(buzzerPin);
    digitalWrite(buzzerPin, LOW);
    delay(500);
    }
  } else { // Cup is off
    if (state == 0) {
      state = 1;
    }
    if (sequenceTracker == 1) {
      missingCupSequence();
      sequenceTracker = 0;
    } else {
      digitalWrite(redLedPin, LOW);
      delay(1500);
      sequenceTracker = 1;
    }
  }
}
void loop() {
  // resting();
  drinkWater();
}
void buzzOnContact() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance < 6) {
    digitalWrite(buzzerPin, HIGH);

    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, HIGH);
    tone(buzzerPin, 2000);
    
    Serial.print("LED ON");
  } else {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    noTone(buzzerPin);

    digitalWrite(buzzerPin, LOW);
  }
  delay(700);
}
