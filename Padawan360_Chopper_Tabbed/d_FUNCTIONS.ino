void triggerAutomation(){
  // Plays random sounds or dome movements for automations when in automation mode
    unsigned long currentMillis = millis();

    if (currentMillis - automateMillis > (automateDelay * 1000)) {
      automateMillis = millis();
      automateAction = random(1, 5);

      // On 1 just move - On 2,3 & 4 move and make sound - On 5 just make a sound
      if (automateAction > 1) {
        Play_Sound(random(2, 16)); // Short Sounds
      }
      if (automateAction < 4) {

      //************* Move the dome for 750 msecs  **************

      #ifdef Cytron10
        motor.setSpeed(Dome_Direction);    // Go one way
      #endif
        
      #if defined(SYRENSIMPLE)
        Syren10.motor(turnDirection);
      #else
        Syren10.motor(1, turnDirection);
      #endif

        delay(750);

        //************* Stop the dome motor **************
      #ifdef Cytron10
        motor.setSpeed(0);    // Stop
      #endif
      
      #if defined(SYRENSIMPLE)
        Syren10.motor(0);
      #else
        Syren10.motor(1, 0);
      #endif

        //************* Change direction for next time **************
        if (Dome_Direction>0) {  
          Dome_Direction = -100; 
        } else {  
          Dome_Direction = 100;    
        }
        
        if (turnDirection > 0) {
          turnDirection = -45;
        } else {
          turnDirection = 45;
        }
      }

      // sets the mix, max seconds between automation actions - sounds and dome movement
      automateDelay = random(5,15);
    }
}

void Check_Chatpad() {


    if (Xbox.getChatpadClick(XBOX_CHATPAD_D1, 0)) {
       //Duel of the Fates 
       Play_Sound(35); // Duel of Fates 4m 17s
    }   

    if (Xbox.getChatpadClick(XBOX_CHATPAD_D2, 0)) {
         //Theme
        Play_Sound(30); // Star Wars Theme 5m 29s
    }   

    if (Xbox.getChatpadClick(XBOX_CHATPAD_D3, 0)) {
       //Imperial March
       Play_Sound(31); // Imperial March 3m 5s
    }   
    
    if (Xbox.getChatpadClick(XBOX_CHATPAD_D4, 0)) {
       //Cantina
       Play_Sound(34); // Cantina 2m 50s
    }   

    if (Xbox.getChatpadClick(XBOX_CHATPAD_D5, 0)) {
       //Star Wars Rebels Stinger
       Play_Sound(32); // Star Wars Rebels Stinger 3s
    }   

        if (Xbox.getChatpadClick(XBOX_CHATPAD_D6, 0)) {
       //Star Wars Rebels Theme
       Play_Sound(33); // Star Wars Rebels Theme 1m 36s
    }   

/*
    if (Xbox.getChatpadClick(XBOX_CHATPAD_D8, 0)) {
       //Muppets
        Play_Sound(173); // Muppets Tune 30s
    }   

    if (Xbox.getChatpadClick(XBOX_CHATPAD_D9, 0)) {
       //Addams
       Play_Sound(168); // Addams family tune 53s
    }   

    if (Xbox.getChatpadClick(XBOX_CHATPAD_D0, 0)) {
       //Gangnam
       Play_Sound(169); // Gangam Styles 24s
    }   
*/
    if (Xbox.getChatpadClick(XBOX_CHATPAD_W, 0)) {
       //WolfWhistle
       Play_Sound(36); // Wolf whistle
    }

    if (Xbox.getChatpadClick(XBOX_CHATPAD_O, 0)) {
       //scream
       Play_Sound(1); // Scream
    }
/*    
    if (Xbox.getChatpadClick(XBOX_CHATPAD_S, 0)) {
       //ohh (Sad Sound)
       Play_Sound(random(25, 31)); // ohh (Sad Sound)  
    }
*/
    if (Xbox.getChatpadClick(XBOX_CHATPAD_D, 0)) {
        //DOODOO
        Play_Sound(15); // DOODOO
    }
    
    if (Xbox.getChatpadClick(XBOX_CHATPAD_T, 0)) {
        //TaDa
        Play_Sound(16); // TaDa
    }
/*    
    if (Xbox.getChatpadClick(XBOX_CHATPAD_L, 0)) {
      if (Xbox.getButtonPress(L2 , 0)){
       //Luke message
       Play_Sound(171); // Luke Message 26s
      }
     else {
       Play_Sound(5); // Leia Long 35s
      }
    }
*/    
    if (Xbox.getChatpadClick(XBOX_CHATPAD_P, 0)) {
      if (Xbox.getButtonPress(L2 , 0)){
        //Periscope Peek
        maestrohead.restartScript(3);//Periscope Peek (incl LED
      }
     else {
        //Periscope Full 
        maestrohead.restartScript(2);//Periscope Look Around (incl LED)
      }
    }
    
    if (Xbox.getChatpadClick(XBOX_CHATPAD_X, 0)) {
        //shortcircuit
       Play_Sound(13); // Short Circuit
    }

    if (Xbox.getChatpadClick(XBOX_CHATPAD_C, 0)) {
        //Chortle
        Play_Sound(23); // Chortle
    }


//Use "SPACE" to stop music and return to random lights
    if (Xbox.getChatpadClick(XBOX_CHATPAD_SPACE, 0)) {
        //Stop music tracks
        YX5300.playStop();
        mp3Trigger.stop(); 
    }
  
}

void Play_Sound(int Track_Num) {
 
  #ifdef MP3_YX5300
     YX5300.playTrack(Track_Num);
  #else
     mp3Trigger.play(Track_Num);  
  #endif 
 
}
