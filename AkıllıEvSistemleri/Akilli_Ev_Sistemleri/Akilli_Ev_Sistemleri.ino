//* 200201132 - Muhammet Cuneyd Kurtbas ******

#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(48, 49, 50, 51, 52, 53); //RW, E, D4, D5, D6, D7

#define FlamePin A3
#define TempPin A7
#define buzzer 1
#define pirPin 44
#define ledPin 12
#define TrueLedPin 31
#define FalseLedPin 30
#define PressLedPin 29

int TempValue;
int PIRValue = 0;
char myStg[20];
String myStringe = "";

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

char* password = "1453";
int currentposition = 0;

byte rowPins[ROWS] = {37, 38, 39, 40}; //tus takiminin satir pinleri
byte colPins[COLS] = {36, 35, 34}; //tus takiminin sutun pinleri

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
    lcd.begin(16, 2);
    pinMode(FlamePin, INPUT_PULLUP); //sensor input
    pinMode(buzzer, OUTPUT);
    pinMode(pirPin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(TrueLedPin, OUTPUT);
    pinMode(FalseLedPin, OUTPUT);
    pinMode(PressLedPin, OUTPUT);
    delay(1000);
    lcd.clear();
}

void loop() {
    
    if(digitalRead(pirPin) == HIGH) {
        digitalWrite(ledPin, HIGH);
    }

    else if(digitalRead(pirPin) == LOW){                    
        digitalWrite(ledPin, LOW);
      }
      
    int Flame = digitalRead(FlamePin);
    
    if(Flame==HIGH) {
        digitalWrite(buzzer, HIGH);
        lcd.setCursor(5, 0);
        lcd.print("YANGIN");
        lcd.setCursor(3, 1);
        lcd.print("ALGILANDI");
        delay(50);
        lcd.clear();
        delay(50);     
    }
    
    else
    {
     digitalWrite(buzzer, LOW); 
    }

    TempValue = analogRead(TempPin);
    float TempCel = ( TempValue/1024.0)*500;

    if (TempCel>=30){
        lcd.print("SICAKLIK YUKSEK");
        delay(50);
        lcd.clear();
        delay(50); 
    }

    else if(TempCel<=20){
        lcd.print("SICAKLIK DUSUK");
        delay(50);
        lcd.clear();
        delay(50); 
    }

    else{
      String myString = "SICAKLIK (C):";
      lcd.setCursor(0, 0);       
      lcd.print(myString);
      lcd.setCursor(0, 1);
      lcd.print(TempCel);
      delay(50);
      lcd.clear();
      delay(50); 
    }

    char key = keypad.getKey();
    if (key != NO_KEY){
        digitalWrite(PressLedPin, HIGH);
        delay(100);
        digitalWrite(PressLedPin, LOW);
        if(key == password[currentposition]){
            ++currentposition;
            if(currentposition == 4){
                currentposition = 0;
                digitalWrite(TrueLedPin, HIGH);
                digitalWrite(FalseLedPin, LOW);
            }
        }
        
        else{
            currentposition = 0;
            digitalWrite(FalseLedPin, HIGH);
            digitalWrite(TrueLedPin, LOW);
        }
    }
}
