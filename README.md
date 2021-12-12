# Pedometer - Course Project  

The repository contains the code for PES (ECEN-5813), Fall 2021 course project. The project contains only the DEBUG 
build target whose purpose is to interface Accerelometer (MMA8451) and 16x2 LCD to implement the functionality of a
pedometer using FRDM-KL25Z board.  

## Project Goals  
### Project Defination  
Developing a pedometer to detect the number of steps accurately and display the count on the 16x2 display. Also, configure
 a GPIO interrupt so that MMA8451Q (Accelerometer) can notify the KL25Z to start counting number of steps.  

### Objectives  
• Interfacing 3-axis accelerometer (MMA8451Q) with KL25Z over I2C to measure the movement across all the 3-axis.  
• Develop an algorithm to detect the number of steps accurately based on the reading from the accelerometer.  
• Interface 16x2 LCD to display the out of number of steps for the user.  

### Features  
A pedometer calculates the total number of steps taken by the person. While taking the steps, there may be variation in motion in all 3-axis. The pedometer, by its core, uses measurements of acceleration in the direction of all 3 axis.  
While running the pedometer can be in any orientation, so it is necessary to incorporate all acceleration in all the 3-axis. To do so, we would calculate the mean of square of acceleration in 3 axis.  
In order to get the complete functionality of the device we would implement all the following features:  
• It counts the steps i.e., number of changes in acceleration in any orientation.  
• Displays the number of steps registered on the LCD  
• The touch panel or the external button is used to reset the pedometer reading to 0.  
• The button is interfaced as an external GPIO interrupt.  

## Software Modules  
• ```button.c/.h```: The file contains the initialization of button interfaced on PA5 pin of the board. The button is configured to generate external gpio based interrupt. The module also contains the IRQ handler to manager the interrupt on the pin. The IRQ handler sets a flag which is exposed to other modules of the project using a functin called ```get_flagSwitch()```.  
• ```tsi.c/.h```: The module handles the configuration and calibration of the onboard capacitive touch sensor. The module holds ```TSI_Detect()``` function which returns a bool value stating if touch is detected on not. The module operates the TSI sensor in the polling mode.  
• ```mma8451.c/.h```: It handles the configuration of accelerometer and reads the data for all the 3-axis' acceleration using the I2C library. It handles the I2C read and write operations to access specific register of the sensor to obtain desired readings.  
• ```i2c.c/.h```: It handles the bare-metal implementation of I2C on KL25Z for I2C port-0. It defines the API for write, read, repeated read and I2C0 init.  
• ```timer.c/.h```: It handles the systick implementation and configuration in the interrupt mode. It also contains the function ```delay()``` to generate blocking delay with 1msec resolution.  
• ```lcd.c/.h```: The module handles the bare-metal code to interface ```JHD 162A (16x2) LCD``` on GPIO port C. The module defines the API to write the string or integer value on the LCD Display.  
• ```utility.c/.h```: The module contains the API to implementation of the application level logic for project implementation i.e. ```step detection algorithm```. The function can be called form the main file to implment the application.  
• ```Course_Project.c```: This file contains the main script which forms the application entry point to the pedometer. The file contains the function in the infinite loop to check the detection of the step and print the required message on the display.  

### Software Flow  
```
![SOFTWARE_FLOW_DIAGRAM][SOFTWARE_FLOW_DIAGRAM]
```

## Hardware Requirements  
o FRDM-KL25Z Evaluation Board  
o 5V 16x2 LCD  
o External Push-Button/TSI Touch Sensor  
o MMA8451Q - Accelerometer (On-board accelerometer)  
o Header connectors for evaluation board  

## System Flow  
```
![SYSTEM_FLOW][SYSTEM_FLOW]  
```

## Manual Test Routine  
To test the system, user can refer to the manual test case routine. The steps should be followed to visually check the functionality of the system. The test should be done on the ```Debug``` build to verify from the debug logs.   

Refer to the test document [here](https://github.com/ruchitnaik/CourseProject_Pedometer/blob/master/Documentation/Manual%20Test%20Routine%20Guide.pdf).

## Project Demo  
Please click on the link to access the video demo of the project [here]().  

Find the images of the working code posted below.  



[SOFTWARE_FLOW_DIAGRAM]: https://github.com/ruchitnaik/CourseProject_Pedometer/blob/master/Screen%20Shots/Flow%20Diagrams/Software%20Design%20Flow%20Diagram.drawio.png 
[SYSTEM_FLOW]: https://github.com/ruchitnaik/CourseProject_Pedometer/blob/master/Screen%20Shots/Flow%20Diagrams/System%20Block%20Diagram.drawio.png
