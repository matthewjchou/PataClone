#include "ofMain.h"
#include "../include/pon.h"
#include <iostream>

namespace patapon {
    const size_t kFontSize = 44;
    const float kBeatSpeed = 0.35;
    const float kBeatVolume = 1.0;

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
        double last_beat_time_;

        double tempoDiff_;

        ofSoundPlayer beat_player_;
        ofSoundPlayer music_player_;

        std::vector<int> valid_keys_  {OF_KEY_UP, OF_KEY_RIGHT, OF_KEY_LEFT, OF_KEY_DOWN};

        void drawDrumName();
        void drawFinished();
        void drawBeatBorder();

        double calculateTempoDiff();

    public:
        //Run once
        void setup();
        void playRhythm();

        //Loop
        void update();
        void draw();

        void keyPressed(const int key);

    };



}
