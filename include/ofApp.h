#include "ofMain.h"
#include "../include/pon.h"
#include <iostream>

namespace patapon {
    enum class GameState {
        IN_PROGRESS,
        FINISHED,
        PAUSED
    };

    class PataponGame : public ofBaseApp {
        GameState current_state_ = GameState::IN_PROGRESS;
        Pon pon_;

        bool should_update_  = true;
        int drum_played_;

        ofTrueTypeFont font_;

        double time_since_keypress_;

        ofSoundPlayer beat_player_;
        ofSoundPlayer music_player_;

        std::thread t;

        void drawDrumName();
        void drawFinished();

    public:
        //Run once
        void setup();
        void playRhythm();

        void update();
        void draw();

        void keyPressed(const int key);

    };



}
