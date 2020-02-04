#include <LiquidCrystal.h>         

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Digital pins to which you connect the LCD
const int inPin1 = A1; // A0 is where you connect the sensor
const int inPin2 = 2;
//const int lm35_pin = A1;
int In1 = 7;
int In2 = 8;
int ENA = 6;
int speed = 255;
float setTemp = 35;
void setup()
{
  lcd.begin(16,2);
    pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(ENA, OUTPUT);
  digitalWrite(In1 , LOW);
  digitalWrite(In2 , HIGH);
  analogWrite(ENA, speed);
  Serial.begin(9600);
}
void loop()
{
  int value = analogRead(inPin1); // read the value from the sensor
  //int val = analogRead(inPin2);
  
  lcd.setCursor(0,1);
  float millivolts = (value / 1024.0) * 5000; 
  float celsius = millivolts / 10;
  float temp_val = celsius;
  lcd.setCursor(0,1);
    if(temp_val > setTemp){
      digitalWrite(In1 , LOW);
      digitalWrite(In2 , HIGH);
      lcd.setCursor(0,1);
      lcd.print("It's more!!");
  }
  if(temp_val < setTemp){
      digitalWrite(In1 , HIGH);
      digitalWrite(In2 , LOW);
      lcd.setCursor(0,1);
      lcd.print("It's less!!");
  }
  //float millivolts2 = (val / 1024.0) * 5000; 
  //float celsius2 = millivolts2 / 10;
   Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" Degree Celsius\n");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp1 = ");
  lcd.print(celsius);
  lcd.print("C");
  lcd.setCursor(0,1);
  //lcd.print("Temp2 = ");
  //lcd.print(celsius2);
  //lcd.print("C");
  if(temp_val > setTemp){
    lcd.print("It's more!!"); 
  }
  else{
     lcd.print("It's less!!");
  }
  //lcd.print("F");
  delay(1000);
} 
