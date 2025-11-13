#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// === Display 1 (Software SPI) ===
#define OLED_MOSI1   10
#define OLED_CLK1    9
#define OLED_DC1     12
#define OLED_CS1     13
#define OLED_RESET1  11

Adafruit_SH1106 display1(OLED_MOSI1, OLED_CLK1, OLED_DC1, OLED_RESET1, OLED_CS1);

void setup() {
  Serial.begin(9600);
  delay(200);
  display1.begin(SH1106_SWITCHCAPVCC);
  delay(100);
  showCenteredText(display1, "A God of", "the New", "World");
}

void showCenteredText(Adafruit_SH1106 &d, const char *line1, const char *line2, const char *line3) {
  d.clearDisplay();

  d.setTextSize(2);      // Large text
  d.setTextColor(WHITE);

  // Calculate total height of 3 lines
  int16_t x1, y1, x2, y2, x3, y3;
  uint16_t w1, h1, w2, h2, w3, h3;

  d.getTextBounds(line1, 0, 0, &x1, &y1, &w1, &h1);
  d.getTextBounds(line2, 0, 0, &x2, &y2, &w2, &h2);
  d.getTextBounds(line3, 0, 0, &x3, &y3, &w3, &h3);

  uint16_t totalHeight = h1 + h2 + h3 + 4; // 4 pixels spacing total (2px each gap)

  int16_t y_start = (SCREEN_HEIGHT - totalHeight) / 2;

  int16_t y_line1 = y_start;
  int16_t y_line2 = y_line1 + h1 + 2; // 2px spacing
  int16_t y_line3 = y_line2 + h2 + 2; // 2px spacing

  int16_t x_line1 = (SCREEN_WIDTH - w1) / 2;
  int16_t x_line2 = (SCREEN_WIDTH - w2) / 2;
  int16_t x_line3 = (SCREEN_WIDTH - w3) / 2;

  // Draw lines
  d.setCursor(x_line1, y_line1);
  d.println(line1);

  d.setCursor(x_line2, y_line2);
  d.println(line2);

  d.setCursor(x_line3, y_line3);
  d.println(line3);

  d.display();
}

void loop() {}
