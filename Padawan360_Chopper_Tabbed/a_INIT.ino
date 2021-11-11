
//************************** Set speed and turn speeds here************************************//

// SPEED AND TURN SPEEDS
//set these 3 to whatever speeds work for you. 0-stop, 127-full speed.
const byte DRIVESPEED1 = 25;//30;
// Recommend beginner: 50 to 75, experienced: 100 to 127, I like 100.
// These may vary based on your drive system and power system
const byte DRIVESPEED2 = 30;//45;
//Set to 0 if you only want 2 speeds.
const byte DRIVESPEED3 = 40;//60;

// Default drive speed at startup
byte drivespeed = DRIVESPEED1;

// the higher this number the faster the droid will spin in place, lower - easier to control.
// Recommend beginner: 40 to 50, experienced: 50 $ up, I like 70
// This may vary based on your drive system and power system
const byte TURNSPEED = 25;//40;

// Set isLeftStickDrive to true for driving  with the left stick
// Set isLeftStickDrive to false for driving with the right stick (legacy and original configuration)
boolean isLeftStickDrive = true; 

// If using a speed controller for the dome, sets the top speed. You'll want to vary it potenitally
// depending on your motor. My Pittman is really fast so I dial this down a ways from top speed.
// Use a number up to 127 for serial
const byte DOMESPEED = 100; //127;

//This is the dome nod servo, the upper and lower limits for the servo, you can increase or decrease each value to alter you specific servo. 
int DomeServolow = 140;
int DomeServohigh =224;

// Ramping- the lower this number the longer R2 will take to speedup or slow down,
// change this by incriments of 1
const byte RAMPING = 5;

// Compensation is for deadband/deadzone checking. There's a little play in the neutral zone
// which gets a reading of a value of something other than 0 when you're not moving the stick.
// It may vary a bit across controllers and how broken in they are, sometimex 360 controllers
// develop a little bit of play in the stick at the center position. You can do this with the
// direct method calls against the Syren/Sabertooth library itself but it's not supported in all
// serial modes so just manage and check it in software here
// use the lowest number with no drift
// DOMEDEADZONERANGE for the left stick, DRIVEDEADZONERANGE for the right stick
const byte DOMEDEADZONERANGE = 20;
const byte DRIVEDEADZONERANGE = 20;


// Set the baud rate for the Sabertooth motor controller (feet)
// 9600 is the default baud rate for Sabertooth packet serial.
// for packetized options are: 2400, 9600, 19200 and 38400. I think you need to pick one that works
// and I think it varies across different firmware versions.
const int SABERTOOTHBAUDRATE = 9600;

// Set the baud rate for the Syren motor controller (dome)
// for packetized options are: 2400, 9600, 19200 and 38400. I think you need to pick one that works
// and I think it varies across different firmware versions.
const int DOMEBAUDRATE = 9600;

//r2 String hpEvent = "";
//r2 char char_array[11];

// I have a pin set to pull a relay high/low to trigger my upside down compressed air like R2's extinguisher
//#define EXTINGUISHERPIN 3

#include <Sabertooth.h>
#include <MP3Trigger.h>
#include <XBOXRECV.h>

#include <Servos.h>
#include <PololuMaestro.h> // added the Maestro libray
#include <SoftwareSerial.h>
#include <SyRenSimplified.h>
#include <Adafruit_PWMServoDriver.h>
#include <CytronMotorDriver.h>

#include <MD_YX5300.h> // https://github.com/MajicDesigns/MD_YX5300

SoftwareSerial maestroSerial(10, 11); //tx pin 11

MiniMaestro maestrobody(Serial3); //create "maestrobody" as the maestro object for the body on Serial 3
MiniMaestro maestrohead(maestroSerial); //create "maestrohead" as the maestro object for the head on Software Serial

/////////////////////////////////////////////////////////////////
Sabertooth Sabertooth2x(128, Serial1);
Sabertooth Syren10(128, Serial2);

// Satisfy IDE, which only needs to see the include statement in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

// Set some defaults for start up
// 0 = full volume, 255 off
byte vol = 20;  //Sparkfun MP3 player volume
// false = drive motors off ( drive stick disabled ) at start
boolean isDriveEnabled = false;

// Automated functionality
// Used as a boolean to turn on/off automated functions like periodic random sounds and periodic dome turns
boolean isInAutomationMode = false;
unsigned long automateMillis = 0;
byte automateDelay = random(5, 20); // set this to min and max seconds between sounds
//How much the dome may turn during automation.
int turnDirection = 20;
// Action number used to randomly choose a sound effect or a dome turn
byte automateAction = 0;

char driveThrottle = 0; 
int throttleStickValue = 0;
int domeThrottle = 0; 
char turnThrottle = 0; 
int domeWobble = 0;

boolean firstLoadOnConnect = false;

AnalogHatEnum turnAxis;AnalogHatEnum throttleAxis;

AnalogHatEnum domeAxis;
AnalogHatEnum domenod;
ButtonEnum speedSelectButton;
ButtonEnum hpLightToggleButton;

boolean manuallyDisabledController = false;

boolean isHPOn = false;

MP3Trigger mp3Trigger;
USB Usb;
XBOXRECV Xbox(&Usb);

/***************** Cytron10 Configuration  *********************/
#define Cytron10 //Uncomment if using a Cytron10 motor controller for the dome
CytronMD motor(PWM_DIR, 3, 4);              // PWM = Pin 3, DIR = Pin 4.
//boolean Dome_Direction = false;             // Used for automation
int Dome_Direction = 100;             // Used for automation
const byte Cytron10_DOMEDEADZONERANGE = 60;    //Set this to the lowest value 

/****************** YX5300 Configuration  **********************/
#define MP3_YX5300   //Uncomment if using a YX5300 for sound
// Connections for serial interface to the YX5300 module
#ifdef MP3_YX5300
  const uint8_t YX5300_RX = 5;    // connect to TX of MP3 Player module
  const uint8_t YX5300_TX = 6;    // connect to RX of MP3 Player module
  MD_YX5300 YX5300(YX5300_RX, YX5300_TX); 
  uint16_t volume =12; //YX5300 Start volume
#endif

/***************************************************************/

/************* Xbox360 Chatpad Configuration  ******************/
#define CHATPAD    //Uncomment if using a chatpad 
