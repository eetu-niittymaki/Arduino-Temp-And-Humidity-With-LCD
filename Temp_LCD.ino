#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

//DHT Sensor:
#define SensorPin 4
#define DHTTYPE DHT22

DHT dht(SensorPin, DHTTYPE);

//Read temp and hum every 10 seconds
const long readInterval = 10000;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //set I2C Address as 0x3F

byte LT[8] =
{
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte UB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
byte RT[8] =
{
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte LL[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
};
byte LB[8] =
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};
byte LR[8] =
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
};
byte UMB[8] =
{
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};
byte LMB[8] =
{
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111
};

void setup() {
  Serial.begin(9600);
  lcd.begin(20,4);
  dht.begin();

  lcd.createChar(1, UB);
  lcd.createChar(2, RT);
  lcd.createChar(3, LL);
  lcd.createChar(4, LB);
  lcd.createChar(5, LR);
  lcd.createChar(6, UMB);
  lcd.createChar(7, LMB);
  lcd.createChar(8, LT);

  getTemp();
}

void num0(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(8);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x, y + 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
}

void num1(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x + 1, y + 1);
  lcd.write(255);
}

void num2(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, y + 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(7);
}

void num3(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(6);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, y + 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void num4(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(3);
  lcd.write(4);
  lcd.write(255);
  lcd.setCursor(x + 2, y + 1);
  lcd.write(255);
}

void num5(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(255);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, y + 1);
  lcd.write(7);
  lcd.write(7);
  lcd.write(5);
}

void num6(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(8);
  lcd.write(6);
  lcd.write(6);
  lcd.setCursor(x, y + 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void num7(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(1);
  lcd.write(1);
  lcd.write(2);
  lcd.setCursor(x + 1, y + 1);
  lcd.write(8);
}

void num8(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x, y + 1);
  lcd.write(3);
  lcd.write(7);
  lcd.write(5);
}

void num9(int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(8);
  lcd.write(6);
  lcd.write(2);
  lcd.setCursor(x + 2, y + 1);
  lcd.write(255);
}

/*
typedef void (*funcs) (int x, int y);

funcs functions[10] = {
  num0,
  num1,
  num2,
  num3,
  num4,
  num5,
  num6,
  num7,
  num8,
  num9,
};

void types(String a) { Serial.println("it's a String"); }
void types(int a) { Serial.println("it's an int"); }
void types(char *a) { Serial.println("it's a char*"); }
void types(float a) { Serial.println("it's a float"); }
void types(bool a) { Serial.println("it's a bool"); }
*/
void getTemp() {
  int row = 4;
  int col = 0;
  int temp = dht.readTemperature();
  int hum = dht.readHumidity();
  float f = dht.readTemperature(true);

  lcd.clear();

  // Write minus sign if negative
  if ((temp <= 0 && temp > -10) || (hum <= 0 && temp >= -9)) {
    lcd.setCursor(row + 2, col);
    lcd.write(4);
  } else if (temp >= -10 && temp < 0) {
    lcd.setCursor(row, col);
    lcd.write(4);
  } else if (temp <= -10) {
    lcd.setCursor(row - 2, col);
    lcd.write(4);
    row -= 4;
  } else if (temp <= 9 && temp >= 0) { // Adds extra space if temp is a one digit number
    row += 4;
  }

  String strTemp = String(temp);
  String strHum = String (hum);
  float hi = dht.computeHeatIndex(f, hum);
  int feelsLike = round(dht.convertFtoC(hi));

  // Temp
  for (int i = 0; i < strTemp.length(); i++) {
      switch (strTemp[i]) {
        case '0':
          num0(row, col);
          break;
        case '1':
          num1(row, col);
          break;
        case '2':
          num2(row, col);
          break;
        case '3':
          num3(row, col);
          break;
        case '4':
          num4(row, col);
          break;
        case '5':
          num5(row, col);
          break;
        case '6':
          num6(row, col);
          break;
        case '7':
          num7(row, col);
          break;
        case '8':
          num8(row, col);
          break;
        case '9':
          num9(row, col);
          break;
      }
    row += 4;
  }

  lcd.setCursor(row - 1, col);
  lcd.write("C");

  col += 2;
  row = 4;

  // Humidity
  for (int i = 0; i < strHum.length(); i++) {
    switch (strHum[i]) {
      case '0':
        num0(row, col);
        break;
      case '1':
        num1(row, col);
        break;
      case '2':
        num2(row, col);
        break;
      case '3':
        num3(row, col);
        break;
      case '4':
        num4(row, col);
        break;
      case '5':
        num5(row, col);
        break;
      case '6':
        num6(row, col);
        break;
      case '7':
        num7(row, col);
        break;
      case '8':
        num8(row, col);
        break;
      case '9':
        num9(row, col);
        break;
    }
    row += 4;
  }

  lcd.setCursor(row - 1, col);
  lcd.write("%");

  lcd.setCursor(row+1, col-2);
  lcd.write("Feels");
  lcd.setCursor(row+1, col-1);
  lcd.write("Like:");
  lcd.setCursor(row+2, col);
  lcd.print(feelsLike);

  row = 0;
  col = 0;
}

void loop() {
  getTemp();
  delay(readInterval);
}
