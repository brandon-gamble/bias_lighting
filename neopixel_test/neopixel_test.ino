// ideas
// -----------READ METHOD 1-----------
// read serial input until delimiter is reached
// once reached, spit out the hex color and send to next pixel
// once an end delimiter is reached, reset pixel count
// e.g. "#123456,#24680,#abcdef\n" would be read in until the ","
// at this point, #123456 is spit out and sent to pixel[i=0]
// then i is incremented and serial is read until next comma,
// spitting out #24680 and sending to pixel[i=1]
// then i is incremented and serial is read until final delimiter, '\n'
// at this point, #abcdef is sent to pixel[i=2] and i is reset to i=0

// -----------READ METHOD 2-----------
// start charac '#', end charac ','
// read colors and send to pixels in a while loop as below
// while i < NUMPIXELS:
//      read and send pixel colors
//      i += 1
// this avoids checking every character in for color end (",")
// or led strip end ("\n")


#include <Adafruit_NeoPixel.h>

#define DATAPIN 6
#define NUMPIXELS 54

Adafruit_NeoPixel pixels(NUMPIXELS, DATAPIN);

// #define DELAYVAL 25

int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(290000);

  pixels.begin();
  pixels.clear();
  pixels.show();
//  pixels.setBrightness(25);
  pixels.setBrightness(95);

  ////////////////////////////////////////////////////////
  // sending array of a single rgb
  ////////////////////////////////////////////////////////
  // int color[] = {100,0,0};
  // for (int i=0; i<NUMPIXELS; i++){
  //     pixels.setPixelColor(i, pixels.Color(color[0],color[1],color[2]));
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // sending array of multiple rgb (2d)
  ////////////////////////////////////////////////////////
  // int color[][3] = {{0,100,0},{100,0,0}};
  // for (int i=0; i<NUMPIXELS/2; i++){
  //     pixels.setPixelColor(i, pixels.Color(color[0][0],color[0][1],color[0][2]));
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  // for (int i=NUMPIXELS/2; i<NUMPIXELS; i++){
  //     pixels.setPixelColor(i, pixels.Color(color[1][0],color[1][1],color[1][2]));
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // sending array of multiple rgb (flattened)
  ////////////////////////////////////////////////////////
  // int color[] = {0,100,0,  100,0,0,  0,0,100};
  // int k = 0;
  // for (int i=0; i<3; i++){
  //     pixels.setPixelColor(i, pixels.Color(color[k],color[k+1],color[k+2]));
  //     k +=3;
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  ////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////
  // difference between gamma32 adjusted and unadjusted //
  ////////////////////////////////////////////////////////
  // for (int i=0; i<9; i++){
  //     pixels.setPixelColor(i, pixels.Color(129,27,207));
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  // for (int i=9; i<18; i++){
  //     pixels.setPixelColor(i, pixels.gamma32(pixels.Color(129,27,207)));
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  ////////////////////////////////////////////////////////
}

void loop() {

  ////////////////////////////////////////////////////////
  // cycle r, g, b thru strip
  ////////////////////////////////////////////////////////
  // put your main code here, to run repeatedly:
  // for (int i=0; i<NUMPIXELS; i++){
  //     pixels.setPixelColor(i, pixels.Color(150,0,0));
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  // for (int i=0; i<NUMPIXELS; i++){
  //     pixels.setPixelColor(i, pixels.Color(0,150,0));
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  // for (int i=0; i<NUMPIXELS; i++){
  //     pixels.setPixelColor(i, pixels.Color(0,0,150));
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  // for (int i=0; i<NUMPIXELS; i++){
  //     pixels.setPixelColor(i, pixels.gamma32(pixels.Color(129,27,207)));
  //     delay(DELAYVAL);
  //     pixels.show();
  // }
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // receive a hex in serial monitor, convert to rgb
  ////////////////////////////////////////////////////////
  // if (Serial.available() > 0) {
  //     String data = Serial.readStringUntil('\n');
  //     Serial.print("arduino received: ");
  //     Serial.println(data);
  //
  //     long number = strtol(&data[1], NULL, 16);
  //     long r = number >> 16;
  //     long g = number >> 8 & 0xFF;
  //     long b = number & 0xFF;
  //     Serial.print(r);
  //     Serial.print(", ");
  //     Serial.print(g);
  //     Serial.print(", ");
  //     Serial.print(b);
  //     Serial.println("\n");
  // }
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // write subsequent hex in serial to leds
  ////////////////////////////////////////////////////////
  // if (Serial.available() > 0) {
  //     String data = Serial.readStringUntil('\n');
  //     Serial.print("arduino received: ");
  //     Serial.println(data);
  //
  //     long number = strtol(&data[1], NULL, 16);
  //     long r = number >> 16;
  //     long g = number >> 8 & 0xFF;
  //     long b = number & 0xFF;
  //     Serial.print(r);
  //     Serial.print(", ");
  //     Serial.print(g);
  //     Serial.print(", ");
  //     Serial.print(b);
  //     Serial.println("\n");
  // }
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // set string to hex from serial monitor
  ////////////////////////////////////////////////////////
  // if (Serial.available() > 0) {
  //     String data = Serial.readStringUntil(',');
  //     Serial.print("arduino received: ");
  //     Serial.println(data);
  //
  //     long number = strtol(&data[1], NULL, 16);
  //     long r = number >> 16;
  //     long g = number >> 8 & 0xFF;
  //     long b = number & 0xFF;
  //     Serial.print(r);
  //     Serial.print(", ");
  //     Serial.print(g);
  //     Serial.print(", ");
  //     Serial.print(b);
  //     Serial.println("\n");
  //
  //     for (int i=0; i<NUMPIXELS; i++){
  //         pixels.setPixelColor(i, pixels.Color(r,g,b));
  //         delay(DELAYVAL);
  //         pixels.show();
  //     }
  // }
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // set string to hex from serial monitor
  // first half unadjusted, second half gamma32 adjusted
  ////////////////////////////////////////////////////////
  // if (Serial.available() > 0) {
  //     String data = Serial.readStringUntil(',');
  //     Serial.print("arduino received: ");
  //     Serial.println(data);
  //
  //     long number = strtol(&data[1], NULL, 16);
  //     long r = number >> 16;
  //     long g = number >> 8 & 0xFF;
  //     long b = number & 0xFF;
  //     Serial.print(r);
  //     Serial.print(", ");
  //     Serial.print(g);
  //     Serial.print(", ");
  //     Serial.print(b);
  //     Serial.println("\n");
  //
  //     for (int i=0; i<NUMPIXELS/2; i++){
  //         pixels.setPixelColor(i, pixels.Color(r,g,b));
  //         delay(DELAYVAL);
  //         pixels.show();
  //     }
  //     for (int i=NUMPIXELS/2; i<NUMPIXELS; i++){
  //         pixels.setPixelColor(i, pixels.gamma32(pixels.Color(r,g,b)));
  //         delay(DELAYVAL);
  //         pixels.show();
  //     }
  // }
  ////////////////////////////////////////////////////////



  ////////////////////////////////////////////////////////
  // set pixel to hex from serial monitor, reset pixel
  // counter when it exceeds string length
  ////////////////////////////////////////////////////////
  // // kinda works but gets tripped up on big strings
  // if (Serial.available() > 0) {
  //     String data = Serial.readStringUntil(',');
  //     Serial.print("arduino received: ");
  //     Serial.println(data);
  //
  //     long number = strtol(&data[1], NULL, 16);
  //     long r = number >> 16;
  //     long g = number >> 8 & 0xFF;
  //     long b = number & 0xFF;
  //     Serial.print(r);
  //     Serial.print(", ");
  //     Serial.print(g);
  //     Serial.print(", ");
  //     Serial.print(b);
  //     Serial.println("\n");
  //
  //     pixels.setPixelColor(i, pixels.Color(r,g,b));
  //     pixels.show();
  //     delay(DELAYVAL);
  //     i += 1;
  //
  // }
  // if (i >= NUMPIXELS) {
  //     i = 0;
  // }
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // set string to hex from serial monitor
  ////////////////////////////////////////////////////////
  if (Serial.available() > 0) {
    // String data = Serial.readStringUntil(',');
    char data[8];
    Serial.readBytes(data, 8);

    // Serial.print("arduino received: ");
    // Serial.println(data);

    long number = strtol(&data[1], NULL, 16);
    long r = number >> 16;
    long g = number >> 8 & 0xFF;
    long b = number & 0xFF;
    //         Serial.print(r);
    //         Serial.print(", ");
    //         Serial.print(g);
    //         Serial.print(", ");
    //         Serial.print(b);
    //         Serial.println("\n");

    pixels.setPixelColor(i, pixels.gamma32(pixels.Color(r, g, b)));
    //        pixels.show();
    // delay(DELAYVAL);
    i += 1;
    // Serial.println(i);

  }

  if (i >= NUMPIXELS) {
    Serial.flush();
    i = 0;
    // Serial.println("END OF STRING-------------------------------------------");
    // Serial.println("END OF STRING-------------------------------------------");
    pixels.show();
    // delay(100);
  }
  ////////////////////////////////////////////////////////


}
