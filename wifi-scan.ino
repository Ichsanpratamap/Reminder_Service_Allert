#define BLYNK_TEMPLATE_ID "TMPL6C-2834LN"
#define BLYNK_TEMPLATE_NAME "Reminder Service"
#define BLYNK_AUTH_TOKEN "oEbkszrv3iLB7RXVQPbX1LhjlUS2fsdX"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BTN_KM 18
#define BTN_RESET 19

long totalKM = 0;
long lastServiceKM = 0;

const long serviceIntervalKM = 3000;

unsigned long lastServiceTime = 0;
const unsigned long serviceIntervalTime =
  30UL * 24UL * 60UL * 60UL * 1000UL;

bool notifSent = false;

void setup() {
  Serial.begin(115200);

  pinMode(BTN_KM, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);

  Wire.begin(21, 22);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  lastServiceTime = millis();
}

void loop() {
  Blynk.run();

  tambahKM();
  resetService();

  tampilOLED();
  kirimBlynk();

  delay(100);
}

void tambahKM() {
  static bool lastBtn = HIGH;

  bool btn = digitalRead(BTN_KM);

  if (btn == LOW && lastBtn == HIGH) {
    totalKM += 500;
    Serial.println("KM Bertambah");
  }

  lastBtn = btn;
}

void resetService() {
  static bool lastBtn2 = HIGH;

  bool btn2 = digitalRead(BTN_RESET);

  if (btn2 == LOW && lastBtn2 == HIGH) {

    lastServiceKM = totalKM;
    lastServiceTime = millis();

    notifSent = false;

    Serial.println("Service Reset");
  }

  lastBtn2 = btn2;
}

void tampilOLED() {

  long kmSinceService = totalKM - lastServiceKM;

  unsigned long timeSinceService =
    millis() - lastServiceTime;

  int days =
    timeSinceService / (1000 * 60 * 60 * 24);

  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("Reminder Service");

  display.setCursor(0, 15);
  display.print("Total KM: ");
  display.println(totalKM);

  display.setCursor(0, 30);
  display.print("KM Service: ");
  display.println(kmSinceService);

  display.setCursor(0, 45);
  display.print("Hari: ");
  display.println(days);

  display.display();
}

void kirimBlynk() {

  long kmSinceService =
    totalKM - lastServiceKM;

  unsigned long timeSinceService =
    millis() - lastServiceTime;

  Blynk.virtualWrite(V0, totalKM);

  if (kmSinceService >= serviceIntervalKM ||
      timeSinceService >= serviceIntervalTime) {

    Blynk.virtualWrite(V1,
      "SERVICE SEKARANG!");

    if (!notifSent) {

      Blynk.logEvent(
        "service_alert",
        "Waktunya service kendaraan!"
      );

      notifSent = true;
    }

  } else {

    Blynk.virtualWrite(V1,
      "Kondisi Aman");
  }
}