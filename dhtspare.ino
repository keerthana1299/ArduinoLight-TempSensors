#include<SoftwareSerial.h>
#include <dht.h>
#include<math.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define dht_apin A1     // what pin we're connected to
#define pwm 9

dht DHT;

byte degree[8] =
{
  0b00011,
  0b00011,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
int sensorPin = A0;
int sensorValue = 0;
int led = 8;
void setup()
{
  //Initialize serial port
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  lcd.begin(16, 2);
  lcd.createChar(1, degree);
  lcd.clear();
  lcd.print("  Greenhouse");
  lcd.setCursor(0, 1);
  lcd.print("  Controlling ");
  delay(2000);
  analogWrite(pwm, 255);
  lcd.clear();
  delay(2000);
}

void loop()
{
  lcd.clear();
  DHT.read11(dht_apin);
  Serial.println("Temp in C");
  Serial.println(DHT.temperature);
  lcd.print(DHT.temperature);
  //Print degree symbol
  lcd.print(" C ");

Serial.println("Humidity %");
  Serial.println(DHT.humidity);
  lcd.print(DHT.humidity);
  lcd.print(" %Hum");
  sensorValue = analogRead(sensorPin);
  Serial.println("Light Intensity ");
  Serial.println(sensorValue);
  lcd.setCursor(0, 1);
  if (DHT.temperature < 30 )
  {
    analogWrite(9, 0);
    lcd.print("Fan OFF            ");
    delay(100);
  }
  else if (DHT.temperature > 30)
  {
    analogWrite(pwm, 255);
    lcd.print("Fan ON   ");
    delay(100);
  }
  if (sensorValue < 100)
  {
   // lcd.print("Light  on");
    digitalWrite(led, HIGH);
    //delay(3000);
  }
  else
  {
  digitalWrite(led, LOW);
  }
  //2000mS delay between reads
  delay(2000);
}
