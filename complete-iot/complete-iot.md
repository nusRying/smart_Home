# IOT Module Code

## Introduction To Module
__Code in the complete-iot.ino file is relevant for the ESP-8266 Wi-Fi Arduino Module.__  
Wifi Module, ESP-8266, is an arduino circuit board with WiFi compatibility. It allows us to change the state of digital pins over WiFi. 
For this process there are two options:
* Connect ESP to some controller mobile app, that will work as a remote for your digital pins. Blynk is a popular option in this regard.
* Write HTML code to create an IP-based web page with buttons.

We have used the latter approach in __complete_iot.ino__ file, as it allows complete customizibility and knows no creative boundaries.

## Running Code Steps
Change the SSID and Password in the code (ref line 4, 5) by the username and password of the Wi-Fi currently in your use.    
Select the pin numbers carefully, define in the code as well (ref line 19,20,21,22,23)
The given code allows pins for upto 6 digital output devices, you can always increase or decrease the number of pins, depending on your requirements.

