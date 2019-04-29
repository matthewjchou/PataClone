#include "../include/ofApp.h"
#include <thread>

using namespace patapongame;

void Game::setup() {
    ofSetWindowTitle("Patapon");
    current_state_ = GameState::IN_PROGRESS;

    box2d.init();
    box2d.setGravity(45, 10);
    box2d.createBounds();
    box2d.setFPS(40);
    box2dCircle.setPhysics(3, 1, 0.3);
    box2dCircle.setup(box2d.getWorld(), 100, ofGetWindowHeight() / 3, 100);

    patapon.can_play_ = true;
    executing_command_ = false;

    beat_count_ = 0;

    srand(time(NULL));
    distr_ = std::uniform_int_distribution<>(-60, 60);

    font_.load("arial.ttf", kFontSize);

    beat_player_.load("Metronome.mp3");
    beat_player_.setSpeed(kBeatSpeed);
    beat_player_.setVolume(kBeatVolume);

    //music_player_.load();

    win_player_.load("FireCrackers.mp3");

    pon_logo_.load("ClearPon.png");
    pon_logo_.crop(420, 300, 650, 490);
    pon_logo_.resize(1 * pon_logo_.getWidth() / 2, 1 * pon_logo_.getHeight() / 2);

    pon_standing_.load("Hatapon.png");
    pon_standing_.resize(1 * pon_standing_.getWidth() / 4, 1 * pon_standing_.getHeight() / 4);

    //pon_walking_.load("HataponWalking.png");
    //pon_walking_.crop(30, 27, 254, 445);
    //pon_walking_.resize(3 * pon_walking_.getWidth() / 2, 3 * pon_walking_.getHeight() / 2);
    boss_ = Boss("Gigantus", 1000, 200, "Gigantus.png");
    boss_.getImage().resize(2 * boss_.getImage().getWidth(), 2 * boss_.getImage().getHeight());

    patapon.input_count_ = 0;
    patapon.total_tempo_diff_ = 0;

    last_beat_time_ = 0;
    std::thread t(&Game::playRhythm, this);
    t.detach();
}

void Game::playRhythm() {
    while(true) {
        if (current_state_ == GameState::IN_PROGRESS && (!beat_player_.isPlaying())) {
            beat_player_.play();
            last_beat_time_ = ofGetElapsedTimeMillis();
            patapon.can_play_ = true;
            if (executing_command_) {
                beat_count_++;
                if (beat_count_ == 5) {
                    beat_count_ = 0;
                    executing_command_ = false;
                }
            }

        } else if (current_state_ == GameState::FINISHED) {
            break;
        }
    }
}

void Game::playWinSound() {
    if (!win_player_.isPlaying()) {
        win_player_.play();
    }
}

void Game::exit() {
    current_state_ = GameState::FINISHED;
    std::cout << "EXITING" << std::endl;
}

void Game::update() {
    if (!executing_command_ && ofGetElapsedTimeMillis() - time_since_keypress_ > 1200) {
        patapon.resetCombo();
    }
    box2d.update();
    draw();
}

void Game::draw() {
    ofBackgroundGradient(ofColor::white, ofColor::gray, OF_GRADIENT_LINEAR);
    drawLogo();
    box2d.drawGround();
    

    if (current_state_ == GameState::IN_PROGRESS) {
        ofPushStyle();
        ofSetLineWidth(15);
        ofSetColor(ofColor::brown);
        ofDrawLine(0, (3 * ofGetWindowHeight() / 4) - 46, ofGetWindowWidth(), (3 * ofGetWindowHeight() / 4) - 46);
        ofPopStyle();
        drawBoss();
        drawPatapon();
        //drawPataponWalking();

        drawVolley();

        if (ofGetElapsedTimeMillis() - last_beat_time_  <= 100) {
            drawBeatBorder();
            beat_drawn_ = true;
        }
        if (ofGetElapsedTimeMillis() - last_beat_time_ <= 200 
            && ofGetElapsedTimeMillis() - time_since_keypress_ <= patapon.kNoPointTime) {
            drawTempoFeedback();
        }
        if (ofGetElapsedTimeMillis() - time_since_keypress_ <= 325) {
            drawDrumName(should_rotate_);
            should_rotate_ = false;
        }
        
    } else if (current_state_ == GameState::FINISHED) {
        drawFinished();
    }
}

void Game::drawDrumName(const bool should_rotate) {
    ofSetColor(ofColor::black);
    ofPushMatrix();

    int x;
    int y;
    if (should_rotate) {
        drum_theta_ = distr_(generator_);
    }
        
    switch (drum_played_) {
        case Drum::CHAKA:
            x = (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(patapon.kChaka, 0, 0).getMaxX() / 2);
            y = (ofGetWindowHeight() / 2) + 25;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            ofSetColor(ofColor::springGreen);
            font_.drawString(patapon.kChaka, 0, 0);
            break;

        case Drum::PON:
            x = (ofGetWindowWidth() / 4) 
                + (font_.getStringBoundingBox(patapon.kPon, 0 ,0).getMaxX() / 2) + 50;
            y = (2 * ofGetWindowHeight() / 3);
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            ofSetColor(ofColor::cyan);
            font_.drawString(patapon.kPon, 0, 0);
            break;

        case Drum::PATA:
            x = (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(patapon.kPata, 0, 0).getMaxX() / 2) - 200;
            y = (2 * ofGetWindowHeight() / 3);
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            ofSetColor(ofColor::orangeRed);
            font_.drawString(patapon.kPata, 0, 0);
            break;

        case Drum::DON:
            x = (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(patapon.kDon, 0 ,0).getMaxX() / 2);
            y = (ofGetWindowHeight() / 2) + 450;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            ofSetColor(ofColor::gold);
            font_.drawString(patapon.kDon, 0, 0);
            break;
    }
    ofPopMatrix(); //Resets the coordinate system
}

void Game::drawFinished() {
    ofSetColor(ofColor::black);
    std::string win_message = "You won! Congratulations!";
    font_.drawString(win_message, (ofGetWindowWidth() / 2) 
        - (font_.getStringBoundingBox(win_message, 0, 0).getMaxX() / 2)
        , ofGetWindowHeight() / 2);
    std::thread t(&Game::playWinSound, this);
    t.detach();
}

void Game::drawLogo() {
    ofSetColor(ofColor::white);
    pon_logo_.draw(ofGetWindowWidth() - pon_logo_.getWidth(),
        ofGetWindowHeight() - pon_logo_.getHeight());
}

void Game::drawBoss() {
    ofSetColor(ofColor::white);
    boss_.getImage().draw(1275, 337);
}

void Game::drawPatapon() {
    ofSetColor(ofColor::white);
    pon_standing_.draw((ofGetWindowWidth() / 4) - (pon_standing_.getWidth() / 2),
        (ofGetWindowHeight() / 2) - (pon_standing_.getHeight() / 2));
}

void Game::drawPataponWalking() {
    ofSetColor(ofColor::white);
    pon_walking_.draw((ofGetWindowWidth() / 2) - (pon_walking_.getWidth()),
        (ofGetWindowHeight() / 2) - (pon_walking_.getHeight()));
}

void Game::drawBeatBorder() {
    ofSetColor(ofColor::black);
    ofNoFill();

    ofDrawRectangle(ofGetWindowWidth() / 45, ofGetWindowHeight() / 30,
        ofGetWindowWidth() - (2 * ofGetWindowWidth() / 45),
        ofGetWindowHeight() - (2 * ofGetWindowHeight() / 30));

    ofDrawRectangle(ofGetWindowWidth() / 40, ofGetWindowHeight() / 25,
        ofGetWindowWidth() - (2 * ofGetWindowWidth() / 40),
        ofGetWindowHeight() - (2 * ofGetWindowHeight() / 25));

    beat_drawn_ = false;
}

void Game::drawTempoFeedback() {
    std::string output;
    ofNoFill();
    switch (tempo_feedback_) {
        case Feedback::PERFECT:
            output = "Perfect!";
            ofSetColor(ofColor::green);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2 * ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2 * ofGetWindowHeight() / 38));
            }
            break;

        case Feedback::GOOD:
            output = "Good!";
            ofSetColor(ofColor::yellow);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2 * ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2 * ofGetWindowHeight() / 38));
            }
            break;

        case Feedback::POOR:
            output = "Poor";     
            ofSetColor(ofColor::red);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2 * ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2 * ofGetWindowHeight() / 38));
            }
            break;
    }
    //Subtracts half the length of the bounding box of the string to actually center it
   font_.drawString(output, ofGetWindowWidth() / 2 
        - (font_.getStringBoundingBox(output, 0, 0).getMaxX() / 2), ofGetWindowHeight() / 2); 
}

void Game::drawVolley() {
    ofFill();
    ofSetColor(ofColor::black);
    box2dCircle.draw();
}

void Game::executeCommand(const Command command) {
    size_t augmented_damage;
    switch(command) {
        case Command::ATTACK:
            augmented_damage = pon_.getStrength() * patapon.score_scalar_;
            std::cout << "UNAUGMENTED DAMAGE: " << std::to_string(pon_.getStrength()) << std::endl;
            std::cout << "BEAT MULTIPLIER DAMAGE: " << std::to_string(augmented_damage) << std::endl;

            if (std::get<0>(charge_scalar_)) {
                augmented_damage *= std::get<1>(charge_scalar_);
                charge_scalar_ = std::make_tuple(false, 1);
                std::cout << "CHARGE MULTIPLIER DAMAGE: " << std::to_string(augmented_damage) << std::endl;
            }

            if (!boss_.takeDamage(augmented_damage)) {
                current_state_ = GameState::FINISHED;
            }   
            break;
        
        case Command::CHARGE:
            if (patapon.score_scalar_ == patapon.kMaxPointMultiplier) {
                charge_scalar_ = std::make_tuple(true, 3);
            } else if (patapon.score_scalar_ == patapon.kNormalPointMultiplier) {
                charge_scalar_ = std::make_tuple(true, 2);
            } else {
                charge_scalar_ = std::make_tuple(false, 1);
            }
            break;

        default:
            break;
    }
}

void Game::contactStart(ofxBox2dContactArgs &e) {

}

void Game::keyPressed(const int key) {
    auto it = kDrumMap.find(key);
    if (it != kDrumMap.end() && !executing_command_) {
        drum_played_ = it->second;
        time_since_keypress_ = ofGetElapsedTimeMillis();
        std::cout << "KEYPRESS: " << time_since_keypress_ << std::endl;
        int tempo_diff = time_since_keypress_ - last_beat_time_;
        std::cout << "TIME DIFF: " << tempo_diff << std::endl;
        tempo_feedback_ = patapon.calculateTempoFeedback(tempo_diff);
        should_rotate_ = true;
        patapon.can_play_ = false;

        Command command = patapon.handleMechanics(tempo_feedback_, it->second, tempo_diff);
        if (command != Command::NOTHING && command != Command::FAIL) {
            executing_command_ = true;
            executeCommand(command);
        }
        
        update();
    }
}

