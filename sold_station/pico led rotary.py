from rotary2 import Rotary
import utime as time
from machine import UART

uart = UART(1, 115200) # init with given baudrate
uart.init(115200, bits=8, parity=None, stop=1)# init with given parameters


from machine import Pin, SPI
import max7219_8digit
spi = SPI(0, baudrate=100000, polarity=1, phase=0, sck=Pin(2), mosi=Pin(3))
ss = Pin(6, Pin.OUT)


sm = Pin(15,Pin.IN, Pin.PULL_UP)   #pin to select mode
st_p =  Pin(11, Pin.IN, Pin.PULL_UP)  # pin to start selecting cordinates
sp = Pin(9,Pin.IN, Pin.PULL_UP)   #pin to select cordinates
# GPIO Pins 16 and 17 are for the encoder pins. 22 is the button press switch.
rotary2 = Rotary(16, 17, 22)
val = 0
display = max7219_8digit.Display(spi, ss)


def rotary_changed(change):
    global val
    if change == Rotary.ROT_CW:
        val = val + 1
        display.write_to_buffer(str(val))
        display.display()
        uart.write(str(val)+"\n")
        print(val)
    elif change == Rotary.ROT_CCW:
        val = int(val) - 1
        print(val)
        display.write_to_buffer(str(val))
        display.display()
        uart.write(str(val)+"\n")
        print(val)
    elif change == Rotary.SW_PRESS:
        display.write_to_buffer(str(val))
        display.display()
    elif change == Rotary.SW_RELEASE:
        display.write_to_buffer(chr(val))
        display.display()



def point_selection_mode():
    x_cord_list = []
    print("point selection mode")
    while(st_p.value() == 1):
        rotary2.add_handler(rotary_changed)
        time.sleep(1)
          
        if sp.value() == 1:
            x_cord_list.append(val)
            print("coordinate added")
            time.sleep(15)
            print("select next cordinate")
    if len(x_cord_list)>0:        
        for i in len(x_cord_list):        
            uart.write(str(x_cord_list[i])+"\n")
            print(x_cord_list[i])
            time.sleep(100000)
    else:
        print("switch the st_p switch on")
        time.sleep(5)



        
        
count=0        
while True :
    mode = sm.value() #either 0 or 1
    if mode == 0:
             if count == 0:
                 print("manual mode")
             rotary2.add_handler(rotary_changed)
             time.sleep(1)
    elif mode == 1:
            while mode == 1:
                point_selection_mode()
    else:
        print("invalid input!!!, problem in sm switch")
        
    count++        
        
