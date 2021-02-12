'''
REVISIONS:
R1  - using pyautogui image obj to get pixel RGB in a for loop :(
R2  - convert image to np array to get pixel RGB vectorized    :)
R3  - turns out rgb averaging with for loop was faster
    -   bc np.array(im) took too long.
R4  - spit out average rgb as string (no longer ints)
R5  - allow buffer to be different for x and y
        (good for ultrawide when left and right is black)
R6  - R3 but with independent x and y buffer
        (doesn't use the string output as updated in R4... in retrospect idk why i did that)
TO DO:
    - vectorize screen_RGB_avg()
    - vectorize rgb_to_hex()
'''
import turtle
import pyautogui as pag
import numpy as np
from datetime import datetime

def get_screen_samplepts(num_x, num_y, buffer_x, buffer_y, im):
    '''
        WHAT IT DO:
    takes a pyautogui screenshot and gets sample pixel locations along border

        ARGUMENTS:
    num_x   int     number of samples in x direction (i.e. number of leds you have)
    num_y   int     number of samples in y direction
    buffer  int     how far from edge of screen to take sample points from
    im      pag obj pyautogui screenshot
        OUTPUT:
    sample_pts  np.array    sampled border pixel locations.
                            serialized from top left clockwise
    '''

    # set min as buffer
    min_x = buffer_x
    min_y = buffer_y

    # get max coords from image
    max_x, max_y = im.size
    # adjust max by buffer
    max_x = max_x - buffer_x
    max_y = max_y - buffer_y

    # get sampled axes
    x_pts = np.linspace(min_x, max_x, num_x)
    y_pts = np.linspace(min_y, max_y, num_y)

    # initialize border vectors
    v1 = np.empty([num_x, 2])
    v2 = np.empty([num_y, 2])
    v3 = np.empty([num_x, 2])
    v4 = np.empty([num_y, 2])

    # each border vector goes corner to corner
    # this means the last and first point between vectors is redundant
    # therefore, after making each vector, the last point is sliced out

    # v1: top left across to top right
    v1[:,0] = x_pts
    v1[:,1] = min_y
    v1 = v1[:-1,:]
    # v2: top right down to bottom right
    v2[:,0] = max_x
    v2[:,1] = y_pts
    v2 = v2[:-1,:]
    # v3: bottom right across to bottom left
    v3[:,0] = np.flip(x_pts)
    v3[:,1] = max_y
    v3 = v3[:-1,:]
    # v4: bottom left up to top left
    v4[:,0] = min_x
    v4[:,1] = np.flip(y_pts)
    v4 = v4[:-1,:]

    # put border vectors together, giving
    # a serialized vector of all sampled border points
    sample_pts = np.concatenate((v1,v2,v3,v4))

    # num_pts = 2*(num_x + num_y - 2)
    # assert num_pts == sample_pts.shape[0]

    return sample_pts

def zone_coord(center,size):
    '''
        WHAT IT DO:
    makes a serialized list of coordinates of a sample zone
        ARGUMENTS:
    center  np.array    ordered pair of coordinates of center of sample zone
    size    int (odd)   dimension of sample zone
        OUTPUT:
    coords  np.array    flattened coords of sample zone
    '''

    # these are the x and y axes, sampled by pixel location
    x = np.linspace(center[0]-(size-1)/2, center[0]+(size-1)/2, size)
    y = np.linspace(center[1]-(size-1)/2, center[1]+(size-1)/2, size)

    # list of all coordinate combinations
    coords = [[a,b] for a in x for b in y]

    # turn list into array
    coords = np.array(coords)

    return coords

def zone_coords(centers, size):
    # each col corresponds to a zone
    # so xs will be dim size x num_pts
    # xs[:,i] are the x coords of the ith zone
    xs = np.linspace(centers[:,0]-(size-1)/2, centers[:,0]+(size-1)/2, size)
    ys = np.linspace(centers[:,1]-(size-1)/2, centers[:,1]+(size-1)/2, size)

    return

def get_RGB_vals(sample_pts, im):
    '''
        WHAT IT DO:
    take a list of sample points and give RGB values at each location
        ARGUMENTS:
    sample_pts  np.array    size (n,2)
    im          PIL.image
        OUTPUT:
    RGB         np.array    size (n,3)
    '''
    # im = pag.screenshot()
    num_pts = sample_pts.shape[0]

    RGB =  np.zeros((num_pts, 3))

    for k,pt in enumerate(sample_pts):
        RGB[k] = im.getpixel(tuple(pt))

    return RGB

def avg_RGB(sample_pts, im):
    '''
        WHAT IT DO:
    get average RGB value of each pt in sample_pts and return their avg RGB val.
    exactly the same as get_RGB_vals with the added averaging line at end
        ARGUMENTS:
    sample_pts  np.array    ordered pairs of points
    im          pag obj     screenshot
        OUTPUT:
    avg         np.array    single RGB value, averaged across sample_pts
    '''

    num_pts = sample_pts.shape[0]

    RGB =  np.zeros((num_pts, 3))

    # ik, ik it's a for loop. i tried using an array and vectorizing
    # vector orperation was fast but converting to matrix in ordered
    # to do vector op took a long time, bottlenecking program
    for k,pt in enumerate(sample_pts):
        RGB[k] = im.getpixel(tuple(pt))

    avg = np.average(RGB, axis=0)

    return avg.astype(int)

def screen_RGB_avg(num_x, num_y, buffer_x, buffer_y, zone_size):
    '''
        WHAT IT DO:
    take sampling dimensions, spit out avg rgb at sample points around border of screen
        ARGUMENTS:
    num_x   int     number of samples in x direction (i.e. number of leds you have)
    num_y   int     number of samples in y direction
    buffer  int     how far from edge of screen to take sample points from
    zone_size int   (odd) dim of sample size at each sample point
        OUTPUT:
    RGB_avg np.array    avg rgb val at each sample point along border of screen
    '''

    # take a screenshot
    im = pag.screenshot()

    # get sample pts along border of screen
    samp_pts = get_screen_samplepts(num_x, num_y, buffer_x, buffer_y, im)

    # initialize avg rgb array
    RGB_avg = np.empty((samp_pts.shape[0],3))

    # for each sample point, generate a sample zone
    # and get the average RGB in the zone
    # ! it would be nice to vectorize this
    for k,pt in enumerate(samp_pts):
        zone = zone_coord(pt, zone_size)
        RGB_avg[k] = avg_RGB(zone,im)

    return RGB_avg.astype(int)

def rgb_to_hex(RGB):
    '''
        WHAT IT DO:
    convert rgb int array to hex str array
        ARGUMENTS:
    array of rgb colors (int)
        OUTPUT:
    array of hex colors (string)
    '''

    RGB = RGB.astype(int) # make sure RGB vals are ints
    hex = [] # initialize hex list
    # for each color, convert to hex
    # if hex is used for LED library, might be worth vectorizing this
    for color in RGB:
        str = '#%02x%02x%02x' % (color[0], color[1], color[2])
        hex.append(str)
    return hex

def draw_square(my_turtle, color):
    # my_turtle.fillcolor('#C0E5C2')
    # my_turtle.fillcolor((100,10,10))
    my_turtle.fillcolor(color)
    my_turtle.begin_fill()
    for _ in range(4):
        my_turtle.forward(box_size)
        my_turtle.right(90)
    my_turtle.end_fill()
    return

def screen_sim(num_x,num_y,hex_colors):
    # a little janky. used to test above functions to make sure they work
    # and give a visual of the result

    global box_size
    box_size = 49

    t = turtle.Turtle()
    t.speed(0)

    sw = t.screen.window_width()
    sh = t.screen.window_height()
    t.penup()
    t.setpos(-sw/2, sh/2)
    t.pendown()

    for k,color in enumerate(hex_colors):
        draw_square(t,color)
        t.forward(box_size)
        if (k == num_x - 1):
            t.right(90)
            t.forward(box_size)
        elif (k == num_x + num_y - 2):
            t.right(90)
            t.forward(box_size)
        elif (k == 2*num_x + num_y - 3):
            t.right(90)
            t.forward(box_size)

    return


if __name__ == "__main__":
    # if run as main, will give you a preview of the border avg pixels
    # in a turtle window
    # also prints to monitor the time it take to compute the rgb serial string

    taskbar = 50 # standard taskbar height is 50 pixels
    # 26/11
    num_x = 20
    num_y = 9
    zone_size = 5
    buffer = taskbar + (zone_size-1)/2

    start = datetime.now()
    RGB_serial = screen_RGB_avg(num_x,num_y,buffer,buffer,zone_size)
    print(datetime.now() - start)

    hex_serial = rgb_to_hex(RGB_serial)

    screen_sim(num_x,num_y,hex_serial)
