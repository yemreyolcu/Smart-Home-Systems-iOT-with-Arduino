#include <Password.h>
#include <Keypad.h>
#include <Wire.h>

#include <LiquidCrystal.h>

Password password = Password( "1234" );
const int yesilled=49;
const int kirmiziled=48;

//LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define FlamePin A0
#define buzzer 13

#define LM35_Pin A1
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

const byte satir = 4;   
const byte sutun = 3;
int position = 0;

char tus_takimi[satir][sutun] = {   
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte satirPin[satir] = { 30,31,32,33 };
byte sutunPin[sutun] = { 29,28,27 };

Keypad keypad = Keypad( makeKeymap(tus_takimi), satirPin, sutunPin, satir, sutun );

int pirPin = 8; //the digital pin connected to the PIR sensor's output 
int ledPin = 21;

void setup() {
   //
     pinMode(yesilled,OUTPUT);
    pinMode(kirmiziled,OUTPUT);
    keypad.addEventListener(keypadEvent); 
   //lcd.begin(16, 2);
   pinMode(FlamePin, INPUT_PULLUP);
   pinMode(buzzer, OUTPUT);
    /*lcd.setCursor(5, 0);
    lcd.print("FLAME");
    lcd.setCursor(3, 1);
    lcd.print("DETECTOR");*/
    delay(1000);
    //lcd.clear();
    ///PIR
    ////
    pinMode(pirPin, INPUT); 
   pinMode(ledPin, OUTPUT);
   digitalWrite(pirPin, LOW);
   //
   //pinMode(LM35_Pin, INPUT_PULLUP);
   float newtemp;
  Serial.begin(9600);
  analogReference(INTERNAL1V1);
  lcd.begin(28,4);
  delay(1000);
  lcd.clear();
   
}

void loop() {
//



//
int Flame = digitalRead(FlamePin);

if(Flame==HIGH)
{
  digitalWrite(buzzer, HIGH);
  delay(200);
  
}
else
{
 digitalWrite(buzzer, LOW); 
}
///PIR
if(digitalRead(pirPin) == HIGH){
     digitalWrite(ledPin, HIGH);
  }
if(digitalRead(pirPin) == LOW){
    digitalWrite(ledPin, LOW);
  }
 //
 
  float temp = analogRead(LM35_Pin);
  float newtemp = temp*1100/(1024*10);
 if(newtemp > 30){
    lcd.setCursor(0,0);
    lcd.print("SICAKLIK: ");
    lcd.print(newtemp);
    lcd.println("*C");
    lcd.setCursor(0,1);
    lcd.println("Sicaklik Artti!");
    //delay(50);
    //lcd.clear();
    
    
    
    }
  else if(newtemp < 20){
    lcd.setCursor(0,0);
    lcd.print("SICAKLIK: ");
    lcd.print(newtemp);
    lcd.println("*C");
    lcd.setCursor(0,1);
    lcd.println("Sicaklik Azaldi!");
    //delay(50);
    //lcd.clear();
    
    

  }
  else {
    
    lcd.setCursor(0,0);
    lcd.print("SICAKLIK : ");
    lcd.print(newtemp);
    lcd.println("*C");
    delay(500);
    lcd.clear();
    
  }
 //
 keypad.getKey();
  

}
void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState())
     {
    case PRESSED:
 
  switch (eKey){
    case '*': checkPassword();  break; 
    case '#': password.reset(); break; 
    default: password.append(eKey);
     }
  }
}

void checkPassword(){
  if (password.evaluate()){
    
    digitalWrite(yesilled,HIGH);
    digitalWrite(kirmiziled,LOW);
                          }
  else
  {
    
    digitalWrite(kirmiziled,HIGH);
    digitalWrite(yesilled,LOW);
  }
}
