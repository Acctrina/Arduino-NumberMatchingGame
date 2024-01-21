# Project Overview
A memory-based number matching game to help keep the minds of seniors active through daily use of their cognitive functions to help combat the long-term effects of dementia. This project has been made to be used in active ageing centers around Singapore and has been specifically designed with simplicity in mind to be catered to the elderly for ease of use, as well as to be contactless for hygiene purposes.

# Board Design

**Slave Board:**
The slave board design uses a MAX7219 Dot Matrix LED to display the patterns and HC-SR04 Ultrasonic sensors to trigger the displays to light up when sensed. The slave modules are programmed using a 8-bit microcontroller, the ATMega328p

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/c4f2b396-3dd8-48a7-b5f0-ae9abd4ece87)

**Master Board:**
Likewise, the master board design also uses the ATMega328p microcontroller and works identically to an Arduino Uno. The only difference is that there are dedicated I2C pin connections for communication between Master and Slave boards along with pins for the timer module for neater connections.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/f4ec0a28-9d5d-49f7-a58d-c33a610909c8)

**Timer Module:**
The timer module is a 4 in 1 MAX7219 Dot Matrix Display Module and is controlled by the master board through SPI. This displays a timer that counts up when the game is started and stops it when it has ended.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/3678c471-1e97-4023-8fda-ca1d1d344bfc)

**Reset Module:**
The reset module is identical to the slave module, with the difference being only the code used to program it. With its function to reset the game when sensed. It also serves a double function as a display to show the last number sensed by the player.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/0036f85e-7c0d-4ca1-a1fb-bf9fbda18f40)

# Design Layout

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/47ecc119-1130-4fc3-9355-0b17b7d92e75)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/5e83c2ea-7a28-40e9-9256-1e3260ff35e1)

# Program Overview 

The master program is responsible for transmitting a random number from a set sequence to each slave board as well as the comparison to see if a pair of numbers that has been sensed are matching or not. In which case, it will then tell the respective slave boards that have been sensed to remain turned ON if it matches or OFF if otherwise. It also controls the Timer module and Reset Module.

The slave board is responsible for lighting up when sensed, showing its assigned digit and to inform the master when it has been sensed.

The timer module is for keeping track of the duration the game lasts for as soon as it starts.

The reset module serves two purposes, one which is to start a new game while the other is to act as a display to show the previously sensed number

### Flow Chart of Respective Programs:


![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/53bb8849-5473-4b21-b50d-bf73d94046d7)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/011318c9-3b5a-4fcb-91ad-2b5e70e12cb5)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/919cc6ac-404c-4e55-a476-5ba06b3f8d11)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/2ca6f513-48c4-4f37-933c-5290b4d9802b)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/02108a42-d5bd-404e-9f86-8631930e7cd8)

# Assinging Unqiue Address to each Slave Board

### Using EEPROM

EEPROM stands for electrically erasable programmable read-only memory and is a type of non-volatile memory used in computers, microcontrollers and other electronic devices to store small amounts of data that can be erased and rewritten.

By using EEPROM I can assign the 16 slave modules their own unique ID. This unique ID is then permenantly stored for about a lifetime of 100,000 write cycles. With the slaves having their own ID, it can then be used for specific transmission of data by the Master to the Slave on a specific one to one basis. 

By using this code, it allows me to write and read values to and from the EEPROM of each slave device through the serial monitor.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/f618f699-2e29-4d8c-939a-eb8ed68c35d1)

# Master Program 

The master program mainly uses 2 libraries, Wire.h to allow communication between I2C devices and Ledcontrol.h to support up to 8 daisy chained MAX72XX drivers for the timer module through SPI.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/799da873-4258-4ff6-a30d-89ece43d4a14)

## Randomization of Values 

The randomization of values is done through the use of arrays and the random function. The arrays used are as shown:

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/821fb505-618d-43e6-9390-63af96b059b9)

With the use of the for loop and random function, the values in the according arrays can be randomized.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/a7a9369a-3985-4bd4-a391-915df113da10)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/eb98602f-aaec-4d83-8686-705723a3e366)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/312c1a7c-38a7-4491-869a-e393bfba466d)

### Serial Monitor Output: 

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/c71dda19-2a9e-40ba-81fa-b4ff93afb6cc)

## Transmission of Values

The transmission of the randomized values from master to slave through I2C is done through the use of the Wire.h library. The functions used are Wire.beginTransmission(), Wire.write() and Wire.endTransmission().

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/1af5aeae-a868-41d6-97de-dc79833a9344)

### Serial Monitor Output: 

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/5908ac6d-03ab-4630-918a-6fefe172700b)

## Comparison of Values 

When one of the slave modules is sensed, it transmits its assigned value to the master which stores it into an array for comparison on the 2nd Update.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/0c142b14-eba4-43c9-9506-66c8de4d02eb)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/053b53a4-5853-455d-818f-1ba5955077c9)

### Comparison of Values (1st Update) 

When one of the slave modules is sensed, it transmits its assigned value to the master which stores it into an array for comparison on the 2nd Update.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/cab68000-e5c4-4ad7-8485-24f7784c9093)

### Serial Monitor Output:

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/0542c711-d597-4ee5-9864-631d7f69239d)

### Comparison of Values (2nd Update) 

Likewise on the second slave module sensed, the value sent to the master is stored into the same compare array which will then be used to compare the two values.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/56ae156c-b61e-46ba-b9e8-5849d829181f)

### Serial Monitor Output: 

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/95570de8-61d1-43b7-9c9b-6651268ff136)

### Comparison (Matched) 

The comparison of values is done by adding the values from the 1st and 2nd Updates respectively and dividing them by 2.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/02bc40da-ee23-49c8-b7a2-79de78879654)

### Serial Monitor Output:

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/4c009e2a-e768-410f-a559-0279bc526d4a)

### Comparison (Not Matched) 

In the case where the compared values are different, the value divided will not be equal to value from the 1st Update as such, the if statement is false and the code will simply reset all values to repeat the process again.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/aec82fc9-3936-4ede-865a-64508aa108e8)

### Serial Monitor Output:

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/94f3327b-ba84-4945-8d2f-1d641d88e725)

# Slave Program

The slave program uses the NewPing.h library to control the ultrasonic sensors. The ultrasonic sensor only registers a input if anything comes within 1 - 3 cm of distance to it. If input is registered, it then displays the number assigned to it by the master board for a set amount of time before clearing the display again and showing nothing. Likewise if no input is detected nothing will be displayed.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/873db296-c4d6-4e91-9e96-d8470147ae54)

The number patterns are saved in binary representation to be displayed when needed.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/56546f79-af9d-4a99-b43b-309fb03310cb)

# Using interrupt for Timer

Using interrupt is the best option for a timer so that is does not disrupt the main code of the program since it runs in the background. It is also ideal for timing purposes as it does a specified function at a set interval.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/634876d2-6601-4d8b-bf79-e2196f8d2e11)

The ATMEGA32P microcontroller has 3 timers/counters, two 8-bit and one 16-bit each with their own prescalers and compare modes with the 16-bit having a capture mode too.

## Determining which Timer to use

For the timer module, it is using timer1 of the ATMEGA32P microcontroller which is a 16-bit timer/counter. In order to have an interrupt every second(1hz), we have to find which timer to use, using the equation:

**compare match register = [ 16,000,000Hz/ (prescaler * desired interrupt frequency) ] - 1**

Using a prescaler of 1024,

**compare match register = [16,000,000 / (1024 * 1) ] -1 = 15,624**

As such we have to use timer1 for the interrupt since:

**256 < 15,624 < 65,536**

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/84054462-7327-474c-9c6f-d4dd9e4b6d3b)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/7fb4d04b-e782-458b-9f61-901f6b408d1c)

## Timer 

The Timer works with the use of the LedControl.h library to display digits onto the dot matrix display. It does so by setting each row of each 8x8 Led Matrix to the specified orientation either through the use of binary or hexadecimal.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/56cea119-2960-431c-ad17-d888d3f52b41)

The calculation for the timer is done with a counter to count the seconds to then convert into minutes and to then update specific segments of the 4 in 1 Matrix Display Module and is done under interrupt to prevent disruption to the main program.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/fefc30e1-2d05-49a8-ad3c-cbd403a09b3e)

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/417b3cde-dddc-4de3-b34e-1693bbd5c716)

**Interrupt Code**

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/688918cb-33e6-4b75-a00d-44e35145907f)

## Reset Program

The reset program works by sensing the reset module for a set amount of time that is set through the millis() function. After this set amount of time has been reached, it will then send a request to the master for a reset.

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/8cbfeaa6-a004-4337-af4a-b55646eb5ed8)

In the master program this code is written outside of void setup:

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/8d952a8c-df4d-43fe-bd74-9bbac0b431de)

This code allows the program to be reset through the call of a resetFunc();

![image](https://github.com/Acctrina/Arduino-NumberMatchingGame/assets/126780174/0fae21ea-8ac1-4f0f-889c-e636678192f7)
















