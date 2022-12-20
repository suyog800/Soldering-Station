from rotary2 import Rotary
import utime as time
from machine import UART
# import time
uart = UART(1, 115200) # init with given baudrate
uart.init(115200, bits=8, parity=None, stop=1)# init with given parameters

from machine import Pin, SPI
import githubled
spi1 = SPI(0, baudrate=100000, polarity=1, phase=0, sck=Pin(2), mosi=Pin(3))
ss1 = Pin(6, Pin.OUT)

spi2 = SPI(1, baudrate=100000, polarity=1, phase=0, sck=Pin(10), mosi=Pin(11))
ss2 = Pin(12, Pin.OUT)
rotary1 = Rotary(17, 16, 22)
rotary2 = Rotary(8, 7, 21)
rotary3 = Rotary(27,26,28)
val1 = 0 #for z axis
val2 = 0 #for x axis
val3 = 0 #for y axis
val4 = 0 #for extruder
display1 = githubled.Display(spi1, ss1)
display2 = githubled.Display(spi2, ss2)

sm = Pin(15,Pin.IN, Pin.PULL_UP)   #pin to select mode
st_p =  Pin(13, Pin.IN, Pin.PULL_UP)  # pin to start selecting cordinates
sp = Pin(9,Pin.IN, Pin.PULL_UP)   #pin to select cordinates enter
# GPIO Pins 16 and 17 are for the encoder pins. 22 is the button press switch.

pending = False
last_sent_at = 0

def send_pending_data():
    if pending==True:
        send_data(True)

def send_data(overwrite=False):
    global last_sent_at
    new_time = time.time()
    # print(new_time)
    if (new_time-1>last_sent_at or overwrite):
        uart.write(str(val1)+","+str(val2)+","+str(val3)+","+str(val4)+"\n")
        last_sent_at = new_time
        print('Data Sent')
    else:
        pending = True

def rotary_changed1(change1):
    global val1
    if change1 == Rotary.ROT_CW:
        val1 = val1 + 1
    elif change1 == Rotary.ROT_CCW:
        val1 = val1 - 1
    print(val1)
    display1.display_two_nums(val1, val2)
    display2.display_two_nums(val3, val4)
    send_data()

def rotary_changed2(change2):
    global val2
    if change2 == Rotary.ROT_CW:
        val2 = val2 + 1
    elif change2 == Rotary.ROT_CCW:
        val2 = val2 - 1
    print(val2)
    display1.display_two_nums(val1, val2)
    display2.display_two_nums(val3, val4)   
    send_data()

def rotary_changed3(change3):
    global val3
    if change3 == Rotary.ROT_CW:
        val3 = val3 + 1
    elif change3 == Rotary.ROT_CCW:
        val3 = val3 - 1
    print(val3)
    display1.display_two_nums(val1, val2)
    display2.display_two_nums(val3, val4)    
    send_data()

def extruder():
    global val4
    val4=val4+1
    


def point_selection_mode():
    x_cord_list = []
    z_cord_list = []
    y_cord_list = []
    print("point selection mode")
    while(st_p.value() == 1):
        if sm.value() == 0:
            break
        rotary1.add_handler(rotary_changed1)
        rotary2.add_handler(rotary_changed2)
        rotary3.add_handler(rotary_changed3)
        while True:
            time.sleep(0.01)
#            send_pending_data()
            send_data()
            if sm.value() == 0:
                break
            if sp.value() == 1:
                x_cord_list.append(val2)
                z_cord_list.append(val1)
                y_cord_list.append(val3)
                
                print("coordinate added, press enter again")
                time.sleep(3)
                print("select next cordinate, else switch st_p off")
                continue
            if st_p.value() == 0:
                print("you are out of the loop")
                break
        

            
    if len(x_cord_list)>0:
        while True:
            for i in range(len(x_cord_list)):
                global val4
                
                print("automatic mode started")
                
                uart.write(str(z_cord_list[i])+","+str(x_cord_list[i])+","+str(y_cord_list[i])+","+str(val4)+"\n")
                print(z_cord_list[i],x_cord_list[i],y_cord_list[i])
                time.sleep(10)
                val4=1+val4
                uart.write(str(z_cord_list[i])+","+str(x_cord_list[i])+","+str(y_cord_list[i])+","+str(val4)+"\n")
                time.sleep(5)
            print("point selection mode execuition completed")    
    else:
        print("switch the st_p switch on to select cordinates")
        time.sleep(1)



        
        

             
count=0        
while True :
    mode = sm.value() #either 0 or 1
    if mode == 0:
         while sm.value()==0:
             print("manual mode\n")
             print("press sp button twice to actuate extruder")
         
             rotary1.add_handler(rotary_changed1)
             rotary2.add_handler(rotary_changed2)
             rotary3.add_handler(rotary_changed3)
                     
             while True:
                time.sleep(0.01)
                if sp.value()==1:
                        val4=val4+1
                        send_data()
                        print("soldering done!!")
                        time.sleep(0.9)
                send_data()
                         
                         
                if sm.value() == 1:
                    print("mode has been changed")
                    time.sleep(0.1)
                    break
                 
    elif mode == 1:
            while mode == 1:
                point_selection_mode()
                if sm.value() == 0:
                    break
                
    else:
        print("invalid input!!!, problem in sm switch")
    count=count+1
    
    #time.sleep(1)