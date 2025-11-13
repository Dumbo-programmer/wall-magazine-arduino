#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// === Servo Pins ===
#define servo1 3
#define servo2 10
#define servo3 5
#define servo4 6
#define servo5 9
#define servo6 11

// === Display 1 (Software SPI) ===
#define OLED_MOSI1   4
#define OLED_CLK1    7
#define OLED_DC1     12
#define OLED_CS1     13
#define OLED_RESET1  8

Adafruit_SH1106 display1(OLED_MOSI1, OLED_CLK1, OLED_DC1, OLED_RESET1, OLED_CS1);

Servo s1, s2, s3, s4, s5, s6;

void setup() {
  Serial.begin(9600);
  delay(200);

  // Attach servos
  s1.attach(servo1);
  s2.attach(servo2);
  s3.attach(servo3);
  s4.attach(servo4);
  s5.attach(servo5);
  s6.attach(servo6);

  // Initialize OLED
  display1.begin(SH1106_SWITCHCAPVCC);
  delay(100);
  showCenteredText(display1, "A God of", "the New", "World");
}

void showCenteredText(Adafruit_SH1106 &d, const char *line1, const char *line2, const char *line3) {
  d.clearDisplay();
  d.setTextSize(2);
  d.setTextColor(WHITE);

  int16_t x1, y1, x2, y2, x3, y3;
  uint16_t w1, h1, w2, h2, w3, h3;

  d.getTextBounds(line1, 0, 0, &x1, &y1, &w1, &h1);
  d.getTextBounds(line2, 0, 0, &x2, &y2, &w2, &h2);
  d.getTextBounds(line3, 0, 0, &x3, &y3, &w3, &h3);

  uint16_t totalHeight = h1 + h2 + h3 + 4;
  int16_t y_start = (SCREEN_HEIGHT - totalHeight) / 2;

  int16_t y_line1 = y_start;
  int16_t y_line2 = y_line1 + h1 + 2;
  int16_t y_line3 = y_line2 + h2 + 2;

  int16_t x_line1 = (SCREEN_WIDTH - w1) / 2;
  int16_t x_line2 = (SCREEN_WIDTH - w2) / 2;
  int16_t x_line3 = (SCREEN_WIDTH - w3) / 2;

  d.setCursor(x_line1, y_line1); d.println(line1);
  d.setCursor(x_line2, y_line2); d.println(line2);
  d.setCursor(x_line3, y_line3); d.println(line3);
  d.display();
}

void loop() {
/** if (Serial.available()) {
    String data = Serial.readStringUntil('\n');  // e.g., "S1:90" or "S3:120"
    data.trim();

    int servoNum = data.substring(1, data.indexOf(':')).toInt();
    int angle = data.substring(data.indexOf(':') + 1).toInt();

    switch (servoNum) {
      case 1: s1.write(angle); break;
      case 2: s2.write(angle); break;
      case 3: s3.write(angle); break;
      case 4: s4.write(angle); break;
      case 5: s5.write(angle); break;
      case 6: s6.write(angle); break;
    }

    Serial.print("Moved Servo ");
    Serial.print(servoNum);
    Serial.print(" to ");
    Serial.println(angle);
  }**/



   s1.write(360); 
   delay(460);
     s2.write(360); 
   delay(460);

      s3.write(360); 
   delay(460);

     s4.write(360); 
   delay(460);

     s5.write(360); 
        delay(460);

    s6.write(360); }
