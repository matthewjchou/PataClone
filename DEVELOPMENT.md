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


Notes:
- work on rhythm matching 
    
 