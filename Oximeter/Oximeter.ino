#include <LiquidCrystal.h>

#define alpha 0.2
#define alpha2 0.05

#define n 200

const int rs = 9, en = 7, d4 = 6, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int data[n];

byte bheart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte sheart[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};



void setup()
{
  pinMode(A0, INPUT_PULLUP);
  Serial.begin(38400);

  lcd.begin(16, 2);

  for (int i = 0; i < n; i++)
    data[i] = 0;

  lcd.createChar(0, bheart);
  lcd.createChar(1, sheart);
lcd.clear();
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print("  Eir v2.0");

  lcd.setCursor(0, 1);
  lcd.print("Place your finger");

  delay(3000);

  lcd.clear();
}

float x, y, raw, sum = 0, avg = 0, braw = 0.0, max = 0, bpm = 0.0, lavg = 0.0, conf, lbpm;
int idx = 0;
int f = 1, ct = 0;
long ls = 0, ps = 0, cs = 0;


void loop()
{

  float bpmavg = 0;
  int zt = 0;

  for (int i = 1; i < 12;)
  {

    braw = calRaw();

    if (braw > 2 && f)
    {
      ps = millis() - ls;
      ls = millis();
      f = 0;
      i++;
      bpmavg += bpm;
      bpm = (1000.0 / ps) * 60;
      ct++;


      lcd.setCursor(0, 0);
      lcd.write(byte(1));
      

      conf = abs((1 - ((abs(lbpm - bpm) / lbpm))) * 100);

      lbpm=bpm;
      lcd.setCursor(5, 0);
      lcd.print("conf:");
      lcd.print(conf);
      lcd.print("%");

      lcd.setCursor(0, 1);
      lcd.print("BPM:");
      lcd.print(lavg);

    }

    else if (braw < -0.5)
    {
      f = 1;
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }


    if (millis() - cs >= 60000)
    {
      zt = ct;
      ct = 0;
      cs = millis();
    }

  }

  lavg = bpmavg / 11;


}

float calRaw()
{
  raw = analogRead(A0);
  x  = alpha * raw + (1 - alpha) * x;
  y  = alpha2 * x + (1 - alpha2) * y;

  sum -= data[idx];
  data[idx] = raw;
  sum += raw;

  idx = (idx + 1) % n;

  avg = sum / n;

  return (y - avg);
}
