#include <Adafruit_NeoPixel.h>

#define DATAPIN 6
#define NUMPIXELS 54

Adafruit_NeoPixel pixels(NUMPIXELS, DATAPIN);

void setup() {
    Serial.begin(290000);
    pixels.begin();
    pixels.clear();
    pixels.show();
    pixels.setBrightness(95);
}

void loop() {
    if (Serial.available() > 0) {
        for (int i = 0; i < NUMPIXELS; i++) {
            // bite off a hex code from the serial monitor
            char data[8];
            Serial.readBytes(data, 8);

            // convert hex to rgb
            long number = strtol(&data[1], NULL, 16);
            long r = number >> 16;
            long g = number >> 8 & 0xFF;
            long b = number & 0xFF;

            // send rgb to next pixel
            pixels.setPixelColor(i, pixels.gamma32(pixels.Color(r, g, b)));
        }
        // once the full string has been written, flush the monitor and show the pixels
        Serial.flush();
        pixels.show();
    }
}
