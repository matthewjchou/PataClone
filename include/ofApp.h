#include "ofMain.h"
#include "../include/pon.hpp"
#include <iostream>
#include <random>
#include <time.h>
#include <map>
#include <array>

namespace patapon {
    enum class GameState {
        IN_PROGRESS,
        FINISHED,
        PAUSED
    };

    enum class Drum {
        PATA,
        PON,
        CHAKA,
        DON 
    };

    enum class Feedback {
        PERFECT,
        GOOD,
        POOR
    };

    enum class Command {
        ATTACK,
        DEFEND,
        MOVE,
        CHARGE,
        JUMP,
        RUNAWAY,
        DANCE,
        NOTHING,
        FAIL
    };

    class PataponGame : public ofBaseApp {
        const size_t kFontSize = 44;
        const double kBeatSpeed = 0.35;
        const double kBeatVolume = 1.0;
        const double kMaxPointTime = 200;
        const double kEarlyPointTime = 500;
        const double kNoPointTime = 425;
        const size_t kMaxPointMultiplier = 2;
        const size_t kNormalPointMultiplier = 1;

        const std::string kChaka = "CHAKA";
        const std::string kPata = "PATA";
        const std::string kPon = "PON";
        const std::string kDon = "DON";

        const std::map<size_t, Drum> kDrumMap  {
            {OF_KEY_UP, Drum::CHAKA},
            {OF_KEY_RIGHT, Drum::PON}, 
            {OF_KEY_LEFT, Drum::PATA}, 
            {OF_KEY_DOWN, Drum::DON}
        };

        const std::array<Drum, 4> kMoveCommand = 
            {Drum::PATA, Drum::PATA, Drum::PATA, Drum::PON};
        const std::array<Drum, 4> kAttackCommand = 
            {Drum::PON, Drum::PON, Drum::PATA, Drum::PON};
        const std::array<Drum, 4> kDefendCommand = 
            {{Drum::CHAKA, Drum::CHAKA, Drum::PATA, Drum::PON}};
        const std::array<Drum, 4> kChargeCommand = 
            {{Drum::PON, Drum::PON, Drum::CHAKA, Drum::CHAKA}};

        std::mt19937 generator_;
        std::uniform_int_distribution<> distr_;

        ofTrueTypeFont font_;

        GameState current_state_;
        Feedback tempo_feedback_;
        Pon pon_;

        bool beat_drawn_;
        bool display_scalar_;
        bool should_rotate_;
        bool can_play_;

        Drum drum_played_;
        int drum_theta_;

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

        std::vector<Drum> combo_;   

        void drawDrumName(const bool should_rotate);
        void drawFinished();
        void drawLogo();
        void drawPatapon();
        void drawPataponWalking();
        void drawBeatBorder();
        void drawTempoFeedback();

        Feedback calculateTempoFeedback(const int tempo_diff);
        size_t calculateScoreScalar(const size_t tempo_diff);
        Command isValidCommand(const std::vector<Drum> &combo);
        Command handleMechanics(const Feedback feedback, const Drum drum, const size_t tempo_diff);

        std::string tempConvert(Drum d) {
            if (d == Drum::CHAKA) return kChaka;
            if (d == Drum::PATA) return kPata;
            if (d == Drum::PON) return kPon;
            if (d == Drum::DON) return kDon;

            return "";
        }

        std::string tempConvertCommand(Command c) {
            if (c == Command::ATTACK) return "ATTACK";
            if (c == Command::DEFEND) return "DEFEND";
            if (c == Command::MOVE) return "MOVE";
            if (c == Command::CHARGE) return "CHARGE";
            if (c == Command::DANCE) return "DANCE";
            if (c == Command::NOTHING) return "NOTHING";
            if (c == Command::FAIL) return "FAIL";

            return "";
        }
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
