#include "../include/ofApp.h"
#include <thread>

using namespace patapongame;

void Game::setup() {
    ofSetWindowTitle("Patapon");
    current_state_ = GameState::IN_PROGRESS;

    patapon.can_play_ = true;

    srand(time(NULL));
    distr_ = std::uniform_int_distribution<>(-60, 60);

    font_.load("arial.ttf", kFontSize);

    beat_player_.load("Metronome.mp3");
    beat_player_.setSpeed(kBeatSpeed);
    beat_player_.setVolume(kBeatVolume);
    //music_player_.load();

    pon_logo_.load("ClearPon.png");
    pon_logo_.crop(420, 300, 650, 490);
    pon_logo_.resize(2 * pon_logo_.getWidth() / 3, 2 * pon_logo_.getHeight() / 3);

    pon_standing_.load("Hatapon.png");
    pon_standing_.resize(1 * pon_standing_.getWidth() / 4, 1 * pon_standing_.getHeight() / 4);

    pon_walking_.load("HataponWalking.png");
    //pon_walking_.crop(30, 27, 254, 445);
    pon_walking_.resize(5 * pon_walking_.getWidth() / 4, 5 * pon_walking_.getHeight() / 4);

    patapon.beat_count_ = 0;
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

        } else if (current_state_ == GameState::FINISHED) {
            break;
        }
    }
}

void Game::exit() {
    current_state_ = GameState::FINISHED;
    std::cout << "EXITING" << std::endl;
}

void Game::update() {
    draw();
}

void Game::draw() {
    ofBackgroundGradient(ofColor::white, ofColor::gray, OF_GRADIENT_LINEAR);
    drawLogo();

    if (current_state_ == GameState::IN_PROGRESS) {
        drawPatapon();
        drawPataponWalking();
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
            x = (ofGetWindowWidth() / 2) 
                - (font_.getStringBoundingBox(patapon.kChaka, 0, 0).getMaxX() / 2);
            y = ofGetWindowHeight() / 4;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            font_.drawString(patapon.kChaka, 0, 0);
            break;

        case Drum::PON:
            x = (3 * ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(patapon.kPon, 0 ,0).getMaxX() / 2);
            y = ofGetWindowHeight() / 2;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            font_.drawString(patapon.kPon, 0, 0);
            break;

        case Drum::PATA:
            x = (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(patapon.kPata, 0, 0).getMaxX() / 2);
            y = ofGetWindowHeight() / 2;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            font_.drawString(patapon.kPata, 0, 0);
            break;

        case Drum::DON:
            x = (ofGetWindowWidth() / 2) 
                - (font_.getStringBoundingBox(patapon.kDon, 0 ,0).getMaxX() / 2);
            y = 3 * ofGetWindowHeight() / 4;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            font_.drawString(patapon.kDon, 0, 0);
            break;
    }
    ofPopMatrix(); //Resets the coordinate system
}

void Game::drawFinished() {
    ofSetColor(ofColor::black);
    
    font_.drawString("You lost :(", ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void Game::drawLogo() {
    ofSetColor(ofColor::white);
    pon_logo_.draw(ofGetWindowWidth() - pon_logo_.getWidth(),
        ofGetWindowHeight() - pon_logo_.getHeight());
}

void Game::drawPatapon() {
    ofSetColor(ofColor::white);
    pon_standing_.draw((ofGetWindowWidth() / 2) - (pon_standing_.getWidth() / 2),
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

void Game::keyPressed(const int key) {
    auto it = kDrumMap.find(key);
    if (it != kDrumMap.end()) {
        drum_played_ = it->second;
        time_since_keypress_ = ofGetElapsedTimeMillis();
        std::cout << "KEYPRESS: " << time_since_keypress_ << std::endl;
        int tempo_diff = time_since_keypress_ - last_beat_time_;
        std::cout << "TIME DIFF: " << tempo_diff << std::endl;
        tempo_feedback_ = patapon.calculateTempoFeedback(tempo_diff);
        should_rotate_ = true;
        patapon.can_play_ = false;

        Command command = patapon.handleMechanics(tempo_feedback_, it->second, tempo_diff);
        
        update();

    }
}

