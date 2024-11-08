# Mouse-City
Welcome to the NextGen Environmental Sensor Lab's Mouse City. We aim to simulate a city environment using urban sounds and various light patterns. This repository is currently incomplete but feel free to use the information available.

For any questions and concerns contact us at rtoledocrow@gc.cuny.edu. We'll try to answer as soon as possible!

Mouse City's core circuit components are a WeMos D1 Mini and a Audio FX Sound Board (from Adafruit). Additional contents of the circuit can be found in the [BOM](https://github.com/NextGen-Environmental-Sensor-Lab/Mouse-City/tree/main/BOM) folder above. The BOM for the full circuit is locate there as well.

<img src="Images/Mouse City Fritzing.PNG" width="300" height = "600"> 

## Content
### Arduino
* Required Libraries and Boards
* Code Contents
### Node-Red
* Node Function and Use
### Mouse City Circuit 
* Parts List

## Arduino IDE
To use the code in the [Arduino](https://github.com/NextGen-Environmental-Sensor-Lab/Mouse-City/tree/main/Arduino/CityMouseLight_Sound) folder the user needs to install the Adafruit Neopixel Repository and the esp8266 (by ESP8266 Community) board manager.
Once installed the code can be used. Note: Our code is a modified version of the Adafruit Neopixel strandtest example. This can be seen where we use the theaterchase function to rotate the lights around the LED strip.

Code Contents: Our code contains multiple functions to control audio, speaker volume, and LED strip function. Note: Our code only recognizes certain commands. Unknown commands will be ignored.
* Audio: Sound() Where each input calls the selected audio track to play.
* Volume: Volume() Where each input increases of decreases the volume.
* LED Strip: theaterChase() Where each input decides the pattern of the LED Strip for about 20 seconds.

## Node-Red
Node-Red is a low-level coding program that visualizes code. We use it to automate the scheduling of our lights and audio. This was done through the use of different blocks of code Node-Red calls 'nodes'. The collection of these nodes are known as 'flows'.

Getting started with Node-Red. All information on setting up Node-Red can be found [here](https://nodered.org/docs/getting-started/) for new users.


<img src="Images/NodeRed Image1.PNG" width="900" height = "450"> 

