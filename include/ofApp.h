#include "ofMain.h"
#include "../include/pon.hpp"
#include <iostream>
#include <random>
#include <time.h>

namespace patapon {
    const size_t kFontSize = 44;
    const double kBeatSpeed = 0.35;
    const double kBeatVolume = 1.0;
    const double kMaxPointTime = 200;
    const double kNoPointTime = 400;
    const size_t kMaxPointMultiplier = 2;
    const size_t kNormalPointMultiplier = 1;

    const std::string kChaka = "CHAKA";
    const std::string kPata = "PATA";
    const std::string kPon = "PON";
    const std::string kDon = "DON";

    enum class GameState {
        IN_PROGRESS,
        FINISHED,
        PAUSED
    };

    enum class Feedback {
        PERFECT,
        GOOD,
        POOR
    };

    class PataponGame : public ofBaseApp {
        GameState current_state_;
        Feedback tempo_feedback_;
        Pon pon_;

        std::mt19937 generator_;
        std::uniform_int_distribution<> distr_;

        bool beat_drawn_;
        bool display_scalar_;
        bool should_rotate_;
        size_t drum_played_;
        int drum_theta_;

        ofTrueTypeFont font_;

        double time_since_keypress_;
        double last_beat_time_;

        size_t beat_count_;
        size_t total_tempo_diff_;
        size_t score_scalar_;

        ofSoundPlayer beat_player_;
        ofSoundPlayer music_player_;

        ofImage pon_logo_;
        ofImage pon_standing_;
        ofImage pon_walking_;
        Pon pon;

        std::vector<size_t> valid_keys_  {OF_KEY_UP, OF_KEY_RIGHT, OF_KEY_LEFT, OF_KEY_DOWN};

        void drawDrumName(bool should_rotate);
        void drawFinished();
        void drawLogo();
        void drawPatapon();
        void drawPataponWalking();
        void drawBeatBorder();
        void drawTempoFeedback();

        Feedback calculateTempoFeedback(int tempo_diff);
        size_t calculateScoreScalar(size_t tempo_diff);

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



}
