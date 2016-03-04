#define cs   A2
#define dc   D6
#define rst  D2
#define relay D5

#include "Adafruit_ST7735.h"
#include "Adafruit_Fingerprint.h"

int getFingerprintIDez();
uint8_t getFingerprintID();

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst); // hardware spi

void setup()
    {
      finger.begin(57600);                    // Start fingerprint scanner
      tft.initG();                            // initialise GREEN TAB LCD
      pinMode(relay,OUTPUT);                  // Relay Pin put in output mode
      tft.fillScreen(ST7735_RED);             // Initialise Display Red
      digitalWrite(relay, HIGH);              // Lock Default closed
    }

void loop()
    {
      getFingerprintIDez();                   // Keep looking for valid finger.
    }

int getFingerprintIDez()
    {
      tft.fillScreen(ST7735_RED);             // Sreen Display RED.
      digitalWrite(relay, HIGH);              // lock closed.
      uint8_t p = finger.getImage();          // Take scan of finger...
      if (p != FINGERPRINT_OK)  return -1;    // No finger present!
      p = finger.image2Tz();                  // Covert Scanned image...
      if (p != FINGERPRINT_OK)  return -1;    // Conversion failed!
      p = finger.fingerFastSearch();          // Search stored images...
      if (p != FINGERPRINT_OK)  return -1;    // No match found!
      tft.fillScreen(ST7735_GREEN);           // Match found...
      digitalWrite(relay, LOW);               // open lock.
      delay(2500);                            // small pause while door opens...
      return finger.fingerID;
  }
