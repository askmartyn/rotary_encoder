#include <LiquidCrystal.h>
#define setbit(data,b) (data|=(1<<b)) //set the b bit of data to 1
#define clrbit(data,b) (data&=~(1<<b)) //set the b bit of data to 0

uint8_t code8421 = 0;
const uint8_t code8Pin = 5;
const uint8_t code4Pin = 4;
const uint8_t code2Pin = 3;
const uint8_t code1Pin = 2;
const int rs = 18, en = 19, d4 = 14, d5 = 15, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  Serial.println("8421 Encoder Starts up!");
  pinMode(rs, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
  //LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  lcd.begin(8,2);
  lcd.clear();
  lcd.print("Hello world");
  pinMode(code8Pin, INPUT);
  pinMode(code4Pin, INPUT);
  pinMode(code2Pin, INPUT);
  pinMode(code1Pin, INPUT);
}

void loop() {
  //According to the pin level and set the corresponding bit to 0 or 1
  if (digitalRead(code8Pin) == HIGH){
    setbit(code8421, 3);
  }else{
    clrbit(code8421, 3);
  }

  if (digitalRead(code4Pin) == HIGH){
    setbit(code8421, 2);
  }else{
    clrbit(code8421, 2);
  }

  if (digitalRead(code2Pin) == HIGH){
    setbit(code8421, 1);
  }else{
    clrbit(code8421, 1);
  }

  if (digitalRead(code1Pin) == HIGH){
    setbit(code8421, 0);
  }else{
    clrbit(code8421, 0);
  }

  //Output the code in hexadecimal 
  Serial.print("Now code8421 is:  ");
  Serial.println(String(code8421, HEX));
  switch (code8421) {
    case 0:
     sendToScreen("Hi Everyone");
     break;
    case 1:
     sendToScreen("Alex here!");
     break;
    case 2:
     sendToScreen("I'd just");
     break;
    case 3:
     sendToScreen("like to take");
     break;
    case 4:
     sendToScreen("a moment");
     break;
    case 5:
     sendToScreen("to thank");
     break;
    case 6:
     sendToScreen("some of");
     break;
    case 7:
     sendToScreen("our patreons");
     break;
    default:
     sendToScreen("");
  }
}

void sendToScreen(String message) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(message);  
  delay(100);
}
