 
// =======================================================================================
// /////////////// Padawan360 Body Code - Mega v2.0 - Chopper ////////////////////////////
// =======================================================================================
/*

v2.1 Changes
Code for Cytron10 Dome motor driver added (Code for Syren10 motor controller retained) - https://github.com/CytronTechnologies/CytronMotorDriver
Code for Body and Dome Pololu Maestro controlles added
Removed all I2C options


v2.0 Changes:
- Makes left analog stick default drive control stick. Configurable between left or right stick via isLeftStickDrive 

v1.4
by Steven Sloan 
Code for YX5300 sound card added.Use "#define MP3_YX5300" if YX5300 is to be used (Code for Sparkfun MP3 Trigger retained but not tested).  
YX5300 arduino library at https://github.com/MajicDesigns/MD_YX5300
Serial connection to FlthyHP breakout board added.  Removed I2C comms to FlthyHP.
Added additional key combinations for extra sounds and actions.

v1.3 by Andy Smith (locqust)
- added in code to move automation to a function so can leave him chatting without controller being on
- code kindly supplied by Tony (DRK-N1GT)

v1.2 by Andy Smith (locqust)
-added in my list of expanded sound files and their associated command triggers. Sound files taken from BHD's setup

v1.1
by Robert Corvus
- fixed inverse throttle on right turn
- where right turn goes full throttle on slight right and slow when all the way right
- fixed left-shifted deadzone for turning
- fixed left turn going in opposite direction
- fixed default baud rate for new syren10
- clarified variable names

V1.0
by Dan Kraus
dskraus@gmail.com
Astromech: danomite4047
Project Site: https://github.com/dankraus/padawan360/

Heavily influenced by DanF's Padwan code which was built for Arduino+Wireless PS2
controller leveraging Bill Porter's PS2X Library. I was running into frequent disconnect
issues with 4 different controllers working in various capacities or not at all. I decided
that PS2 Controllers were going to be more difficult to come by every day, so I explored
some existing libraries out there to leverage and came across the USB Host Shield and it's
support for PS3 and Xbox 360 controllers. Bluetooth dongles were inconsistent as well
so I wanted to be able to have something with parts that other builder's could easily track
down and buy parts even at your local big box store.

Hardware:
***Arduino Mega 2560***
USB Host Shield from circuits@home
Microsoft Xbox 360 Controller
Microsoft Xbox 360 Chatpad (Requires https://github.com/willtoth/USB_Host_Shield_2.0/tree/xbox-chatpad version of USB_Host_Shield_2.0 Library)
Xbox 360 USB Wireless Reciver
Sabertooth Motor Controller
Syren Motor Controller
Sparkfun MP3 Trigger (or YX-5300)

This sketch supports I2C and calls events on many sound effect actions to control lights and sounds.
It is NOT set up for Dan's method of using the serial packet to transfer data up to the dome
to trigger some light effects.If you want that, you'll need to reference DanF's original Padawan code.

It uses Hardware Serial pins on the Mega to control Sabertooth and Syren

Set Sabertooth 2x25/2x12 Dip Switches 1 and 2 Down, All Others Up
For SyRen Simple Serial Set Switches 1 and 2 Down, All Others Up
For SyRen Packetized Serial Set Switchs 1, 2 & 4 Down, All Others Up
Placed a 10K ohm resistor between S1 & GND on the SyRen 10 itself

Pins in use
1 = MP3 Trigger Rx
3 = EXTINGUISHER relay pin

PWM 2 = Dome Nod Servo PWM

PWM 3 = Cytron10 PWM (speed) Input
PWM 4 = Cytron10 DIR Input

PWM 5 = Rx to YX5300 MP3 player
PWM 6 = Tx to YX5300 MP3 player

PWM 10 = Maestro Dome Serial Rx
PWM 11 = Maestro Dome Serial Tx

14 = Serial3 (Tx3) = Maestro Body Serial 
15 = Serial3 (Rx3) = Maestro Body Serial
16 = Serial2 (Tx2) = Syren10 S1
18 = Serial1 (Tx1) = Sabertooth 2x25 S1
19 = Serial1 (Rx1) = Sabertooth 2x25 S2

*/
