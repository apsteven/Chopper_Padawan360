//============================
//    MAIN LOOP             //
//============================

void loop() {
  Usb.Task();
  // if we're not connected, return so we don't bother doing anything else.
  // set all movement to 0 so if we lose connection we don't have a runaway droid!
  // a restraining bolt and jawa droid caller won't save us here!
  if (!Xbox.XboxReceiverConnected || !Xbox.Xbox360Connected[0]) {
    Sabertooth2x.drive(0);
    Sabertooth2x.turn(0);
    Syren10.motor(1, 0);
    firstLoadOnConnect = false;
    #ifdef Cytron10
      motor.setSpeed(0);    // Stop
    #endif  
    // If controller is disconnected, but was in automation mode, then droid will continue
    // to play random sounds and dome movements
    if(isInAutomationMode){
      triggerAutomation();
    }
    if(!manuallyDisabledController){     
    }
    return;
  }

  // After the controller connects, Blink all the LEDs so we know drives are disengaged at start
  if (!firstLoadOnConnect) {
    firstLoadOnConnect = true;
     Play_Sound(8);
    Xbox.setLedMode(ROTATING, 0);
    manuallyDisabledController=false;
  }
  
  if (Xbox.getButtonClick(XBOX, 0)) {
    if(Xbox.getButtonPress(L1, 0) && Xbox.getButtonPress(R1, 0)){ 
      manuallyDisabledController=true;
      Xbox.disconnect(0);
    }
  }

  // enable / disable right stick (droid movement) & play a sound to signal motor state
  if (Xbox.getButtonClick(START, 0)) {
    if (isDriveEnabled) {
      isDriveEnabled = false;
      Xbox.setLedMode(ROTATING, 0);
      Play_Sound(38); // 3 Beeps
    } else {
      isDriveEnabled = true;
      Play_Sound(37); // 2 Beeps
      // //When the drive is enabled, set our LED accordingly to indicate speed
      if (drivespeed == DRIVESPEED1) {
        Xbox.setLedOn(LED1, 0);
      } else if (drivespeed == DRIVESPEED2 && (DRIVESPEED3 != 0)) {
        Xbox.setLedOn(LED2, 0);
      } else {
        Xbox.setLedOn(LED3, 0);
      }
    }
  }

  //Toggle automation mode with the BACK button
  if (Xbox.getButtonClick(BACK, 0)) {
    if (isInAutomationMode) {
      isInAutomationMode = false;
      automateAction = 0;
      Play_Sound(38); // 3 Beeps
     } else {
      isInAutomationMode = true;
      Play_Sound(37); // 2 Beeps
    }
  }

  // Plays random sounds or dome movements for automations when in automation mode
  if (isInAutomationMode) {
    triggerAutomation();
}

  // Volume Control of MP3 Trigger
  // Hold R1 and Press Up/down on D-pad to increase/decrease volume
  if (Xbox.getButtonClick(DOWN, 0)) {
    // volume down
    if (Xbox.getButtonPress(R1, 0)) {
      
       #ifdef MP3_YX5300
           YX5300.volumeDec();
      #else    
        if (vol > 0) {
          vol--;
          mp3Trigger.setVolume(vol);  
        }
      #endif
      
    }
  }
  if (Xbox.getButtonClick(UP, 0)) {
    //volume up
    if (Xbox.getButtonPress(R1, 0)) {

       #ifdef MP3_YX5300
           YX5300.volumeInc();
      #else      
        if (vol < 255) {
          vol++;
          mp3Trigger.setVolume(vol);  
        }
      #endif
      
    }
  }


//Maestro Animation section

//***************** Body Animations ************************//

if (Xbox.getButtonPress(R2, 0)) {
    if (Xbox.getButtonPress(UP, 0)) {
     maestrobody.restartScript(0);// Arm & Doors open/close
    } 
  }

  if (Xbox.getButtonPress(R2, 0)) {
    if (Xbox.getButtonPress(DOWN, 0)) {
     maestrobody.restartScript(3);//Left door, Arm, Right door wave
    } 
  }

if (Xbox.getButtonPress(R2, 0)) {
    if (Xbox.getButtonPress(LEFT, 0)) {
     maestrobody.restartScript(1);//Arm out, wait4, arm in
    } 
  }
  if (Xbox.getButtonPress(R2, 0)) {
    if (Xbox.getButtonPress(RIGHT, 0)) {
     maestrobody.restartScript(2);//Doors open/close
    } 
  }

//***************** Dome Animations ************************//

if (Xbox.getButtonPress(L2, 0)) {
    if (Xbox.getButtonPress(UP, 0)) {
     maestrohead.restartScript(0);//Dome arms flex (async)
    } 
  }

  if (Xbox.getButtonPress(L2, 0)) {
    if (Xbox.getButtonPress(DOWN, 0)) {
     maestrohead.restartScript(1);//Dome arm flex (sync)
    } 
  }

  if (Xbox.getButtonPress(L2, 0)) {
    if (Xbox.getButtonPress(LEFT, 0)) {
     maestrohead.restartScript(2);//Periscope Look Around (incl LED)
    } 
  }

  if (Xbox.getButtonPress(L2, 0)) {
    if (Xbox.getButtonPress(RIGHT, 0)) {
     maestrohead.restartScript(3);//Periscope Peek (incl LED) //Single arm wave
    } 
  }
 
#if defined(CHATPAD)
  Check_Chatpad();
#endif

  // Y Button and Y combo buttons
  if (Xbox.getButtonClick(Y, 0)) {
     if (Xbox.getButtonPress(L1, 0) && Xbox.getButtonPress(R1, 0)) {
       //Addams
       Play_Sound(168); // Addams family tune 53s
     } else if (Xbox.getButtonPress(L1, 0)) {
        //Annoyed
        Play_Sound(8); // Annoyed sounds
    } else if (Xbox.getButtonPress(L2, 0)) {
        //Chortle
        Play_Sound(2); // Chortle
    } else if (Xbox.getButtonPress(R1, 0)) {
         //Theme
        Play_Sound(9); // Star Wars Theme 5m 29s
    } else if (Xbox.getButtonPress(R2, 0)) {
        //More Alarms
        Play_Sound(random(56, 71)); // More alarms
    } else {
        Play_Sound(random(13,17)); // Alarms
    }
  }

  // A Button and A combo Buttons
  if (Xbox.getButtonClick(A, 0)) {
   if (Xbox.getButtonPress(L1, 0) && Xbox.getButtonPress(R1, 0)) {
       //Gangnam
       Play_Sound(169); // Gangam Styles 24s
   } else if (Xbox.getButtonPress(L1, 0)) {
       //shortcircuit
       Play_Sound(6); // Short Circuit
    } else if (Xbox.getButtonPress(L2, 0)) {
       //scream
       Play_Sound(1); // Scream
    } else if (Xbox.getButtonPress(R1, 0)) {
       //Imperial March
       Play_Sound(11); // Imperial March 3m 5s
    } else if (Xbox.getButtonPress(R2, 0)) {
       //More Misc
       Play_Sound(random(72,99));  // Misc Sounds
    } else {
       //Misc noises
       Play_Sound(random(17,25)); // More Misc Sounds
    }
  }

  // B Button and B combo Buttons
  if (Xbox.getButtonClick(B, 0)) {
     if (Xbox.getButtonPress(L1, 0) && Xbox.getButtonPress(R1, 0)) {
        //Muppets
        Play_Sound(173); // Muppets Tune 30s
     } else if (Xbox.getButtonPress(L1, 0)) {
        //patrol
        Play_Sound(7); // Quiet Beeps
    } else if (Xbox.getButtonPress(L2, 0)) {
        //DOODOO
        Play_Sound(3); // DOODOO
    } else if (Xbox.getButtonPress(R1, 0)) {
       //Cantina
       Play_Sound(10); // Cantina 2m 50s
    } else if (Xbox.getButtonPress(R2, 0)) {
       //Proc/Razz
       Play_Sound(random(100, 138)); // Proc/Razz
    } else {
       //Sent/Hum
       Play_Sound(random(32,52)); //Sent/Hum
    }
  }

  // X Button and X combo Buttons
  if (Xbox.getButtonClick(X, 0)) {
   if (Xbox.getButtonPress(L1, 0) && Xbox.getButtonPress(R1, 0)) {
       //Leia Short
       Play_Sound(170); // Leia Short 6s
    } else if (Xbox.getButtonPress(L2, 0) && Xbox.getButtonPress(R1, 0)) {
       //Luke message
       Play_Sound(171); // Luke Message 26s
    } else if (Xbox.getButtonPress(L1, 0)) {
       // leia message L1+X
       Play_Sound(5); // Leia Long 35s
    } else if (Xbox.getButtonPress(L2, 0)) {
       //WolfWhistle
       Play_Sound(4); // Wolf whistle
    } else if (Xbox.getButtonPress(R1, 0)) {
       //Duel of the Fates 
       Play_Sound(12); // Duel of Fates 4m 17s
    } else if (Xbox.getButtonPress(R2, 0)) {
       //Scream/Whistle 
       Play_Sound(random(139, 168));    // Scream/Whistle
    } else {
       //ohh (Sad Sound)
       Play_Sound(random(25, 31)); // ohh (Sad Sound)  
    }
  }


  // Change drivespeed if drive is enabled
  // Press Left Analog Stick (L3) for left stick drive mode
  // Press Right Analog Stick (R3) for right stick drive mode
  // Set LEDs for speed - 1 LED, Low. 2 LED - Med. 3 LED High
  if (Xbox.getButtonClick(speedSelectButton, 0) && isDriveEnabled) {
    //if in lowest speed
    if (drivespeed == DRIVESPEED1) {
      //change to medium speed and play sound 3-tone
      drivespeed = DRIVESPEED2;
      Xbox.setLedOn(LED2, 0);
      Play_Sound(38); // 3 Beeps
    } else if (drivespeed == DRIVESPEED2 && (DRIVESPEED3 != 0)) {
      //change to high speed and play sound scream
      drivespeed = DRIVESPEED3;
      Xbox.setLedOn(LED3, 0);
      Play_Sound(39);  // Scream
    } else {
      //we must be in high speed
      //change to low speed and play sound 2-tone
      drivespeed = DRIVESPEED1;
      Xbox.setLedOn(LED1, 0);
      Play_Sound(37); // 2 Beeps
    }
  }


  // FOOT DRIVES
  // Xbox 360 analog stick values are signed 16 bit integer value
  // Sabertooth runs at 8 bit signed. -127 to 127 for speed (full speed reverse and  full speed forward)
  // Map the 360 stick values to our min/max current drive speed
  throttleStickValue = (map(Xbox.getAnalogHat(throttleAxis, 0), -32768, 32767, -drivespeed, drivespeed));
  if (throttleStickValue > -DRIVEDEADZONERANGE && throttleStickValue < DRIVEDEADZONERANGE) {  
    // stick is in dead zone - don't drive
    driveThrottle = 0;
  } else {
    if (driveThrottle < throttleStickValue) {
      if (throttleStickValue - driveThrottle < (RAMPING + 1) ) {
        driveThrottle += RAMPING;
      } else {
         driveThrottle = throttleStickValue;
      }
    } else if (driveThrottle > throttleStickValue) {
      if (driveThrottle - throttleStickValue < (RAMPING + 1) ) {
        driveThrottle -= RAMPING;
      } else {
        driveThrottle = throttleStickValue;
      }
    }
  }

  turnThrottle = map(Xbox.getAnalogHat(turnAxis, 0), -32768, 32767, TURNSPEED, -TURNSPEED);
//  turnThrottle = map(Xbox.getAnalogHat(turnAxis, 0), -32768, 32767, -TURNSPEED, TURNSPEED);

  // DRIVE!
  // right stick (drive)
  if (isDriveEnabled) {
    // Only do deadzone check for turning here. Our Drive throttle speed has some math applied
    // for RAMPING and stuff, so just keep it separate here
    if (turnThrottle > -DRIVEDEADZONERANGE && turnThrottle < DRIVEDEADZONERANGE) {
      // stick is in dead zone - don't turn
      turnThrottle = 0;
    }
    Sabertooth2x.turn(-turnThrottle);
    Sabertooth2x.drive(driveThrottle);
  }

  // DOME DRIVE!
    #ifdef Cytron10
      
          domeThrottle = (map(Xbox.getAnalogHat(domeAxis, 0), -32768, 32767,-255, 255));  

          if (domeThrottle > -Cytron10_DOMEDEADZONERANGE && domeThrottle < Cytron10_DOMEDEADZONERANGE) {  
            //stick in dead zone - don't spin dome  
            motor.setSpeed(0);    // Stop             
          } 
          else {  
            motor.setSpeed(domeThrottle);    // Stop
          }

    #else  
    
      domeThrottle = (map(Xbox.getAnalogHat(domeAxis, 0), -32768, 32767, DOMESPEED, -DOMESPEED));
          if (domeThrottle > -DOMEDEADZONERANGE && domeThrottle < DOMEDEADZONERANGE) {
            //stick in dead zone - don't spin dome
            domeThrottle = 0;
          }
        
          Syren10.motor(1, domeThrottle);
          
  #endif

      domeWobble = (map(Xbox.getAnalogHat(domenod, 0), -32768, 32767, DomeServohigh, DomeServolow));
      analogWrite(2,domeWobble); //write servo nod value to head nod servo  
} // END loop()
