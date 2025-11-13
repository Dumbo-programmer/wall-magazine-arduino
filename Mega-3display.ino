#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

// === Display Config ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// --- Display 1 ---
#define OLED_MOSI1   9
#define OLED_CLK1    10
#define OLED_DC1     11
#define OLED_CS1     12
#define OLED_RESET1  13
Adafruit_SH1106 display1(OLED_MOSI1, OLED_CLK1, OLED_DC1, OLED_RESET1, OLED_CS1);

// --- Display 2 ---
#define OLED_MOSI2   3
#define OLED_CLK2    2
#define OLED_DC2     5
#define OLED_CS2     6
#define OLED_RESET2  4
Adafruit_SH1106 display2(OLED_MOSI2, OLED_CLK2, OLED_DC2, OLED_RESET2, OLED_CS2);

// --- Display 4 ---
#define OLED_MOSI4   24
#define OLED_CLK4    22
#define OLED_DC4     28
#define OLED_CS4     30
#define OLED_RESET4  26
Adafruit_SH1106 display4(OLED_MOSI4, OLED_CLK4, OLED_DC4, OLED_RESET4, OLED_CS4);

// === Motor (L298N) ===
#define ENA   7
#define IN1   8
#define IN2   A0
bool motorRunning = false;

// === Timers ===
unsigned long lastMove = 0;
const unsigned long moveInterval = 2000;

// === Display Refresh Watchdog ===
unsigned long lastDisplayRefresh = 0;
const unsigned long refreshInterval = 10000; // re-render every 10s for safety

// === Blink Timing ===
unsigned long lastBlink = 0;
const unsigned long blinkInterval = 700; // blink every 700 ms
bool textVisible = true;

// ==== STABLE DISPLAY UPDATE ====
void safeDisplayUpdate(Adafruit_SH1106 &d, const char *text, bool visible) {
  noInterrupts();               // Prevent SPI overlap
  d.clearDisplay();
  if (visible) {
    d.setTextSize(2);
    d.setTextColor(WHITE);

    int16_t x1, y1;
    uint16_t w, h;
    d.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    int16_t x = (SCREEN_WIDTH - w) / 2;
    int16_t y = (SCREEN_HEIGHT - h) / 2;

    d.setCursor(x, y);
    d.println(text);
  }
  d.display();
  interrupts();
}

// ==== INITIALIZE ALL DISPLAYS ====
void initDisplays() {
  Serial.println("Initializing SH1106 displays safely...");
  delay(150);

  display1.begin(SH1106_SWITCHCAPVCC);
  delay(200);
  display2.begin(SH1106_SWITCHCAPVCC);
  delay(200);
  display4.begin(SH1106_SWITCHCAPVCC);
  delay(200);

  safeDisplayUpdate(display1, "Game Over", true);
  safeDisplayUpdate(display2, "An Alternate Reality", true);
  safeDisplayUpdate(display4, "So those the player?", true);
}

// ==== MOTOR CONTROL ====
void runMotorSlow() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 40);
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

// ==== SAFETY RESET FOR DISPLAY ====
void refreshDisplaysIfNeeded() {
  unsigned long now = millis();
  if (now - lastDisplayRefresh > refreshInterval) {
    lastDisplayRefresh = now;
    Serial.println("Refreshing all displays...");
    initDisplays();  // Re-init in case of glitch
  }
}

// ==== BLINK ANIMATION ====
void blinkDisplays() {
  unsigned long now = millis();
  if (now - lastBlink > blinkInterval) {
    lastBlink = now;
    textVisible = !textVisible;

    safeDisplayUpdate(display1, "Game Over", textVisible);
    safeDisplayUpdate(display2, "An Alternate Reality", textVisible);
    safeDisplayUpdate(display4, "So those the player?", textVisible);
  }
}

void setup() {
  Serial.begin(9600);
  delay(200);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  stopMotor();

  initDisplays();
}

void loop() {
  unsigned long now = millis();

  // Reinitialize display every few seconds if needed
  refreshDisplaysIfNeeded();

  // Blink text word-by-word safely
  blinkDisplays();

  // Toggle motor every 2s
  if (now - lastMove > moveInterval) {
    lastMove = now;

    if (motorRunning) {
      stopMotor();
      motorRunning = false;
      Serial.println("Motor stopped.");
    } else {
      runMotorSlow();
      motorRunning = true;
      Serial.println("Motor running slowly...");
    }
  }
}
