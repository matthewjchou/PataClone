#include "ofMain.h"
#include "../include/patapon.hpp"
#include "../include/pon.hpp"
#include <iostream>
#include <random>
#include <time.h>
#include <map>
#include <array>

namespace patapongame {
    enum class GameState {
        IN_PROGRESS,
        FINISHED,
        PAUSED
    };

    class Game : public ofBaseApp {
        const size_t kFontSize = 44;
        const double kBeatSpeed = 0.35;
        const double kBeatVolume = 1.0;

        const std::map<size_t, Drum> kDrumMap  {
            {OF_KEY_UP, Drum::CHAKA},
            {OF_KEY_RIGHT, Drum::PON}, 
            {OF_KEY_LEFT, Drum::PATA}, 
            {OF_KEY_DOWN, Drum::DON}
        };

        std::mt19937 generator_;
        std::uniform_int_distribution<> distr_;

        ofTrueTypeFont font_;

        GameState current_state_;
        Feedback tempo_feedback_;
        Pon pon_;

        bool beat_drawn_;
        bool should_rotate_;
        bool executing_command_;

        Drum drum_played_;
        int drum_theta_;
        size_t beat_count_;

        double time_since_keypress_;
        double last_beat_time_;

        ofSoundPlayer beat_player_;
        ofSoundPlayer music_player_;

        ofImage pon_logo_;
        ofImage pon_standing_;
        ofImage pon_walking_;

        Patapon patapon = Patapon();
        Pon pon;
        
        void drawDrumName(const bool should_rotate);
        void drawFinished();
        void drawLogo();
        void drawPatapon();
        void drawPataponWalking();
        void drawBeatBorder();
        void drawTempoFeedback();

    public:
        //Run once
        void setup();
        void playRhythm();
        void exit();

        //Loop
        void update();
        void draw();

        void keyPressed(const int key);

    };



}//namespace patapon
