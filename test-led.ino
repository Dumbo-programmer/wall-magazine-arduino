#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// === Display 1 (Software SPI) ===
#define OLED_MOSI1   9
#define OLED_CLK1    10
#define OLED_DC1     11
#define OLED_CS1     12
#define OLED_RESET1  13

// === Display 2 (Software SPI) ===
#define OLED_MOSI2   3
#define OLED_CLK2    2
#define OLED_DC2     5
#define OLED_CS2     6
#define OLED_RESET2  4

// === Display 4 (Software SPI) ===
#define OLED_MOSI4   24
#define OLED_CLK4    22
#define OLED_DC4     28
#define OLED_CS4     30
#define OLED_RESET4  26

Adafruit_SH1106 display1(OLED_MOSI1, OLED_CLK1, OLED_DC1, OLED_RESET1, OLED_CS1);
Adafruit_SH1106 display2(OLED_MOSI2, OLED_CLK2, OLED_DC2, OLED_RESET2, OLED_CS2);
Adafruit_SH1106 display4(OLED_MOSI4, OLED_CLK4, OLED_DC4, OLED_RESET4, OLED_CS4);

void setup() {
  Serial.begin(9600);
  delay(200);

  Serial.println("Initializing SH1106 displays...");

  display1.begin(SH1106_SWITCHCAPVCC);
  display2.begin(SH1106_SWITCHCAPVCC);
  display4.begin(SH1106_SWITCHCAPVCC);

  delay(100);

  showCenteredText(display1, "Game Over");
  showCenteredText(display2, "An Alternate Reality");
  showCenteredText(display4, "So those the player?");
}

// Function to center text nicely on the screen
void showCenteredText(Adafruit_SH1106 &d, const char *text) {
  d.clearDisplay();
  d.setTextSize(2);        // Larger text
  d.setTextColor(WHITE);

  // Measure text width
  int16_t x1, y1;
  uint16_t w, h;
  d.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  // Center horizontally and vertically
  int16_t x = (SCREEN_WIDTH - w) / 2;
  int16_t y = (SCREEN_HEIGHT - h) / 2;

  d.setCursor(x, y);
  d.println(text);
  d.display();
  delay(50);
}

void loop() {}
