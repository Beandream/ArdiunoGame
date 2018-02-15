#define RED 5
#define GREEN 6
#define BLUE 7
int buttonApin = 2;
int buttonBpin = 3;
int buttonCpin = 4;
int ledPinRED = 10;
int ledPinGREEN = 9;
int ledPinBLUE = 8;
int score;
int difficulty = 3;
int color = 0;
int start = 0;
int delaytime = 1000;

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite (ledPinRED, LOW);
  digitalWrite (ledPinGREEN, LOW);
  digitalWrite (ledPinBLUE, LOW);
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonCpin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print("helloworld");
  Serial.print("\n");
  randomSeed(analogRead(0));
}

void loop()
{
  if (start == 0) {
    if (digitalRead(buttonApin) == LOW){ difficulty = 0; gameStart();}
    if (digitalRead(buttonBpin) == LOW){ difficulty = 1; gameStart();}
    if (digitalRead(buttonCpin) == LOW){ difficulty = 2; gameStart();}
  }
}
void scoreCheck() {
  if (score < 6 && score > 0) {
    digitalWrite (ledPinRED, LOW);
    digitalWrite (ledPinGREEN, LOW);
    digitalWrite (ledPinBLUE, HIGH);
  }

  if (score > 5 && score < 11) {
    digitalWrite (ledPinRED, LOW);
    digitalWrite (ledPinGREEN, HIGH);
    digitalWrite (ledPinBLUE, LOW);
  }

  if (score > 10 && score < 15) {
    digitalWrite (ledPinRED, HIGH);
    digitalWrite (ledPinGREEN, LOW);
    digitalWrite (ledPinBLUE, LOW);
  }

  if (score > 15 && difficulty < 2) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    digitalWrite (ledPinRED, HIGH);
    digitalWrite (ledPinGREEN, HIGH);
    digitalWrite (ledPinBLUE, HIGH);
    delay(5000);
  }
}
void blinkColor() {
  if (color == 1) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    delay(50);
    ledOff();
    checkForHit();
  }
  if (color == 2) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    delay(50);
    ledOff();
    checkForHit();
  }
  if (color == 3) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
    delay(50);
    ledOff();
    checkForHit();
  }
}
void missedPoint() {
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite (ledPinRED, HIGH);
  digitalWrite (ledPinGREEN, HIGH);
  digitalWrite (ledPinBLUE, HIGH);
  delay (400);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite (ledPinRED, LOW);
  digitalWrite (ledPinGREEN, LOW);
  digitalWrite (ledPinBLUE, LOW);
  score = 0;
  color = 0;
  start = 0;
  difficulty = 3;
  delaytime = 1000;
  delay(1000);
}
void hitPoint() {
  if (difficulty == 0){delaytime -= 35;}
  if (difficulty == 1){delaytime -= 45; Serial.print(delaytime); Serial.print("\n");}
  if (difficulty == 2){delaytime  /= 1.05; Serial.print(delaytime); Serial.print("\n");}
  score += 1;
  scoreCheck();
  delay(1000);
  colorPicker();
  color = 0;
}
void checkForHit() {
  for (int i = 0; i <= delaytime; i++) {
    delay(1);
    if (color == 1) {
      if (digitalRead(buttonApin) == LOW) {
        hitPoint();
        return;
      }
      else if (digitalRead(buttonBpin) == LOW || digitalRead(buttonCpin) == LOW) {
        Serial.print("WrongPoint");
        missedPoint();
        return;
      }
    }

    if (color == 2) {
      if (digitalRead(buttonBpin) == LOW) {
        hitPoint();
        return;
      }
      else if (digitalRead(buttonApin) == LOW || digitalRead(buttonCpin) == LOW) {
        Serial.print("WrongPoint");
        missedPoint();
        return;
      }
    }

    if (color == 3) {
      if (digitalRead(buttonCpin) == LOW) {
        hitPoint();
        return;
      }
      else if (digitalRead(buttonApin) == LOW || digitalRead(buttonBpin) == LOW) {
        Serial.print("WrongPoint");
        missedPoint();
        return;
      }
    }
  }
  Serial.print("\n");
  Serial.print("waitedTooLong");
  Serial.print("\n");
  missedPoint();
}
void ledOff() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}
void colorPicker() {
  color = random(1, 4);
  Serial.print(score);
  Serial.print(" <score");
  Serial.print("\n");
  blinkColor();
}
void gameStart(){
  Serial.print ("GameStarted");
  Serial.print ("\n");
  delay(1000);
  colorPicker();
  start = 1;
}


