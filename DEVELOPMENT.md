# Development

* Successfully got the base app to compile and run
* Added ofSoundPlayers to play music/the background beat in a loop
    * Put the beat player in a thread as I wanted the beat/music to go continuously, regardless of what happens in the game
        * To start the thread, had to pass a pointer to a member function
* Refactor keyPressed() function to be cleaner
* Added a beat border
    * Border flashes with the beat
    * Some bugs with inconsistency, fixed through changing implementation
        * Changed from boolean controlled to time controlled
* Adjusted how "off tempo" you can be to get a regular score or good bonus
* Words are now correctly centered on the screen
* Border now flashes according to the feedback (Green for perfect, yellow for good, red for poor)
    * The words do too
* Added a sprite to the bottom of the screen
* Tuned border again, now feedback flashes with the border
    * Not sure if this is better, now the feedback is super quick, and it doesn't display if the beat isn't flashing too
* Refactored key pressed to work with a map containing the OF_KEYS and the Drum enum
    * Allows for simpler code and so I can keep track of notes played
* Now keeps track of the 4 beats played to create a combo
* Combo is now analyzed and turned into a command, if the combo is determined to not form a command halfway through, it fails
* After finishing command, you must now wait 4 beats to play another command
    * 4 beats to play, 4 beats to execute command
* Refactored project structure
    * Game extends ofBaseApp and Patapon is an object that Game uses so the methods in Patapon can be unit tested
    * Changed namespace from patapon to patapongame to avoid naming/namespace problems
* Integrated ofxBox2d


Notes:
- work on rhythm matching 
    
 