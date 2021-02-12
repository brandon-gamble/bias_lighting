import monitor_colors_R6 as mc
import pc_duino_com_R2 as coms
import time
# uses neopixel_test.ino

'''
how to speed up?
- send entire hex_serial as single transmission
    - this would require messing with .ino script to be able to
    handle a long input
    - might want to look at "<>" start/end characs to help duino parse
    this might help with when it gets a lot and trips up, it can just move to
    next pixel rather than ruin the rest of the transmission
- figure out how to send RGB directly py to ino
    - currently, py needs to convert to hex, send hex, then
    ino receives hex and needs to convert to rgb
    - would be faster to cut out these conversions
'''

#taskbar = 50*10/5
taskbar = 40#+50
ultrawide = 320#+133
# 26/11
# 20/9 - 54
# 7/4 - 18
num_x = 20
num_y = 9
zone_size = 5
buffer_x = ultrawide + (zone_size-1)/2
buffer_y = taskbar + (zone_size-1)/2

ser = coms.initialize_com(290000);

time.sleep(2)
it = 0
while True:
    RGB_serial = mc.screen_RGB_avg(num_x,num_y,buffer_x,buffer_y,zone_size)
    hex_serial = mc.rgb_to_hex(RGB_serial)

    for color in hex_serial:
        msg = color+','
        coms.send_msg(ser, color)

    # mc.screen_sim(num_x,num_y,hex_serial)
    # it = it+1
    # input('press any key to continue to it '+str(it)+'...')
