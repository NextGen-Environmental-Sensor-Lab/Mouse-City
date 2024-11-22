# Mouse-City
Welcome to the NextGen Environmental Sensor Lab's Mouse City. We aim to simulate a city environment using urban sounds and various light patterns. This repository is currently incomplete but feel free to use the information available.

For any questions and concerns please file an issue through the issue tab. We'll try to resolve the issue as soon as possible!

Mouse City's core circuit components are a WeMos D1 Mini and a Audio FX Sound Board (from Adafruit). Additional contents of the circuit can be found in the [BOM](https://github.com/NextGen-Environmental-Sensor-Lab/Mouse-City/blob/main/BOM.md)  above. The BOM of the full circuit is located there as well.




<img src="Images/Mouse City Fritzing.PNG" width="300" height = "600"> 

## Content
### Arduino
* Required Libraries and Boards
* Code Contents
### Audio Tracks
* Audio File Type
* Converter
### Mouse City Circuit 
* Parts List
### Node-Red
* Node Function and Use


## Arduino IDE
To use the code in the [Arduino](https://github.com/NextGen-Environmental-Sensor-Lab/Mouse-City/tree/main/Arduino/CityMouseLight_Sound) folder the user needs to install the Adafruit Neopixel library and the esp8266 (by ESP8266 Community) board manager.
Once installed the code can be used. 

Note: The board used from this board manager is the "WEMOS D1 MINI ESP32".

Also Note: Our code is a modified version of the Adafruit Neopixel strandtest example. This can be seen where we use the theaterchase function to rotate the lights around the LED strip.

Code Contents: Our code contains multiple functions to control audio, speaker volume, and LED strip function. 

Note: Our code only recognizes certain commands. Unknown commands will be ignored.
* Audio: Sound() Where each input calls the selected audio track to play. There are 4 pins available, but only 3 are in use here.
* Volume: Volume() Where each input increases of decreases the volume.
* LED Strip: theaterChase() Where each input decides the pattern of the LED Strip for about 20 seconds.

## Audio Tracks 
To use the Sound() function the Arduino Soundboard needs at least one audio track. These tracks must be wav files. If the files you intend to use are different you can convert them. The converter we used is [cloud convert](https://cloudconvert.com/mp3-to-wav). 

Note: The soundboard only accepts 8 or 16 bit wav files. (The higher the bit the better the audio sounds). Also mono files compared to stero files are smaller in size allowing for less storage consumption. 

## Mouse City Circuit 
### Parts List
<img src="Images/City Mouse Image 1.jpg" width="500" height = "400">

| Part Name | Part Image | Purchase Link|
|----------|--------|:-----------------------:|
|1000 µF Capacitor| <img src="Images/Core Circuit Images/Capacitor.png" width="150" height = "200"> |[Digikey](https://www.digikey.com/en/products/detail/panasonic-electronic-components/ECA-1CM102B/8603353?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Medium%20ROAS%20Categories&utm_term=&utm_content=&utm_id=go_cmp-20223376311_adg-_ad-__dev-c_ext-_prd-8603353_sig-Cj0KCQjwjNS3BhChARIsAOxBM6rq-EZxlEMLGUnWqKobcya32Tr_djYuXm6wenygM1xgtaHWTUAy6HAaAiYCEALw_wcB&gad_source=1&gclid=Cj0KCQjwjNS3BhChARIsAOxBM6rq-EZxlEMLGUnWqKobcya32Tr_djYuXm6wenygM1xgtaHWTUAy6HAaAiYCEALw_wcB)
|470 Ohm Resistor| <img src="Images/Core Circuit Images/Resistor.png" width="170" height = "200"> |[Digikey](https://www.digikey.com/en/products/detail/koa-speer-electronics,-inc./CF1%2F4C471J/13537235?utm_adgroup=General&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Zombie%20SKUs&utm_term=&utm_content=General&utm_id=go_cmp-17815035045_adg-_ad-__dev-c_ext-_prd-13537235_sig-Cj0KCQjwjNS3BhChARIsAOxBM6pdZWOkhexXrhcUmCtDRSBonp6of6M5_js4P4ElzA45IlZfCEqIjtQaAlmEEALw_wcB&gad_source=1&gclid=Cj0KCQjwjNS3BhChARIsAOxBM6pdZWOkhexXrhcUmCtDRSBonp6of6M5_js4P4ElzA45IlZfCEqIjtQaAlmEEALw_wcB)
|Adafruit Audio FX Sound Board| <img src="Images/Core Circuit Images/Soundboard.png" width="250" height = "150"> |[Adafruit](https://www.adafruit.com/product/2217)
|Breadboard| <img src="Images/Core Circuit Images/Breadboard.png" width="100" height = "200"> |[Amazon](https://www.amazon.com/EL-CP-003-Breadboard-Solderless-Distribution-Connecting/dp/B01EV6LJ7G/ref=asc_df_B01EV6LJ7G/?tag=hyprod-20&linkCode=df0&hvadid=693308325598&hvpos=&hvnetw=g&hvrand=9404664182806824334&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9004080&hvtargid=pla-368202573973&psc=1&mcid=73a4e46a53ed3eadb095584a7921608a)
|ELEGOO PCB Board Kit| <img src="Images/Full Circuit/PCB Board Kit.png" width="175" height = "175"> |[Amazon](https://www.amazon.com/ELEGOO-Prototype-Soldering-Compatible-Arduino/dp/B072Z7Y19F)
|Jumper Wire Kit| <img src="Images/Core Circuit Images/WireKit.png" width="200" height = "150"> |[Amazon](https://www.amazon.com/AUSTOR-Lengths-Assorted-Preformed-Breadboard/dp/B07CJYSL2T/ref=sr_1_3?crid=B0S5ZQ43UCTK&dib=eyJ2IjoiMSJ9._--XVj7sIVPW5Oud9uWtGRLcItNAzP_oKgb5XnBnAESH-41hm1aXYP-z0LyQecbUB4PwCpd9hgam1p8XLSusb5WMATWn7WuKW8AMz0pzQ6uocTDJ6-z_yKWPa05zAXrPjlVQPw7SMG_stOkZY_B-my7qhvSwHimdq8Sg0STi3PvUP3RNw_jrSzReKq_a-bX7uVKZJ3SH7_5gO0ybMWKxvZ63AAHAKkg5hV3EBn4bnXx--lpvCitoiXIQm5Qiv4Ip0wajuGiETqRom6K2GbzhiYVLdXyJ1Mkv-b4P5QslpbE.52sJjcqXgAcbXkMpsyKdnvN-_KVsl35BuasWdHUbS9g&dib_tag=se&keywords=jumper+wire+kit&qid=1728051755&s=industrial&sprefix=jumper+%2Cindustrial%2C56&sr=1-3)
|LED Strip (White)| <img src="Images/Core Circuit Images/LEDStrip.png" width="250" height = "200"> |[BTF Lighting](https://www.btf-lighting.com/products/1-sk6812-rgbw-4-in-1-pixels-individual-addressable-led-strip-dc5v?_pos=1&_sid=09f9497e4&_ss=r&variant=45843368247522)
|Speaker - 40mm Diameter - 4 Ohm 5 Watt| <img src="Images/Core Circuit Images/Speaker.png" width="200" height = "200"> |[Adafruit](https://www.adafruit.com/product/3968)
|Terminal Blocks| <img src="Images/Full Circuit/Terminal Block.png" width="175" height = "175"> |[Digikey](https://www.digikey.com/en/products/detail/qualtek/311007-01/183390)
|WeMos D1 Mini (Microcontroller)| <img src="Images/Core Circuit Images/Wemos.png" width="175" height = "175"> |[Amazon](https://www.amazon.com/dp/B0BR9GBNZH?ref=fed_asin_title)

### Important Note!!
Running the LED Strip and Voltage Supply through the bread board will cause a short circuit. To avoid this we suggest a spliced connection between the power supply, LED strip, and terminal block.

## Node-Red
Node-Red is a low-level coding program that visualizes code. We use it to automate the scheduling of our lights and audio. This was done through the use of different blocks of code Node-Red calls 'nodes'. The collection of these nodes are known as 'flows'.

Getting started with Node-Red. All information on setting up Node-Red can be found [here](https://nodered.org/docs/getting-started/) for new users.


<img src="Images/NodeRed Image 1.png" width="900" height = "450"> 

* Node Function:
    * The orange box shows all of the known commands our code will accept. These nodes inject/input the stated commands into the wemos d1 mini.
    
        Note: The commands for Sounds (Train, Siren, and Jack Hammer) are "PLAY0\n", "PLAY1\n", and "PLAY2\n" respectively. 
    * The purple box outputs anything the serial port receives by use of the debug and serial port nodes. It also allows the user to disconnect from the serial port by injecting a "false".
    * The blue box contains the schedule for one of our audio tracks and lights. At a specified time set in the blue inject node (cronplus) the lights and sound play. The lights and sound are looped by the msg. node to play x amount of times that the user chooses.
    * The yellow box makes a local text file logging the inputs to the system through the use of a function we designed.
    * The green box is a special scheduler (timegate) that allows two different action to take place based on the time they receive a preset command.

Note: All NodeRed flows can be accessed [here](https://github.com/NextGen-Environmental-Sensor-Lab/Mouse-City/tree/main/Node%20Red%20Flows).

