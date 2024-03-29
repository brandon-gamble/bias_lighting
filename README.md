# bias_lighting
Bias lighting for monitor backlighting. Uses a python script to sample the border of the screen and generate average RGB values which are serialized as hex colors and sent via USB to an arduino which in turn sends the colors to an addressable LED strip.

You can see a demo of it here: https://youtu.be/FVjuAfjO09M

## How to use this software
Get yourself some WS2812B leds (other addressables will work but you'll have to tweak the arduino code). These are an easy 3 pin connection - pwr/gnd/data. No sweat.

Put them on the back of your monitor facing the wall. Don't worry about finding something to diffuse them - they'll diffuse on their own since they're pointed at the wall. 

Upload the `ambiled.ino` script to your arduino. Keep your arduino plugged into your computer via usb.

Run the `ambiled.py` script on your computer.*** 

Done! It's that easy.

*** It's likely that the arduino will be the only COM open. If this the case, then the python script will automatically use your arduino. If, however, you have multiple COMs open, you will be asked which to use. If you're not sure which port is your arduino, just open your arduino ide and check which COM port your arduino is attached to, then type it into the python window and press enter.

## arduino code
### `ambiled.ino`
This is a simple script that initializes the pixel strip and reads the rgb data sent over usb, then writes the rgb data to the led strip.
Lines 24 to 27 are a sneaky way to convert from a hex value to r, g, and b values. Idk how it works, I found it on stack exchange.  ¯\_(ツ)_/¯

### `neopixel_test.ino`
I included this to show all the testing I did in my development and debug phase to get the pixel strip working how I wanted. 

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
