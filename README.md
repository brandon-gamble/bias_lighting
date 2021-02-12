# bias_lighting
Bias lighting for monitor backlighting. Uses a python script to sample the screen and generate RGB values, which are sent via USB to an arduino which controls an addressable LED strip.

## How to use this software
Get yourself some WS2812B leds (other addressables will work but you'll have to tweak the arduino code). These are an easy 3 pin connection - pwr/gnd/data. No sweat.

Put them on the back of your monitor facing the wall. Don't worry about finding something to diffuse them - they'll diffuse on their own since they're pointed at the wall. 

Upload the `ambiled.ino` script to your arduino.

Run the `ambiled.py` script on your computer.

Done! It's that easy.

## arduino code
### `ambiled.ino`
This is a simple script that initializes the pixel strip and reads the rgb data sent over usb, then writes the rgb data to the led strip.
Lines 24 to 27 are a sneaky way to convert from a hex value to r, g, and b values. Idk how it works, I found it on stack exchange.  ¯\_(ツ)_/¯

### `neopixel_test.ino`
I included this to show all the ridiculous testing I did in my development and debug phase to get the pixel strip working how I wanted. 

You don't need it. 

You Probably don't even want to see it.

## python code
### `ambiled.py`
Ooops there are two `ambiled` scripts - one `.ino` and one `.py`. This is the papa script that runs continuously. It utilizes the following two scripts...

### `monitor_colors_R6.py`
This is where the bulk of the work happens, so strap in (it's not actually that complicated, don't worry).

I spent a lot of time commenting this script so I won't explain it here other than to say that it handles all the pixel sampling and color averaging.

### `pc_duino_com.py`
A few simple serial communication functions. Easy to figure out if you read the code.
