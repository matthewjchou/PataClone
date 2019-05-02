#include "ofMain.h"
#include "../include/patapon.hpp"
#include "../include/pon.hpp"
#include "../include/boss.hpp"
#include "ofxBox2d.h"
#include <iostream>
#include <random>
#include <time.h>
#include <map>
#include <array>
#include <tuple>
#include <cmath>

namespace patapongame {
    enum class GameState {
        IN_PROGRESS,
        FINISHED,
        PAUSED
    };

    class Game : public ofBaseApp {
        const size_t kFontSize = 55;
        const double kBeatSpeed = 0.35;
        const double kBeatVolume = 1.0;
        const size_t kHitboxTransparency = 0;

        const std::map<size_t, Drum> kDrumMap  {
            {OF_KEY_UP, Drum::CHAKA},
            {OF_KEY_RIGHT, Drum::PON}, 
            {OF_KEY_LEFT, Drum::PATA}, 
            {OF_KEY_DOWN, Drum::DON}
        };

        std::mt19937 generator_;
        std::uniform_int_distribution<> distr_;
        std::normal_distribution<> norm_distr_;

        ofTrueTypeFont font_;

        GameState current_state_;
        Feedback tempo_feedback_;
        Command current_command_;
        Drum drum_played_;

        bool beat_drawn_;
        bool should_rotate_;
        bool should_draw_damage_;
        bool executing_command_;
        bool collision_;
        bool allow_damage_;

        int drum_theta_;
        int transparency_tick_;
        int augmented_damage_;

        double time_since_keypress_;
        double last_beat_time_;

        ofSoundPlayer beat_player_;
        ofSoundPlayer music_player_;
        ofSoundPlayer win_player_;
        ofSoundPlayer impact_player_;

        ofImage background_image_;
        ofImage pon_logo_;
        ofImage pon_standing_;
        ofImage pon_walking_;

        Patapon patapon = Patapon();
        Pon pon_ = Pon();
        Boss boss_;

        ofxBox2d box2d;
        ofxBox2dCircle box2dCircle;
        std::vector<std::shared_ptr<ofxBox2dCircle>> circles_;

        std::tuple<bool, size_t> charge_scalar_;
        std::tuple<ofPoint, ofPoint> ground_points_ = std::make_tuple(
            ofPoint(0, (3 * ofGetWindowHeight() / 4) - 46, 0)
            , ofPoint(ofGetWindowWidth(), (3 * ofGetWindowHeight() / 4) - 46, 0));
        
        void drawDrumName(const bool should_rotate);
        void drawFinished();

        void drawLogo();
        void drawBackgroundImage();

        void drawBoss();
        void drawBossIcon();
        void drawBossHealthBar();
        void drawDamageTaken(int damage);

        void drawGround();

        void drawPatapon();
        void drawPataponWalking();

        void drawBeatBorder();
        void drawTempoFeedback();
        void drawTempoFeedbackBorder();

        void drawVolley();

        void executeCommand(const Command command);

        void contactStart(ofxBox2dContactArgs &e);
        void contactEnd(ofxBox2dContactArgs &e);

        void createVolley(size_t score_scalar, std::tuple<bool, size_t> charge_scalar);
        void destroyVolley();

    public:
        //Run once
        void setup();
        void playRhythm();
        void playWinSound();
        void exit();

        //Loop
        void update();
        void draw();

        void keyPressed(const int key);

    };



}//namespace patapon
