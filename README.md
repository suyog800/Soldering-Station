# Soldering Station
 The soldering station is a multipurpose power soldering device designed for electronic components soldering. Soldering stations are widely used in electronics repair workshops, electronic laboratories, in industries, etc. Sometimes it becomes a tedious task to solder some parts that are small, and can thus cause some disturbance in the circuit if not soldered properly.  
Working of the Project:
How to use: 
The soldering station can be operated in two modes: manual and point selection. Manual mode is for immediate soldering at a given point, and point selection mode is for soldering at ‘n’ number of points, as per user input. User can select the mode via the toggle switch (SW1). 

Manual mode: after toggling the selection switch to the manual mode, the user can, through the rotary encoders, control the motors and thus move the manipulator in x,y,z directions- to the desired point. Then user will press the red ‘enter’ button (SW3) twice- this will make the solder wire extend from the extruder mechanism and come out through the pipe. Soldering will thus be done at this point. 

Point selection mode: after toggling the selection switch to the point selection mode, the user turns ON the black SPST switch (SW2) to start selecting points. Through the rotary encoders, the user can move the manipulator to the desired coordinate (the coordinate will be displayed on the screen). Pressing the red ‘enter’ button twice to select this coordinate. The user can then select the next desired coordinate again via the encoders (and continue with the same steps). Once user is done selecting the required number of coordinates, the black SPST switch is turned OFF. Now the manipulator will move on its own and go to these specified points and soldering will thus be done there. 

An additional microscope, placed on the manipulator, can be connected to a monitor, and used to view in case of smaller components. 

The design is divided into two domains— Mechanical and Electronics.  

Mechanical- 

The bot can move in x, y and z direction. In x direction we have designed the 3d part to give gt2 belt proper tension and has put that tension on one side and on other side there is nema17 motor. So, in x direction belt is moving through pulley and belt. In y direction we have tensioner and gantry on other side. On gantry we designed a part so that it can hold nema17 motor and simultaneously pass the x and y direction belt. For z part we have designed a part which can have Nema 17 motor, lead screw and smooth rod. It can also have the component like soldering iron, microscope and have mechanism such that the soldering wire can pass through it. 

Electronics- 

The Nema17 motors are actuated by the arduino mega and the ramps 1.4 cnc shield. The ardiuno mega is in turn controlled by the raspberry pi pico microcontroller via UART serial communication. The raspberry pi pico forms the main control system and takes in user input for the coordinates through three separate rotary encoders (for x,y,z axis), displays the said coordinates on the screen, and enters them. 

The actuation of the motors (arduino mega) is coded in C language on the arduino ide, while the raspberry pi pico is programmed in python. 

Once the mode is selected and coordinates are appropriately decided, the user enters the coordinates by pressing the “enter” button. This will thus lead to serial communication of the data (axes coordinates) from the pico to the mega. The mega will receive the data and actuate the motors to go to the position corresponding to the given coordinates. Once the manipulator is in the specified position, the extruder motor rotates slightly, and solder wire extends out, and soldering is done at that point. 

The cnc shield also has endstops (limit switches) connected which are placed at the two ends of the axes, as a safety precaution. 

This current set-up can theoretically provide 5micrometer (practically 40 micrometer, due to vibrations of components) of precision, made possible by enabling microstepping for the Nema17 motors.
![image](https://user-images.githubusercontent.com/85508275/208583627-d36f925f-571f-4b89-88d0-04b9fc0c303e.png)
Specifications:
Sr.  No.	Component	     Specification/Rating
1.	  X axis T-slot	        Aluminium Alloy 6063
2.	  Y axis T-slot	        Aluminium Alloy 6063
3.	  Z axis Lead Screw	    304 Stainless Steel
4. 	 X axis Nema17 motor	
5.	  Y axis Nema17 motor	
6.	  Zaxis Nema17 motor	
7. 	 Extruder motor	
8.	  Soldering Iron	
Part List:
Total cost of project:


![image](https://user-images.githubusercontent.com/85508275/208583886-d2868199-05f7-474c-9b1e-3e089536cfe8.png)

Design Considerations/Decisions:
While designing the soldering station first issue we solved was giving belt tension by designing the tensioner for it.  Later we made the design such that the x and y belt do not coincide with each other and can move smoothly with right tension. Also, for z movement we made the cad model such that smooth rod and lead screw can move through bearing also for soldering wire we have the cad model such that through mk8 extruder wire directly passes through that design and directly goes to the place where we have to solder. 

Tensioner-
Top View-
![image](https://user-images.githubusercontent.com/85508275/208584018-fc18961e-3054-43c7-afb6-3fb0467e2fd9.png)


Bottom View-![image](https://user-images.githubusercontent.com/85508275/208584049-1f291af9-04dc-436e-ac87-fd94c1a93b2b.png)

Left View- ![image](https://user-images.githubusercontent.com/85508275/208584111-5a6230e4-2a72-4b29-b0f0-e234e5125478.png)

Right View-![image](https://user-images.githubusercontent.com/85508275/208584159-61833a4c-b5b0-4383-abac-c0ad84a668e7.png)

Front View-![image](https://user-images.githubusercontent.com/85508275/208584224-e39d1df4-565a-4b77-a4b1-eea14505a464.png)
Back View- ![image](https://user-images.githubusercontent.com/85508275/208584271-e41f95c7-b435-4419-876d-969140730c5c.png)
                                                        
  Nema 17 Motor-
  
  
