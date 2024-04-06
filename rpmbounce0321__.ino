#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
volatile unsigned int count = 0;
const byte counterPin = 2;
unsigned long count_start;
unsigned int rpm;
const byte magnet_num = 3;
//unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
//const int debounceDelay = 200;   // the debounce time; increase if the output flickers
const unsigned long one_sec = 1000000;

void counter() {
  //if ((micros() - lastDebounceTime) > debounceDelay)
    {
    count++;
    //lastDebounceTime = micros();
     }
}
void setup() {
  lcd.begin(16, 2); // 設定LCD顯示的列數行數
  lcd.setCursor(0, 0); // 設定LCD顯示文字的位置
  lcd.print("RPM= ");
  pinMode(counterPin, INPUT); // 設定arduino的引腳模式至輸入模式
  attachInterrupt(0, counter, FALLING); // 用於設定中斷程序
  count = 0;
  rpm = 0;
  count_start = 0;
}

void loop() {
  static unsigned long timestone = 0;
  static char msg[16] = {0};
  static char msg2[16] = {0};
  static uint16_t frequency = 0;
  if (micros() -  count_start  >= one_sec) {  /* 每秒更新 */
    detachInterrupt(0); // 計算 rpm 時，停止計時  //  cmd();
    // 偵測的格數count * (60 * 1000 / 一圈網格數3）/ 時間差)
    rpm = (60.0 * (float)one_sec / (float)magnet_num ) / ((float)micros() - (float) count_start ) * (float)count;
    frequency = count;
    count = 0;
    count_start = micros();

    attachInterrupt(0, counter, FALLING);
    sprintf(msg, "RPM = %5d", rpm);
    lcd.setCursor(0, 0);
    lcd.print(msg);
    sprintf(msg2, "freq. = %5dHz", frequency);
    lcd.setCursor(0, 1);
    lcd.print(msg2);

  }
}
