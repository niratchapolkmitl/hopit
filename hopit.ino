#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trig = 4; //trig
const int echo = 2; //echo

byte frog_walk[8] = {
  0b00000,
  0b01010,
  0b10101,
  0b11111,
  0b10001,
  0b11111,
  0b11011,
  0b10001
};
byte frog_jump[8] = {
  0b01010,
  0b10101,e
  0b11111,
  0b10001,
  0b11111,
  0b11011,
  0b01010,
  0b00000
};
byte things_top[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b01111,
  0b11111,
  0b11111
};
byte things_below[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01111,
  0b11100,
  0b00111,
  0b00000,
  0b00000
};

int frogY = 1; // 1 walk - 0 jump
bool isJumping = false;
int jumpTimer = 0;
int score = 0;
bool gameOver = false;

//make things
const int Max_things = 3;
int thingsX[Max_things]; // แกนx (0-15)
int thingsY[Max_things]; // แกนy (1 walk - 0 jump)
bool thingActive[Max_things]; // เปิดใช้งานอุปสรรคนั้นๆ

//check hand wave
float getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  long duration = pulseIn(echo, HIGH, 30000); // กันค้าง - timeout 30ms
  if (duration == 0) return 999; //อ่านค่าไม่ได้ให้คืนค่าไกล
  return (duration * 0.0343) / 2.0;
}

void resetGame() {
  score = 0;
  frogY = 1;
  isJumping = false;
  gameOver = false;
  
  for (int i = 0; i < Max_things; i++) {
    thingActive[i] = false;
  }
  
  //random first thing ti show on lcd
  thingsX[0] = 15;
  thingsY[0] = random(0, 2);
  thingActive[0] = true;
}

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  randomSeed(analogRead(0));
  
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, frog_walk);
  lcd.createChar(1, frog_jump);
  lcd.createChar(2, things_top);
  lcd.createChar(3, things_below);
  
  lcd.setCursor(3, 0);
  lcd.print("Frog Hop!");
  lcd.setCursor(2,1);
  lcd.print("Wave to Jump");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (gameOver) {
    lcd.setCursor(3, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(3, 1);
    lcd.print("Score: ");
    lcd.print(score);
    
    if (getDistance() >= 2.0 && getDistance() <= 15.0) {
      resetGame();
      lcd.clear();
      delay(500);
    }
  return;
  }
  
  //read distance
  float dist = getDistance();
  
  //wave hand in 2-15 cm. and  frog isn't jumping
  if (dist >= 2.0 && dist <= 15.0 && !isJumping) {
    isJumping = true;
    frogY = 0; //กระโดดขึ้นแถวบน
    jumpTimer = 0; // รีเซ็ตเวลาลอยตัว
  }
  
  //manage time jumping
  if (isJumping) {
    jumpTimer++;
    if (jumpTimer > 3) {
      frogY = 1; // go down to wallk
      isJumping = false;
    }
  }
  
  // move things
  for (int i = 0; i < Max_things; i++) {
    if (thingActive[i]) {
      thingsX[i]--;
      
      if (thingsX[i] == 1 && frogY == thingsY[i]) {
        gameOver = true;
      }
      
      if (thingsX[i] < 0) {
        thingActive[i] = false;
        score++;
      }
    }
  }
  
  //randoem show things on lcd and check that how far thing go from right panel
  int rightX = 0;
  for (int i = 0; i < Max_things; i++) {
    if (thingActive[i] && thingsX[i] > rightX) {
      rightX = thingsX[i];
    }
  }
  
  //if last things <= 11
  if (rightX <= 11) {
    if (random(0, 100) < 40) { // 40% ที่จะเกิด
      for (int i = 0; i < Max_things; i++) {
        if (!thingActive[i]) {
          thingsX[i] = 15;
          thingsY[i] = random(0, 2); //random top or below
          thingActive[i] = true;
          break;
        }
      }
    }
  }
 
  lcd.clear();

  lcd.setCursor(1, frogY);
  if (frogY == 1) {
    lcd.write((millis() / 150) % 2);
  }
  else {
    lcd.write(1);
  }

  // draw things
  for (int i = 0; i < Max_things; i++) {
    if (thingActive[i] && thingsX[i] >= g0 && thingsX[i] <= 15) {
      lcd.setCursor(thingsX[i],thingsY[i]);
      if (thingsY[i] == 1) {
        lcd.write(2);
      }
      else {
        lcd.write(3);
      }
    }
  }
  
  //show score
  lcd.setCursor(13, 0);
  lcd.print(score);

  delay(200);
}
