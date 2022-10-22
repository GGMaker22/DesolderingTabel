#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define sensor A0
#define heater 8
#define swStartStop 18
#define swUp 7
#define swDown 6

bool condition = false;
float c1 ;
float TEMPERATURE;
int setTemp = 50;
int buf;



void stopStart()
{
 delay(20);
      condition = !condition;

}
void setup()
{
  pinMode(sensor, INPUT);
  pinMode(heater, OUTPUT);
  pinMode(swStartStop, INPUT_PULLUP);
  pinMode(swUp, INPUT_PULLUP);
  pinMode(swDown, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(swStartStop), stopStart, FALLING);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TempNow:");
  lcd.setCursor(0, 1);
  lcd.print("SetTemp:");
  lcd.setCursor(11, 1);
  lcd.print(setTemp);
}

int temp() // returns temperature in degrees Celsius
{
buf = analogRead(sensor);
TEMPERATURE = 0.0007 * (pow(buf,2)) -0.6724*buf + 192.94; 
   
    return TEMPERATURE;

}



void loop()
{


  if (condition == true)
  {
       digitalWrite(LED_BUILTIN, HIGH);
    if (temp() < setTemp)
    {
      digitalWrite(heater, HIGH);
     delay(3000);
    }
    else
    {
     
      digitalWrite(heater, LOW);
    delay(2000);
    }
    lcd.setCursor(12, 0);
    lcd.print("  ");
    lcd.setCursor(11, 0);
    lcd.print(temp());
    
  }
  if (condition == false)
  {

    if (digitalRead(swUp) == LOW)
    {
      delay(20);
      if (digitalRead(swUp) == HIGH) // SETTEMP +20 Celsius
      {
        setTemp = setTemp + 20;
      }
    }
    if (digitalRead(swDown) == LOW) //// SETTEMP -20 Celsius
    {
      delay(20);
      if (digitalRead(swDown) == HIGH)
      {
        setTemp = setTemp - 20;
      }
    }

    if (setTemp < 30)
    {
      setTemp = setTemp + 240;
    }

    if (setTemp > 250)
    {
      setTemp = setTemp - 240;
    }
    lcd.setCursor(12, 0);
    lcd.print("  ");
    lcd.setCursor(11, 0);
    lcd.print(temp());
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(heater, LOW);
    lcd.setCursor(11, 1);
    lcd.print("   ");
    lcd.setCursor(11, 1);
    lcd.print(setTemp);
  }
}
