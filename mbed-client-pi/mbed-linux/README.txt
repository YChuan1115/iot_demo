
mbed client using Raspberry Pi with IT-Pi Shield
Author: joseph chen (robot@ittraining.com.tw)
WebSite: www.ittraining.com.tw
-------------------------------------------


How to build 
===================

step1: download compiler and set PATH environment 

step2: cd trunk/git/mbed-client-linux-example

#clean up code
yotta clean

# build code 
yotta build

Note: you have to go to the mDS and login, and then generate the "DEVICE SECURITY CREDENTIALS" for your device(raspberry Pi) 


How to Execute
===================

cd  mbed-client-linux-example/build/x86-linux-native/source
./mbed-client-linux-example


How to Test
===================
Note: login into mDS, and use API console to do some test .
POST /GPIO/0/STATE with payload data 27/1  ==> LED ON
POST /GPIO/0/STATE with payload data 27/0  ==> LED OFF
POST /GPIO/0/STATE with payload data 12/1  ==> Buzzer ON
POST /GPIO/0/STATE with payload data 12/0  ==> Buzzer OFF

GET /GPIO/0/STATE 
==>
{"GPIO_STATUS":[{"GPIO":12,"value":0},{"GPIO":17,"value":0},{"GPIO":22,"value":0},{"GPIO":23,"value":0},{"GPIO":24,"value":0},{"GPIO":27,"value":0}]}



References
====================

1)To Deploy mbed IoT cloud
http://blog.ittraining.com.tw/2016/07/to-deploy-mbed-iot-cloud.html
2)ARM mbed cloud server
https://connector.mbed.com/
3)Raspberry Pi 上編譯mbed client
http://blog.ittraining.com.tw/2016/06/raspberry-pi-mbed-client.html#links
4)ARM mbed cloud slide
http://blog.ittraining.com.tw/2016/08/arm-mbed-client-code.html