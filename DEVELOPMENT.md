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



Notes:
- work on rhythm matching 
    
 